//
//  Printer.cpp
//  Assignment I
//
//  Created by Joseph Sayad on 05/11/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#include "Printer.h"

/* Explicitly-defined default constructor */

Printer::Printer() {
  cout << "Printer exists.\n";
}

/* Queue Functions */

void Printer::push(ProcessNode* process) {
  ptrToProcess_.push(process);
}

void Printer::pop() {
  ptrToProcess_.pop();
}

unsigned int& Printer::processUsingPrinter() {
  return (ptrToProcess_.front())->PID; 
}

bool Printer::isEmpty() {
  return ptrToProcess_.empty();
}

int Printer::size() {
  return ptrToProcess_.size();
}

/* Convenience Function */

void Printer::displayQueue() {
  cout << "ptrToProcess contains: ";
  
  while (!ptrToProcess_.empty()) {
    cout << " " << *ptrToProcess_.front();
    ptrToProcess_.pop();
  }
}
