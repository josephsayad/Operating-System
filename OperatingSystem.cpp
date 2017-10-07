//
//  OS.cpp
//  Assignment I
//
//  Created by Joseph Sayad on 05/11/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#include "OperatingSystem.h"

/* Explicitly-Defined Default Constructor */

OperatingSystem::OperatingSystem() : MAX_MEMORY(4000000000) {}

/* OS Simulation Execution Function */

void OperatingSystem::runSimulation() {
  userQueries();

  manager_.setMemoryCapacity(memorySize_);
  manager_.initializeRAM();
  
  listen();
}

/* Convenience Functions */

void OperatingSystem::printCompSpecs() {
  cout << "\n";
  cout << setfill('-') << setw(56) << " ";
  cout << "\n|";

  cout << setfill(' ') <<  right << setw(34) << "Computer Specs";
  cout << setfill(' ') << setw(21) << "|\n";
  cout << setfill('-') << setw(56) << " ";
  cout << "\n";

  cout << setfill(' ') << left << setw(15) << "Memory Size [B]";
  cout << setfill(' ') <<  right << setw(15) << "Disks";
  cout << setfill(' ') <<  right << setw(23) << "Printers";
  cout << "\n";
  
  cout << setfill(' ') << left << setw(15) << memorySize_;
  cout << setfill(' ') <<  right << setw(15) << numberOfDisks_;
  cout << setfill(' ') <<  right << setw(23) << numberOfPrinters_;
  cout << "\n";

  cout << setfill('-') << setw(56) << " ";
  cout << "\n\n";
}

/* Private Helper Methods */

/* Query Functions */

void OperatingSystem::userQueries() {
  RAMQuery();
  IOQueries();

  setupPrinters();
  setupDisks();

  printCompSpecs();
}

void OperatingSystem::RAMQuery() {
  cout << "\n[os] How much RAM memory (bytes) is there on the simulated computer?\n>\t";
  
  string userInput;
  long size; 

  while (getline(cin, userInput)) {
    
    try {
      size = stoll(userInput);

  	  if (size <= 0 || size > MAX_MEMORY) { 
  	    cout << "[os] Invalid entry: size range from 1 to 4 billion bytes.\n>\t"; 
  	    continue; 
  	  } 

  	  else { 
  	  	memorySize_ = size; 
  	  	break; 
  	  }      
    }
    
    catch(invalid_argument& e) {
      cout << "[os] Invalid entry: enter integer value.\n>\t";
      continue; 
    }

    catch(out_of_range& e) {
      cout << "[os] Invalid entry: value is out of range.\n>\t";
      continue;
    }
  }
}

void OperatingSystem::IOQueries() { 
  string userInput = "";
  int number = -1; 

  cout << "[os] How many hard disks does the simulated computer have?\n>\t";
  numberOfDisks_ = queryHelper(userInput, number);

  userInput = ""; 
  number = -1;

  cout << "[os] How many printers does the simulated computer have?\n>\t";
  numberOfPrinters_ = queryHelper(userInput, number);
}

int OperatingSystem::queryHelper(string& userInput, int& number) {
  while (getline(cin, userInput)) {
    try {
      number = stoi(userInput);
      
      if (number <= 0) {
  	    cout << "[os] Invalid entry: range from 1 to N.\n>\t"; 
  	    continue; 
      } else {
        return number;
      }

    }
    
    catch(invalid_argument& e) {
      cout << "[os] Invalid entry: enter integer value.\n>\t";
      continue; 
    }

    catch(out_of_range& e) {
      cout << "[os] Invalid entry: value is out of range.\n>\t";
      continue;
    }
  }
}

/* IO Device Functions */

void OperatingSystem::setupPrinters() { 
  Printer *pointer = nullptr;

  for (int i = 0; i < numberOfPrinters_; ++i) {
    pointer = new Printer();
    printers_.push_back(*pointer);
  }

  pointer = nullptr;
}

void OperatingSystem::setupDisks() { 
  Disk *pointer = nullptr;

  for (int i = 0; i < numberOfDisks_; ++i) {
    pointer = new Disk();
    disks_.push_back(*pointer);
  }

  pointer = nullptr;
}

