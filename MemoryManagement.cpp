//
//  MemoryManagement.h
//  Assignment I
//
//  Created by Joseph Sayad on 05/13/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#include "MemoryManagement.h"

/* Explicitly-Defined Default Constructor */

MemoryManagement::MemoryManagement() : PID_COUNTER(1) {}

/* Explicitly-Defined Default Destructor */

MemoryManagement::~MemoryManagement() {}

/* Memory Management Functions */

void MemoryManagement::initializeRAM() {
  long start = 0;
  long end = memoryCapacity_ - 1;
  long size = memoryCapacity_;
  string type = "HOLE";

  MemoryNode *starterNode = new MemoryNode(start, end, size, type);
  RAM_.push_front(*starterNode);
}

ProcessNode* MemoryManagement::newProcess(unsigned int& priority, long& size) {
  long pStartAddress = -1;
  ProcessStore::iterator holePos;

  /* First-fit Algorithm Implemented in findHole method */

  // If hole found...
  if (findHole(size, pStartAddress, holePos)) {
    // Create PCB and allocate memory and return pointer to process in ready-queue.
    return (createPCB(priority, size, pStartAddress, holePos));
  } 

  // Else error handle...
  else {
    cout << "[memory manager] No memory capacity for process of size " << size << ". Try 't' for more space.\n";
    ProcessNode* nullP = nullptr;
    return nullP;
  }
}

ProcessNode* MemoryManagement::createPCB(unsigned int& priority, long& size, long& start, ProcessStore::iterator& holePos) {
  string type = "PROCESS";
  long end = (start + size) - 1;

  /* Handle Process in Memory */

  MemoryNode *node = new MemoryNode(start, end, size, type);
  node->setPID(PID_COUNTER);

  /* Handle Process in Ready-Queue */

  ProcessNode *process = new ProcessNode(PID_COUNTER, priority, size);

  ++PID_COUNTER; // increment for next process
  
  storeProcessInRAM(*node, holePos);

  return process;
}

void MemoryManagement::storeProcessInRAM(MemoryNode& node, ProcessStore::iterator& holePos) {
  RAM_.insert(holePos, node); // Insert memory node

  /* If process is the same size as hole, remove hole */

  if (holePos->sizeInBytes == node.sizeInBytes) {
    RAM_.erase(holePos);
  }

  /* If process is smaller than the hole, adjust size and start of hole */
  
  else {
    holePos->sizeInBytes -= node.sizeInBytes;
    holePos->startAddress = ++node.endAddress;
  }
}

/***************************************************
 * Note: Terminating processes & Memory Release
 ***************************************************
 * Evaluation of the memory location of process is 
 * necessary before releasing it from memory via: 
 * 't'. There are four cases when deleting a MemoryNode,
 * which represent processes in RAM: 
 *
 * CASE 1: FIRST PROCESS IN RAM
 * CASE 2: LAST PROCESS IN RAM
 * CASE 3: 1 PROCESS IN RAM, NO HOLES
 * CASE 4: PROCESS IN THE MIDDLE OF RAM
 */

void MemoryManagement::evalMemory(unsigned int& targetPID) {
  ProcessStore::iterator nodeToRemove;
  traverseTo(targetPID, nodeToRemove); 

  string before;
  string after;

  /* CASE 1 */

  // If process to terminate is at the beginning of RAM_,
  // and there is more than 1 MemoryNode in RAM_...

  if (nodeToRemove == RAM_.begin() && RAM_.size() >= 2) {
    
    // (1) No MemoryNode before the nodeToRemove.
    before = "null";

    // (2) Get the type of node after the nodeToRemove.
    nodeToRemove++;
    after = nodeToRemove->typeOf;

    // (3) Point at the nodeToRemove.
    nodeToRemove--;
  } 

  /* CASE 2 */

  // If process to terminate is at the end of RAM_,
  // and there is more than 1 MemoryNode in RAM_...

  else if (*nodeToRemove == RAM_.back() && RAM_.size() >= 2) { 

    // (1) No MemoryNode after the nodeToRemove.
    after = "null"; 

    // (2) Get the type of node before the nodeToRemove.
    nodeToRemove--;
    before = nodeToRemove->typeOf;

    // (3) Point at the nodeToRemove.
    nodeToRemove++;
  }

  /* CASE 3 */

  // If there is only 1 process that takes the entirety of 
  // RAM_...

  else if (nodeToRemove == RAM_.begin() && RAM_.size() >= 1) {
    
    // (1) No MemoryNode after and before the nodeToRemove.
    before = "null";
    after = "null";
  }

  /* CASE 4 */

  // If the process is found in the middle of RAM_

  else {
   
    // (1) Get the type of node before the nodeToRemove.
    nodeToRemove--;
    before = nodeToRemove->typeOf;

    // (2) Get the type of node after the nodeToRemove.
    nodeToRemove++;
    nodeToRemove++;
    after = nodeToRemove->typeOf;

    // (3) Point at the nodeToRemove.
    nodeToRemove--;
  }

  releaseMemory(before, after, nodeToRemove);
}

void MemoryManagement::traverseTo(unsigned int& targetPID, ProcessStore::iterator& nodeToRemove) {
  for (auto it = RAM_.begin(); it != RAM_.end(); ++it) {
    if (it->typeOf == "HOLE") { /* Skip */ }
    
    else if (it->typeOf == "PROCESS" && it->PID == targetPID) {
      nodeToRemove = it;
    }
  }
}

