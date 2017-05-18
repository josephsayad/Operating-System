//
//  ShortTermScheduler.cpp
//  Project 1
//
//  Created by Joseph Sayad on 05/11/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#include "ShortTermScheduler.h"

/* Explicitly-defined default constructor */

ShortTermScheduler::ShortTermScheduler() : processUsingCPU_(nullptr) {
  createReadyQueue();
}

ShortTermScheduler::~ShortTermScheduler() {}

/* Set-up functions */

void ShortTermScheduler::createReadyQueue() {
  readyQueue_.push_back(zero_);
  readyQueue_.push_back(one_);
  readyQueue_.push_back(two_);
  readyQueue_.push_back(three_);
  readyQueue_.push_back(four_);
}

void ShortTermScheduler::eval(ProcessNode* newProcess) {
  if (processUsingCPU_ == nullptr) { processUsingCPU_ = newProcess; }

  else if (processUsingCPU_ != nullptr && newProcess->priority > processUsingCPU_->priority) {
     ProcessNode *tmp = processUsingCPU_;
     processUsingCPU_ = newProcess;
     newProcess = tmp;

     push(newProcess);
  }

  else if (processUsingCPU_ != nullptr && newProcess->priority <= processUsingCPU_->priority) {
    push(newProcess);
  }
}

void ShortTermScheduler::push(ProcessNode* process) {
  if (process->priority == 0) {
    readyQueue_.at(0).push_back(process);
  } 

  else if (process->priority == 1) {
    readyQueue_.at(1).push_back(process);
  } 

  else if (process->priority == 2) {
    readyQueue_.at(2).push_back(process);
  } 

  else if (process->priority == 3) {
    readyQueue_.at(3).push_back(process);
  } 

  else if (process->priority == 4) {
    readyQueue_.at(4).push_back(process);
  } 

  else {
    cout << "Error: invalid process priority...\n";
    exit(1);
  }
}

void ShortTermScheduler::terminate(unsigned int& tPID) {
  if (processUsingCPU_ == nullptr) {
    cout << "[scheduler] CPU is not in use. Use 'A' to create a process.\n";
  }

  else if (processUsingCPU_ != nullptr) {
    /* Delete contents of terminated process and 
     * set pointer to null.
    */
    
    tPID = processUsingCPU_->PID;
    delete processUsingCPU_;
    processUsingCPU_ = nullptr;


    for (int i = readyQueue_.size() - 1; i >= 0; --i) {
      if (!readyQueue_.at(i).empty()) {

        /* Point to new content.
         * Set pointer in queue to null.
         * Pop dangling pointer.
         */

        processUsingCPU_ = readyQueue_.at(i).front();
        readyQueue_.at(i).front() = nullptr;
        readyQueue_.at(i).pop_front();
        break;
      }
    }
  }
}

/* IO QUEUE FUNCTIONS START */

ProcessNode* ShortTermScheduler::toIODevice() {
  ProcessNode *tmp = nullptr;

  if (processUsingCPU_ == nullptr) {
    cout << "[scheduler] CPU is not in use. Use 'A' to create a process.\n";
  }

  else if (processUsingCPU_ != nullptr) {
    
    /* Delete contents of terminated process and 
     * set pointer to null.
    */
    
    tmp = processUsingCPU_; 
    processUsingCPU_ = nullptr;

    for (int i = readyQueue_.size() - 1; i >= 0; --i) {
      if (!readyQueue_.at(i).empty()) {

        /* Point to new content.
         * Set pointer in queue to null.
         * Pop dangling pointer.
         */

        processUsingCPU_ = readyQueue_.at(i).front();
        readyQueue_.at(i).front() = nullptr;
        readyQueue_.at(i).pop_front();
        break;
      }
    }
  }

  return tmp;
}

/* IO QUEUE FUNCTIONS END */

/* Convenience functions */

void ShortTermScheduler::readyQueueSnapshot() {
  cout << "\n";

  if (processUsingCPU_ != nullptr) { 

    int localPID = processUsingCPU_->PID;

    cout << setfill('-') << setw(56) << " ";
    cout << "\n|";

    cout << setfill(' ') <<  right << setw(28) << "CPU :: P" << localPID;
    cout << setfill(' ') << setw(26) << "|\n";
    cout << setfill('-') << setw(56) << " ";
    cout << "\n";
  }

  else {
    cout << setfill('-') << setw(56) << " ";
    cout << "\n|";

    cout << setfill(' ') <<  right << setw(30) << "CPU :: empty";
    cout << setfill(' ') << setw(25) << "|\n";
    cout << setfill('-') << setw(56) << " ";
    cout << "\n";    
  }

  for (int i = readyQueue_.size() - 1; i >= 0; --i) {
  	cout << "Level " << i << " :: ";

    for (auto it = readyQueue_.at(i).begin(); it != readyQueue_.at(i).end(); ++it) {
      cout << "P" << (*it)->PID << " <- ";
    } cout << "[end of list]";

  	if (i != 0) { cout << "\n|\n"; }
  	else { cout << "\n"; }
  }

  cout << "\n";
}
