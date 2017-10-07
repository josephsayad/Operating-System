//
//  Printer.h
//  Assignment I
//
//  Created by Joseph Sayad on 05/15/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <list>

#include "Node.h"

using namespace std;

typedef list<ProcessNode*> printerQueue;

class Printer {
  
  public: 

  /* Explicitly-Defined Default Constructor */

  Printer();

  /* Printer Queue Functions */

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

  ProcessNode* processUsingPrinter();
  // Postcondition: Returns a reference to the first element of 
  // ptrToProcess_.

  /* Convenience Function */

  void displayQueue();
  // Postcondition: Dereferences, and prints contents of ptrToProcess_.
  // Objects of type ProcessNode - that each pointer references - is 
  // printed to console.

  private: 
    
  /* Private Data Members */
  
  printerQueue ptrToProcess_;
  // Note: List of pointers to objects of type ProcessNode. 
  // Each printer has its own queue.

};

#endif