void OperatingSystem::listen() {
  cout << "[os] Listening for user commands. Enter exit() to terminate program.\n>\t";

  string userCommand;

  while (getline(cin, userCommand)) {
    stringstream ss(userCommand);
    string command [4];
    string token, typeOf;

    for (unsigned int i = 0; getline(ss, token, ' ') && i <= 3; ++i) {
      command[i] = token;
    }

    if (command[3] != "") {
      cout << "[os] Invalid entry: check command and/or parameters.\n";
      typeOf = "null"; 
    }

    else if (command[2] != "") { typeOf = "twoParam"; }

    else if (command[1] != "") { typeOf = "oneParam"; }

    else if (command[0] != "") {
      if (command[0] == "exit()") { cout << "\nbye...\n"; break; }    
      typeOf = "noParam";
    }

    if (typeOf != "null") { commandParse(command, typeOf); }

    cout << ">\t";
  }
}

void OperatingSystem::commandParse(string (&command) [4], string& typeOf) {
  
  /* Command with two parameters */

  if (typeOf == "twoParam") {
    
    if (command[0] != "A") {
      cout << "[os] Invalid command. Did you mean 'A'?\n";  
    } else { twoParamHandle(command); }
  }

  /* Command with one parameter */

  else if (typeOf == "oneParam") {
    
    if (command[0] == "d") {
      
      int number = 0;
      
      try {
        number = stoi(command[1]);
        
        if (number >= 0 && number < numberOfDisks_) {
          processUsingCPURequestsDisk(number);
        }

        else {
          cout << "[os] Invalid entry: out of disk range.\n";
        }
      }

      catch(invalid_argument& e) {
        cout << "[os] Invalid entry: disk number should be an integer value.\n";
      }

      catch(out_of_range& e) {
        cout << "[os] Invalid entry: out of disk range.\n";
      }
    }

    else if (command[0] == "D") {
      int number = 0;
      
      try {
        number = stoi(command[1]);
        
        if (number >= 0 && number < numberOfDisks_) {
          diskRequestComplete(number);
        }

        else {
          cout << "[os] Invalid entry: out of disk range.\n";
        }
      }

      catch(invalid_argument& e) {
        cout << "[os] Invalid entry: disk number should be an integer value.\n";
      }

      catch(out_of_range& e) {
        cout << "[os] Invalid entry: out of disk range.\n";
      }
    }
  
    else if (command[0] == "p") {
      
      int number = 0;
      
      try {
        number = stoi(command[1]);
        
        if (number >= 0 && number < numberOfPrinters_) {
          processUsingCPURequestsPrinter(number);
        }

        else {
          cout << "[os] Invalid entry: out of printer range.\n";
        }
      }

      catch(invalid_argument& e) {
        cout << "[os] Invalid entry: printer number should be an integer value.\n";
      }

      catch(out_of_range& e) {
        cout << "[os] Invalid entry: out of printer range.\n";
      }
    }

    else if (command[0] == "P") {
      int number = 0;
      
      try {
        number = stoi(command[1]);
        
        if (number >= 0 && number < numberOfPrinters_) {
          printerRequestComplete(number);
        }

        else {
          cout << "[os] Invalid entry: out of printer range.\n";
        }
      }

      catch(invalid_argument& e) {
        cout << "[os] Invalid entry: printer number should be an integer value.\n";
      }

      catch(out_of_range& e) {
        cout << "[os] Invalid entry: out of printer range.\n";
      }
    }

    else if (command[0] == "S") {
      if (command[1] == "r") {
        scheduler_.readyQueueSnapshot();
      } 

      else if (command[1] == "i") {
        printIOSnapshot();
      } 

      else if (command[1] == "m") {
        manager_.memorySnapshot();
      } 

      else {
        cout << "[os] Invalid snapshot parameter. Did you mean 'r', 'i', or 'm'?\n";  
      }
    }

    else {
      cout << "[os] Invalid command and/or number of parameters. Did you mean 'D', 'd', 'P', 'p', or 'S'?\n";       
    }
  }

  /* Command with no parameters */

  else if (typeOf == "noParam") {
    
    if (command[0] != "t") {
      cout << "[os] Invalid command. Did you mean 't', or 'exit()'?\n";  
    }

    else {
      terminateProcess();
    }
  }

  else {
    cout << "[os] Invalid command. Whitespace is not allowed before commands.\n";
  }
}

