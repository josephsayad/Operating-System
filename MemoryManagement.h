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

  /* Explicitly-Defined Default Constructor */

  MemoryManagement();

  /* Explicitly-Defined Default Destructor */

  ~MemoryManagement();

  /* Memory Management Functions */

  void initializeRAM();
  //  Postcondition: instantiates a MemoryNode starter node to RAM_, which
  //  is of type "HOLE" in the onset of the program. If the user enters a
  //  value such as 4 billon, the MemoryNode of type "HOLE" will have a 
  //  start of 0 and end of 3999999999.

  ProcessNode* newProcess(unsigned int& priority, long& size);
  //  Precondition: Requires an object of type unsigned int by reference,
  //  and an object of type long by reference.
  //  Postcondition: Returns a pointer to an object of type ProcessNode.
  //  If there is available memory to allocate for a new process - returns
  //  nullptr.

  ProcessNode* createPCB(unsigned int& priority, long& size, long& pStartAddress, ProcessStore::iterator& holePos);
  //  Precondition: Requires an object of type unsigned int by reference,
  //  two objects of type long by reference, and an iterator of type ProcessStore 
  //  by reference. 
  //  Postcondition: Declares and instantiates ProcessNode and MemoryNode objects.
  //  Then, storeProcessInRAM is invoked with MemoryNode and position of the hole 
  //  as parameters.

  void storeProcessInRAM(MemoryNode& node, ProcessStore::iterator& holePos);
  //  Precondition: Requires an object of type MemoryNode by reference, and an 
  //  iterator of type ProcessStore by reference. 
  //  Postcondition: Inserts a process into RAM_ and triggers a conditional based
  //  on the size of the process.
  
  void evalMemory(unsigned int& targetPID);
  //  Precondition: Requires an object of type unsigned int by reference. 
  //  Postcondition: Traverses to the MemoryNode with the targetPID, and 
  //  may set before and/or after local variables to null depending on
  //  the case of termination. releaseMemory is then invoked with after and
  //  before as arguments to the function.

  void traverseTo(unsigned int& targetPID, ProcessStore::iterator& nodeToRemove);
  //  Precondition: Requires an object of type unsigned int by reference, and a
  //  ProcessStore iterator by reference.
  //  Postcondition: the nodeToRemove iterator points to the process that is to 
  //  be terminated - process using the CPU.

  void releaseMemory(string& nodeBefore, string& nodeAfter, ProcessStore::iterator& nodeToRemove);
  //  Precondition: Requires two objects of type string by reference, and a ProcessStore 
  //  iterator by reference.
  //  Postcondition: Removes MemoryNode (process sitting in RAM) and adjusts RAM in a way
  //  that depends on the 4 cases defined in CPP file.

  /* Accessor Functions */

  long getMemoryCapacity() const;
  //  Postcondition: returns an object of type long which represents the memory capacity 
  //  of RAM.

  /* Mutator Functions */

  void setMemoryCapacity(long& initCapacity);
  //  Precondition: Requires an object of type long by reference.
  //  Postcondition: Sets memoryCapacity_ to a value of type long by reference.

  /* Convenience Functions */

  void memorySnapshot() const;
  //  Postcondition: Prints snapshot of RAM to console.

  private: 

  /* Private Data Members */ 
  
  unsigned int PID_COUNTER;
  long memoryCapacity_;
  ProcessStore RAM_;

  /* Private Data Helpers */ 

  bool findHole(long& processSize, long& pStartAddress, ProcessStore::iterator& holePos);
  //  Precondition: Requires two objects of type long by reference, and a ProcessStore 
  //  iterator by reference.
  //  Traverses a doubly-linked list of MemoryNode objects, and returns true if a hole 
  //  (larger or equal to the size of the process) is found.

};

#endif
