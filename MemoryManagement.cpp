//
//  MemoryManagement.h
//  Assignment I
//
//  Created by Joseph Sayad on 05/13/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#include "MemoryManagement.h"

/* Explicitly-defined default constructor */

MemoryManagement::MemoryManagement() : PID_COUNTER(1) {}

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

  if (findHole(size, pStartAddress, holePos)) {
    return (createPCB(priority, size, pStartAddress, holePos));
  } else {
    cout << "[memory manager] Memory capacity has been met. Use 't' to terminate processes, and free up space.\n";
    
    ProcessNode* nullP = nullptr; // is this ok?
    return nullP;
  }
}

ProcessNode* MemoryManagement::createPCB(unsigned int& priority, long& size, long& start, ProcessStore::iterator& holePos) {
  string type = "PROCESS";
  long end = (start + size) - 1;

  MemoryNode *node = new MemoryNode(start, end, size, type);
  node->setPID(PID_COUNTER);

  ProcessNode *process = new ProcessNode(PID_COUNTER, priority, size);

  ++PID_COUNTER;
  
  storeProcessInRAM(*node, holePos);
  return process;
}

void MemoryManagement::storeProcessInRAM(MemoryNode& node, ProcessStore::iterator& holePos) {
  RAM_.insert(holePos, node);

  /* If process is the same size as hole. */

  if (holePos->sizeInBytes == node.sizeInBytes) {
    RAM_.erase(holePos);
  }

  /* If process size is smaller than the hole. */
  
  else {
    holePos->sizeInBytes -= node.sizeInBytes;
    holePos->startAddress = ++node.endAddress;
  }

  memorySnapshot();
}

void MemoryManagement::evalMemory(unsigned int& targetPID) {
  ProcessStore::iterator nodeToRemove;
  traverseTo(targetPID, nodeToRemove); 

  string before;
  string after;

  // first node in RAM
  if (nodeToRemove == RAM_.begin() && RAM_.size() >= 2) {
    before = "null";

    nodeToRemove++;
    after = nodeToRemove->typeOf;

    nodeToRemove--; // Iterator points to node to deallocate from RAM.
    cout << "HELLOONE!\n";
  } 

  // last node in RAM
  else if (*nodeToRemove == RAM_.back() && RAM_.size() >= 2) { 
    after = "null"; 

    nodeToRemove--;
    before = nodeToRemove->typeOf;

    nodeToRemove++; // Iterator points to node to deallocate from RAM.
    cout << "HELLOFOUR!\n";
  }

  // 1 process node in ram, 0 holes 
  else if (nodeToRemove == RAM_.begin() && RAM_.size() >= 1) {
    before = "null";
    after = "null";

    cout << "HELLOTWO\n";
  }

  // middle node in RAM
  else {
    nodeToRemove--;
    before = nodeToRemove->typeOf;

    nodeToRemove++;
    nodeToRemove++;
    after = nodeToRemove->typeOf;
    nodeToRemove--; // Iterator points to node to deallocate from RAM.

    cout << "HELLOTHREE\n";
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

  /* TERMINATING A PROCESS THAT OCCUPIES START OF RAM */

  if (nodeBefore == "null" && nodeAfter != "null") {
    if (nodeAfter == "PROCESS") {
      nodeToRemove->PID = -1; 
      nodeToRemove->typeOf = "HOLE";

      /* No memoryAddBack - not merging holes */    
    }

    else if (nodeAfter == "HOLE") {
      long newStart = nodeToRemove->startAddress;
      memoryAddBack = nodeToRemove->sizeInBytes;

      nodeToRemove = RAM_.erase(nodeToRemove);
      nodeToRemove->startAddress = newStart;
      nodeToRemove->sizeInBytes += memoryAddBack;
    }
  }

  /* TERMINATING A PROCESS THAT OCCUPIES END OF RAM */

  else if (nodeBefore != "null" && nodeAfter == "null") {
    if (nodeBefore == "PROCESS") {
      nodeToRemove->PID = -1; 
      nodeToRemove->typeOf = "HOLE";
    }

    else if (nodeBefore == "HOLE") {
      long newEnd = nodeToRemove->endAddress;
      memoryAddBack = nodeToRemove->sizeInBytes;
     
      nodeToRemove = RAM_.erase(nodeToRemove);
      nodeToRemove->endAddress = newEnd;
      nodeToRemove->sizeInBytes += memoryAddBack;    
    }
  }

  /* TERMINATING A PROCESS THAT OCCUPIES THE WHOLE OF RAM */

  else if (nodeBefore == "null" && nodeAfter == "null") {
    nodeToRemove->PID = -1; 
    nodeToRemove->typeOf = "HOLE";

    /* No memoryAddBack - no difference taken when storing process */
  }

  /* TERMINATING A PROCESS THAT OCCUPIES MIDDLE OF RAM */

  else {

    if (nodeBefore == "PROCESS" && nodeAfter == "PROCESS") {
      nodeToRemove->PID = -1; 
      nodeToRemove->typeOf = "HOLE";

      /* No memoryAddBack - not merging holes */ 
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

  memorySnapshot();
}

/* Accessor Functions */

long MemoryManagement::getMemoryCapacity() const { return memoryCapacity_; }

/* Mutator Functions */

void MemoryManagement::setMemoryCapacity(long& initCapacity) {
  memoryCapacity_ = initCapacity;
}

/* Convenience Functions */

void MemoryManagement::memorySnapshot() const {
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
  cout << "\n";
}

/* Private Data Helpers */ 

bool MemoryManagement::findHole(long& processSize, long& pStartAddress, ProcessStore::iterator& holePos) {
  for (auto it = RAM_.begin(); it != RAM_.end(); ++it) {
    
    if (it->typeOf == "HOLE") {

      // cout << "FOR LAST ENTRY PAY ATTENTION: " << processSize << " is requested!" << endl;
      // cout << "FOR LAST ENTRY PAY ATTENTION: " << it->sizeInBytes << " available!" << endl;
      
      if (processSize <= it->sizeInBytes) {
        pStartAddress = it->startAddress;
        holePos = it; 

        return true; 
      } 
    } 

    else if (it->typeOf == "PROCESS") {}
  }

  return false;
}
