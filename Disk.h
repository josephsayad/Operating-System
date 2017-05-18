//
//  Disk.h
//  Assignment I
//
//  Created by Joseph Sayad on 05/17/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#ifndef DISK_H
#define DISK_H

#include <iostream>
#include <list>

#include "Node.h"

using namespace std;

typedef list<ProcessNode*> diskQueue;

class Disk {

  public: 

  /* Explicitly-defined default constructor */

  Disk();

  /* Queue Functions */

  bool isEmpty();
  int size();
  void push(ProcessNode* process);
  void pop();
  ProcessNode* processUsingDisk();

  /* Convenience Function */

  void displayQueue();

  private: 
    
  /* Private Data Members */
  
  diskQueue ptrToProcess_;

};

#endif