void OperatingSystem::twoParamHandle(string (&command) [4]) {
  
  /* Process priority error handling. */

  try {
    int priority = stoi(command[1]);
  
    if (priority >= 0 && priority < 5) { // If priority is valid...
      
      /* Process size error handling. */

      try {
        long size = stoll(command[2]);

        if (size <= 0 || size > memorySize_) { 
          cout << "[os] Invalid entry: size range from 1 to " << memorySize_ << ".\n"; 
        } 

        else { // If priority and size are valid... Manage new process in RAM & CPU schedule...
          unsigned int uPriority = priority;
          scheduleProcess(manager_.newProcess(uPriority, size));
        }  
      }
    
      catch(invalid_argument& e) {
        cout << "[os] Invalid entry: enter integer value for process size.\n";
      }

      catch(out_of_range& e) {
        cout << "[os] Invalid entry: size value is out of range.\n";
      }          
    } 

    else { 
      cout << "[os] Invalid entry: priority values range from 0 to 4.\n";
    }      
  }
  
  catch(invalid_argument& e) {
    cout << "[os] Invalid entry: enter integer value for priority.\n";
  }

  catch(out_of_range& e) {
    cout << "[os] Invalid entry: priority values range from 0 to 4.\n";
  }
}

void OperatingSystem::scheduleProcess(ProcessNode* process) {
  if (process == nullptr) { /* Can't schedule process: no memory available. */ }
  
  else {
    scheduler_.eval(process);
  }
}

void OperatingSystem::terminateProcess() {
  unsigned int processToRemove = -1; 
  scheduler_.terminate(processToRemove);

  if (processToRemove != -1) {
    manager_.evalMemory(processToRemove);
  }

  else {
    cout << "[memory manager] No memory to deallocate.\n";
  }
}

/* IO Device Functions */

void OperatingSystem::processUsingCPURequestsPrinter(int number) {
  ProcessNode *processPtr = scheduler_.toIODevice();

  if (processPtr == nullptr) { /* NO PROCESS USING CPU: IGNORE */ }

  else if (processPtr != nullptr) {
    printers_.at(number).push(processPtr);     
  }
}

void OperatingSystem::printerRequestComplete(int number) {
  if (!printers_.at(number).isEmpty()) {
    ProcessNode *process = nullptr;

    /* Step 1: Point to process and pop nullptr from printer queue */

    process = printers_.at(number).processUsingPrinter();

    /* in pop function, set pointer to nullptr */
    printers_.at(number).pop();
 
    //  Step 2: Let scheduler evaluate and push to either CPU or queue 

    scheduler_.eval(process);
  } else {
    cout << "Printer " << number << " is empty." << endl;
  }
}

void OperatingSystem::printerQueueSnapshot() {
  cout << "\n";
  cout << setfill('-') << setw(25) << " ";
  cout << "\n";
  
  for (int i = 0; i < printers_.size(); ++i) {
    if (!printers_.at(i).isEmpty()) {
      cout << "Printer #" << i << " :: BUSY\n";
      printers_.at(i).displayQueue();
    } else {
      cout << "Printer #" << i << " :: NOT BUSY\n";
    }

    cout << setfill('-') << setw(25) << " ";
    cout << "\n";
  }
}

void OperatingSystem::processUsingCPURequestsDisk(int number) {
  ProcessNode *processPtr = scheduler_.toIODevice();

  if (processPtr == nullptr) { /* NO PROCESS USING CPU: IGNORE */ }

  else if (processPtr != nullptr) {
    disks_.at(number).push(processPtr);     
  }
}

void OperatingSystem::diskRequestComplete(int number) {
  if (!disks_.at(number).isEmpty()) {
    ProcessNode *process = nullptr;

    /* Step 1: Point to process and pop nullptr from printer queue */

    process = disks_.at(number).processUsingDisk();

    /* in pop function, set pointer to nullptr */
    disks_.at(number).pop();
 
    //  Step 2: Let scheduler evaluate and push to either CPU or queue 

    scheduler_.eval(process);

  } else {
    cout << "Disk " << number << " is empty." << endl;
  }
}

void OperatingSystem::diskQueueSnapshot() {
  cout << setfill('-') << setw(25) << " ";
  cout << "\n";
  
  for (int i = 0; i < disks_.size(); ++i) {
    if (!disks_.at(i).isEmpty()) {
      cout << "Disk #" << i << " :: BUSY\n";
      disks_.at(i).displayQueue();
    } else {
      cout << "Disk #" << i << " :: NOT BUSY\n";
    }

    cout << setfill('-') << setw(25) << " ";
    cout << "\n";
  }
}

void OperatingSystem::printIOSnapshot() {
  cout << "\n";
  cout << setfill('-') << setw(56) << " ";
  cout << "\n|";

  cout << setfill(' ') <<  right << setw(30) << "IO DEVICES";
  cout << setfill(' ') << setw(25) << "|\n";
  cout << setfill('-') << setw(56) << " ";

  printerQueueSnapshot();
  diskQueueSnapshot();

  cout << "\n";
}