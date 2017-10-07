//
//  Printer.cpp
//  Assignment I
//
//  Created by Joseph Sayad on 05/15/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#include "Printer.h"

/* Explicitly-Defined Default Constructor */

Printer::Printer() {}

/* Printer Queue Functions */

void Printer::push(ProcessNode* process) {
  ptrToProcess_.push_back(process);
}

void Printer::pop() {
  if (!ptrToProcess_.empty()) {
    ptrToProcess_.front() = nullptr;
    ptrToProcess_.pop_front();
  } 

  else {
    cout << "\n[os] No process found in PRINTER queue.\n";
  }
}

ProcessNode* Printer::processUsingPrinter() {
  if (!ptrToProcess_.empty()) {
    return ptrToProcess_.front();
  } 

  else {
    return nullptr;
  }
}

bool Printer::isEmpty() {
  return ptrToProcess_.empty();
}

int Printer::size() {
  return ptrToProcess_.size();
}

/* Convenience Function */

void Printer::displayQueue() {
  if(ptrToProcess_.empty()) {
    cout << "PRINTER :: empty\n";
  } 

  else {
    printerQueue::iterator it = ptrToProcess_.begin();
    
    for(auto it2 = ptrToProcess_.begin(); it2 != ptrToProcess_.end(); ++it2) {
      if (it == it2) {
        cout << *(*it2) << " :: USING PRINTER\n";
      } else {
        cout << *(*it2) << " :: WAITING ON PRINTER\n";      
      }
    }
  }  
}
