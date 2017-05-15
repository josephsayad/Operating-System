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
 
  /* Explicitly-defined default constructor */

  ShortTermScheduler();
  ~ShortTermScheduler();

  /* Set-up functions */

  void createReadyQueue();

  void eval(ProcessNode* newProcess);
  void push(ProcessNode* newProcess);
  void terminate(unsigned int& tPID);

  /* Convenience functions */

  void readyQueueSnapshot();
  
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
