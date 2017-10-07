//
//  ShortTermScheduler.h
//  Project 1
//
//  Created by Joseph Sayad on 05/11/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#ifndef SHORTTERMSCHEDULER_H
#define SHORTTERMSCHEDULER_H

#include <iostream>
#include <vector>
#include <list>

#include "Node.h"

using namespace std;

typedef list<ProcessNode*> priorityLevel;
typedef vector<priorityLevel> multiLevel;

class ShortTermScheduler {

  public: 

  /* Explicitly-Defined Default Constructor */

  ShortTermScheduler();

  /* Explicitly-Defined Default Destructor */

  ~ShortTermScheduler();

  /* CPU Scheduler Functions */

  void createReadyQueue();
  //  Postcondition: Pushes objects of type priorityLevel to the 
  //  readyQueue_.

  void eval(ProcessNode* newProcess);
  // Precondition: Requires an object of type ProcessNode by reference. 
  // Postcondition: A series of conditionals that are used a check for 
  // process insertion. Process will either end up at the CPU, or the 
  // readyQueue_. 

  void push(ProcessNode* newProcess);
  // Precondition: Requires an object of type ProcessNode by reference. 
  // Postcondition: Pushes a pointer to a ProcessNode object to the back
  // of a priorityLevel in the readyQueue_.

  void terminate(unsigned int& tPID);
  // Precondition: Requires an object of type unsigned int by reference. 
  // Postcondition: If there is a process in the CPU, this function will
  // terminate that process. Memory is deallocated and the dangling pointer
  // is set to nullptr. 

  /* IO Function */

  ProcessNode* toIODevice();
  // Postcondition: Pushes pointer to process to IO device, sets the 
  // processUsingCPU pointer to nullptr, and resets the pointer to the 
  // next higher-priority process in the readyQueue_ if one exists in 
  // the queue at the time.

  /* Convenience Functions */

  void readyQueueSnapshot();
  // Postcondition: Prints snapshot of Ready-Queue to console.

  private: 

  /* Private Data Members */

  priorityLevel zero_;
  priorityLevel one_;
  priorityLevel two_;
  priorityLevel three_;
  priorityLevel four_;

  multiLevel readyQueue_;
  ProcessNode *processUsingCPU_; 

};

#endif
