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

  /* Explicitly-defined default constructor */

  Printer();

  /* Queue Functions */

  bool isEmpty();
  int size();
  void push(ProcessNode* process);
  void pop();
  ProcessNode* processUsingPrinter();

  /* Convenience Function */

  void displayQueue();

  private: 
    
  /* Private Data Members */
  
  printerQueue ptrToProcess_;

};

#endif
