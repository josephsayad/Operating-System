//
//  Printer.h
//  Assignment I
//
//  Created by Joseph Sayad on 05/11/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <queue>

#include "Node.h"

using namespace std;

typedef queue<ProcessNode*> printerQueue;

class Printer {
  
  public: 

  /* Explicitly-defined default constructor */

  Printer();

  /* Queue Functions */

  bool isEmpty();
  int size();
  void push(ProcessNode* process);
  void pop();
  unsigned int& processUsingPrinter();

  /* Convenience Function */

  void displayQueue();

  private: 
    
  /* Private Data Members */
  
  printerQueue ptrToProcess_;

};

#endif