void MemoryManagement::releaseMemory(string& nodeBefore, string& nodeAfter, ProcessStore::iterator& nodeToRemove) {
  long memoryAddBack = 0;

  /* Terminating a process that sits at the start of RAM */

  if (nodeBefore == "null" && nodeAfter != "null") {
    if (nodeAfter == "PROCESS") {
      nodeToRemove->PID = -1; 
      nodeToRemove->typeOf = "HOLE";

      // No memoryAddBack - not merging holes.    
    }

    else if (nodeAfter == "HOLE") {
      long newStart = nodeToRemove->startAddress;
      memoryAddBack = nodeToRemove->sizeInBytes;

      nodeToRemove = RAM_.erase(nodeToRemove);
      nodeToRemove->startAddress = newStart;
      nodeToRemove->sizeInBytes += memoryAddBack;
    }
  }

  /* Terminating a process that sits at the end of RAM */

  else if (nodeBefore != "null" && nodeAfter == "null") {
    if (nodeBefore == "PROCESS") {
      nodeToRemove->PID = -1; 
      nodeToRemove->typeOf = "HOLE";
    }

    else if (nodeBefore == "HOLE") {
      long newEnd = nodeToRemove->endAddress;
      memoryAddBack = nodeToRemove->sizeInBytes;

      nodeToRemove = RAM_.erase(nodeToRemove);

      nodeToRemove--; // iterate to hole

      /* Adjust Hole Size & End Address */

      nodeToRemove->endAddress = newEnd;
      nodeToRemove->sizeInBytes += memoryAddBack;
    }
  }

  /* Terminating a process that occupies all of RAM */

  else if (nodeBefore == "null" && nodeAfter == "null") {
    nodeToRemove->PID = -1; 
    nodeToRemove->typeOf = "HOLE";

    // No memoryAddBack - no difference taken when storing process.
  }

  /* Terminating a process that sits in the middle of RAM */

  else {

    if (nodeBefore == "PROCESS" && nodeAfter == "PROCESS") {
      nodeToRemove->PID = -1; 
      nodeToRemove->typeOf = "HOLE";

      // No memoryAddBack - not merging holes.
    }

    else if (nodeBefore == "PROCESS" && nodeAfter == "HOLE") {
      long newStart = nodeToRemove->startAddress;
      memoryAddBack = nodeToRemove->sizeInBytes;

      nodeToRemove = RAM_.erase(nodeToRemove);

      nodeToRemove->startAddress = newStart;
      nodeToRemove->sizeInBytes += memoryAddBack;
    }

    else if (nodeBefore == "HOLE" && nodeAfter == "PROCESS") {
      long newEnd = nodeToRemove->endAddress;
      memoryAddBack = nodeToRemove->sizeInBytes;
      
      nodeToRemove = RAM_.erase(nodeToRemove);
      
      nodeToRemove--;

      nodeToRemove->endAddress = newEnd;
      nodeToRemove->sizeInBytes += memoryAddBack;
    }

    else if (nodeBefore == "HOLE" && nodeAfter == "HOLE") {
      nodeToRemove--;
      
      /* Point to first of three holes */

      long newStart = nodeToRemove->startAddress; // record start position
      memoryAddBack = nodeToRemove->sizeInBytes; // record hole size 
      nodeToRemove = RAM_.erase(nodeToRemove); // erase first hole
      
      /* Point to second of three holes */    
      
      memoryAddBack += nodeToRemove->sizeInBytes; // add to hole size
      nodeToRemove = RAM_.erase(nodeToRemove); // erase second hole

      /* Point to third of three holes */    
      
      nodeToRemove->startAddress = newStart; // set new starting address 
      nodeToRemove->sizeInBytes += memoryAddBack; // add back lost space
    }
  }
}

/* Accessor Functions */

long MemoryManagement::getMemoryCapacity() const { return memoryCapacity_; }

/* Mutator Functions */

void MemoryManagement::setMemoryCapacity(long& initCapacity) {
  memoryCapacity_ = initCapacity;
}

/* Convenience Functions */

void MemoryManagement::memorySnapshot() const {
  cout << "\n";
  cout << setfill('-') << setw(56) << " ";
  cout << "\n|";

  cout << setfill(' ') <<  right << setw(27) << "RAM";
  cout << setfill(' ') << setw(28) << "|\n";
  cout << setfill('-') << setw(56) << " ";
  cout << "\n";
  
  cout << setfill(' ') << left << setw(15) << "Type";
  cout << setfill(' ') <<  right << setw(15) << "Start [B]";
  cout << setfill(' ') <<  right << setw(18) << "End [B]";
  cout << "\n";

  for (auto it = RAM_.begin(); it != RAM_.end(); ++it) {
    cout << *it << "\n";
  }

  cout << setfill('-') << setw(56) << " ";
  cout << "\n\n";
}

/* Private Data Helpers */ 

bool MemoryManagement::findHole(long& processSize, long& pStartAddress, ProcessStore::iterator& holePos) {
  
  // Traverse list of MemoryNode objects:  
  for (auto it = RAM_.begin(); it != RAM_.end(); ++it) {
    
    // If MemoryNode object is of type "HOLE"...
    if (it->typeOf == "HOLE") {

      // If process size is less than or eqaul to hole size...      
      if (processSize <= it->sizeInBytes) {
        pStartAddress = it->startAddress;
        holePos = it; // occupy hole

        return true; // Hole found.
      } 
    } 

    else if (it->typeOf == "PROCESS") {}
  }

  return false; // Hole not found.
}
