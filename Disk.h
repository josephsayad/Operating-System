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

  /* Explicitly-Defined Default Constructor */

  Disk();

  /* Disk Queue Functions */

  bool isEmpty();
  // Postcondition: Returns 1 if ptrToProcess_ is empty().

  int size();
  // Postcondition: Returns the number of elements ptrToProcess_
  // contains.

  void push(ProcessNode* process);
  // Precondition: Accepts an object that points to a ProcessNode.
  // Postcondition: Pushes the pointer into a doubly linked-list 
  // of ProcessNode pointers.

  void pop();
  // Postcondition: Pops the first pointer of the doubly linked-list 
  // of ProcessNode pointers. An underlying pop_front() method is 
  // used.

  ProcessNode* processUsingDisk();
  // Postcondition: Returns a reference to the first element of 
  // ptrToProcess_.

  /* Convenience Function */

  void displayQueue();
  // Postcondition: Dereferences, and prints contents of ptrToProcess_.
  // Objects of type ProcessNode - that each pointer references - is 
  // printed to console.

  private: 
    
  /* Private Data Members */
  
  diskQueue ptrToProcess_; 
  // Note: List of pointers to objects of type ProcessNode. 
  // Each disk has its own queue.

};

#endif
