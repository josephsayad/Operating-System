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

  /* Explicitly-defined default constructor */

  OperatingSystem();

  /* Execute OS */

  void runSimulation();

  /* Convenience Functions */

  void printCompSpecs();
  
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

  void userQueries();
  void RAMQuery();
  void IOQueries();

  int queryHelper(string& userInput, int& number);

  /* IO DEVICE FUNCTIONS -------- */

  void setupPrinters();
  // --
  void processUsingCPURequestsPrinter(int number);
  void printerRequestComplete(int number);
  // --
  void printerQueueSnapshot();

  void setupDisks();
  // --
  void processUsingCPURequestsDisk(int number);
  void diskRequestComplete(int number);
  // --
  void diskQueueSnapshot();

  /* IO DEVICE FUNCTIONS -------- */

  void listen();
  void commandParse(string (&command) [4], string& typeOf);
  void twoParamHandle(string (&command) [4]);

  void scheduleProcess(ProcessNode* process);
  void terminateProcess();
  void printIOSnapshot();
   
};

#endif
