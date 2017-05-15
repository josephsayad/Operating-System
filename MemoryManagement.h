//
//  MemoryManagement.h
//  Assignment I
//
//  Created by Joseph Sayad on 05/13/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#ifndef MEMORYMANAGEMENT_H
#define MEMORYMANAGEMENT_H

#include <iostream>
#include <iomanip>
#include <list>

#include "Node.h"

using namespace std;

typedef list<MemoryNode> ProcessStore;

class MemoryManagement {
  
  public: 

  /* Explicitly-defined default constructor */

  MemoryManagement();
  ~MemoryManagement();

  /* Memory Management Functions */

  void initializeRAM();

  ProcessNode* newProcess(unsigned int& priority, long& size);
  ProcessNode* createPCB(unsigned int& priority, long& size, long& pStartAddress, ProcessStore::iterator& holePos);
  void storeProcessInRAM(MemoryNode& node, ProcessStore::iterator& holePos);
  
  void evalMemory(unsigned int& targetPID);
  void traverseTo(unsigned int& targetPID, ProcessStore::iterator& nodeToRemove);
  void releaseMemory(string& nodeBefore, string& nodeAfter, ProcessStore::iterator& nodeToRemove);

  /* Accessor Functions */

  long getMemoryCapacity() const;

  /* Mutator Functions */

  void setMemoryCapacity(long& initCapacity);

  /* Convenience Functions */

  void memorySnapshot() const;

  private: 

  /* Private Data Members */ 
  
  unsigned int PID_COUNTER;
  long memoryCapacity_;
  ProcessStore RAM_;

  /* Private Data Helpers */ 

  bool findHole(long& processSize, long& pStartAddress, ProcessStore::iterator& holePos);

};

#endif
