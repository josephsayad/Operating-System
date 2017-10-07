//
//  OperatingSystem.h
//  Assignment I
//
//  Created by Joseph Sayad on 05/11/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <memory>

#include "Node.h"

#include "MemoryManagement.h"
#include "ShortTermScheduler.h"
#include "Printer.h"
#include "Disk.h"

using namespace std;

class OperatingSystem {
  
  public: 

  /* Explicitly-Defined Default Constructor */

  OperatingSystem();

  /* OS Simulation Execution Function */

  void runSimulation();
  //  Postcondition: Runs simulation when invoked.

  /* Convenience Function */

  void printCompSpecs();
  //  Postcondition: Prints the specifications of the simulated
  //  computer - amount of RAM in bytes, number of printers, and
  //  number of disks.
  
  private: 

  /* Private Data Members */

  unsigned int MAX_MEMORY;

  long memorySize_;
  int numberOfDisks_;
  int numberOfPrinters_; 

  MemoryManagement manager_;
  ShortTermScheduler scheduler_;
  
  vector<Printer> printers_;
  vector<Disk> disks_;

  /* Private Helper Methods */

  /* Query Functions */

  void userQueries();
  //  Postcondition: invokes RAMQuery, IOQueries, printCompSpecs, 
  //  and IO setup methods. 

  void RAMQuery();
  //  Postcondition: Writes RAM query to console and reads user 
  //  input.

  void IOQueries();
  //  Postcondition: Writes printer and disk queries to console and 
  //  reads user input. Invokes queryHelper method. 

  int queryHelper(string& userInput, int& number);
  //  Postcondition: returns an object of type int by copy, which
  //  sets numberOfPrinters_ and numberOfDisks_.

  /* IO Device Functions */

  void setupPrinters();
  //  Postcondition: dynamically allocates objects of type Printer
  //  via for loop, and Printer pointer.

  void processUsingCPURequestsPrinter(int number);
  //  Postcondition: Pushes pointer to object of type ProcessNode
  //  to specified printer queue.

  void printerRequestComplete(int number);
  //  Postcondition: Sets pointer to ProcessNode using specified 
  //  Printer object, pops the first element of the printer queue,
  //  and sets pointer to process as argument to scheculer_.eval 
  //  method.

  void printerQueueSnapshot();
  // Postcondition: Prints busy and not busy printers to console. 
  // Busy printers are followed by the process using and waiting 
  // for this particular IO device.
  
  void setupDisks();
  //  Postcondition: dynamically allocates objects of type Disk
  //  via for loop, and Disk pointer.

  void processUsingCPURequestsDisk(int number);
  //  Postcondition: Pushes pointer to object of type ProcessNode
  //  to specified disk queue.

  void diskRequestComplete(int number);
  //  Postcondition: Sets pointer to ProcessNode using specified 
  //  Disk object, pops the first element of the disk queue,
  //  and sets pointer to process as argument to scheculer_.eval 
  //  method.

  void diskQueueSnapshot();
  // Postcondition: Prints busy and not busy disks to console. 
  // Busy disks are followed by the process using and waiting 
  // for this particular IO device.

  void printIOSnapshot();
  //  Postcondition: Invokes printer QueueSnapshot and diskQueueSnapshot
  //  methods. 

  /* Listening and Parsing */

  void listen();
  //  Postcondition: Reads user input from console, categorizes commands 
  //  via typeOf local variable, invokes commandParse with typeOf and 
  //  an array of tokens as arguments.

  void commandParse(string (&command) [4], string& typeOf);
  //  Postcondition: Contains conditionals that will invoke various commands 
  //  of the simulation. Exceptions and error are handeled in this function.

  void twoParamHandle(string (&command) [4]);
  //  Postcondition: Creates process if all conditional checks are passed via
  //  scheduleProcess method.

  /* Scheduling and Termination of Processes */

  void scheduleProcess(ProcessNode* process);
  //  Postcondition: Schedules process via scheduler_.eval method.

  void terminateProcess();
  //  Postcondition: Terminates process using CPU (processUsingCPU points to
  //  is deleted and pointer is set to nullptr).
   
};

#endif
