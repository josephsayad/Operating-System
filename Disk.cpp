//
//  Disk.cpp
//  Assignment I
//
//  Created by Joseph Sayad on 05/17/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#include "Disk.h"

/* Explicitly-Defined Default Constructor */

Disk::Disk() {}

/* Disk Queue Functions */

void Disk::push(ProcessNode* process) {
  ptrToProcess_.push_back(process);
}

void Disk::pop() {
  if (!ptrToProcess_.empty()) {
    ptrToProcess_.front() = nullptr;
    ptrToProcess_.pop_front();
  } 

  else {
    cout << "\n[os] No process found in DISK queue.\n";
  }
}

ProcessNode* Disk::processUsingDisk() {
  if (!ptrToProcess_.empty()) {
    return ptrToProcess_.front();
  } 

  else {
    return nullptr;
  }
}

bool Disk::isEmpty() {
  return ptrToProcess_.empty();
}

int Disk::size() {
  return ptrToProcess_.size();
}

/* Convenience Function */

void Disk::displayQueue() {
  if(ptrToProcess_.empty()) {
    cout << "DISK :: empty\n";
  } 

  else {
    diskQueue::iterator it = ptrToProcess_.begin();
    
    for(auto it2 = ptrToProcess_.begin(); it2 != ptrToProcess_.end(); ++it2) {
      if (it == it2) {
        cout << *(*it2) << " :: USING DISK\n";
      } else {
        cout << *(*it2) << " :: WAITING ON DISK\n";      
      }
    }
  }  
}
