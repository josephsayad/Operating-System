//
//  OS.cpp
//  Assignment I
//
//  Created by Joseph Sayad on 05/11/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#include "OperatingSystem.h"

/* Explicitly-defined default constructor */

OperatingSystem::OperatingSystem() : MAX_MEMORY(4000000000) {}

/* Execute OS */

void OperatingSystem::runSimulation() {
  userQueries();

  manager_.setMemoryCapacity(memorySize_);
  manager_.initializeRAM();
  manager_.memorySnapshot();
  cout << "\n";
  
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

void OperatingSystem::userQueries() {
  RAMQuery();
  IOQueries();

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

// May to have implement queryHelper as recursive

int OperatingSystem::queryHelper(string& userInput, int& number) {
  while (getline(cin, userInput)) {
    try {
      number = stoi(userInput);
      
      if (number < 0) {
  	    cout << "[os] Invalid entry: range from 0 to N.\n>\t"; 
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
  // Later implement something that checks if command[0] is a number, or string -
  // if not it lists commands! 

  if (typeOf == "twoParam") {
    
    if (command[0] != "A") {
      cout << "[os] Invalid command. Did you mean 'A'?\n";  
    } else { twoParamHandle(command); }
  }

  // ONE PARAM BELOW ---------------- Implement HANDLE & FUNCTION

  else if (typeOf == "oneParam") {
    if (command[0] == "D") {
      cout << "[os] Disk #n finished work! Error handle here\n";  
    }

    else if (command[0] == "d") {
      cout << "[os] Process using CPU requests disk #N. Error handle here!\n";  
    }
  
    else if (command[0] == "P") {
      cout << "[os] Printer #n finished work! Error handle here\n";  
    }

    else if (command[0] == "p") {
      cout << "[os] Process using CPU requests printer #N. Error handle here!\n";  
    }

    else if (command[0] == "S") {
      cout << "[os] Snapshot command. Error handle here!\n";
    }

    else {
      cout << "[os] Invalid command and/or number of parameters. Did you mean 'D', 'd', 'P', 'p', or 'S'?\n";       
    }
  }

  // NO PARAM BELOW ---------------- Implement HANDLE & FUNCTION

  else if (typeOf == "noParam") {
    
    if (command[0] != "t") {
      cout << "[os] Invalid command. Did you mean 't', or 'exit()'?\n";  
    }

    else {
      terminateProcess();
      scheduler_.readyQueueSnapshot();
    }
  }

  // WEIRD Input -----------------

  else {
    cout << "Error: Invalid command. Whitespace is not allowed before commands.\n";
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
  if (process == nullptr) { /* Can't schedule process that if no memory available. */ }
  
  else {
    scheduler_.eval(process);
    scheduler_.readyQueueSnapshot();
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
