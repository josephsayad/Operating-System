//
//  Node.h
//  Project 1
//
//  Created by Joseph Sayad on 05/10/17.
//  Copyright © 2016 Joseph Sayad. All rights reserved.
//

#ifndef NODE_H
#define NODE_H

#include <string>
#include <iomanip>

using namespace std;

/***************************************************
 * Note: Ready-Queue
 ***************************************************
 * The ready-queue for CPU use is a multi-level queue,
 * which is represented by a vector of doubly linked 
 * lists. The lists serves as a data container for 
 * pointers that reference objects of type ProcessNode.
 * ProcessNode is a struct that represents processes in
 * in the ready-queue. *****************************
 */

struct ProcessNode {

  /* Public Data Members */
 
  unsigned int PID; 
  unsigned int priority;
  long sizeInBytes;

  /* Overloading the Default Constructor */
  
  ProcessNode(const unsigned int& init_PID, const unsigned int& init_priority, const long& init_size) 
    : PID(init_PID), priority(init_priority), sizeInBytes(init_size) {}

  /* Overloading the operator<< */
  
  friend std::ostream& operator<<(std::ostream& out, const ProcessNode& process) {
    // out << "Process " << process.PID << " has been created with priority " << process.priority;
    out << "P" << process.PID;
    return out;
  }
}; 

/***************************************************
 * Note: Initialize RAM
 ***************************************************
 * RAM is represented by a list of memory nodes of
 * type: "PROCESS" or "HOLE." When initializing the 
 * list of MemoryNode objects, we create a starter
 * node of type "HOLE." This represents free space 
 * available in RAM. MemoryNode is a struct that 
 * represents processes in RAM. ********************
 */

struct MemoryNode {

  /* Public Data Members */
 
  unsigned int PID;
  long startAddress; 
  long endAddress;
  long sizeInBytes;
  
  std::string typeOf;

  /* Overloading the Default Constructor */
  
  MemoryNode(long& init_start, long& init_end, const long& init_size, std::string& init_type) 
    : PID(-1), startAddress(init_start), endAddress(init_end), sizeInBytes(init_size), typeOf(init_type) {}

  void setPID(unsigned int& ID) { PID = ID; }

  /* Overloading the operator<< */
  
  friend std::ostream& operator<<(std::ostream& out, const MemoryNode& node) {
    if (node.PID == -1) {
      out << setfill(' ') << left << setw(15) << node.typeOf;
    }

    else {
      std::string PID = "PROCESS " + to_string(node.PID);
      out << setfill(' ') << left << setw(15) << PID;
    }

    out << setfill(' ') <<  right << setw(15) << node.startAddress;
    out << setfill(' ') <<  right << setw(18) << node.endAddress;

    return out;
  }

  /* Overloading the operator== */

  friend bool operator==(const MemoryNode& node, const MemoryNode& nodeToCompare) {
    return node.PID == nodeToCompare.PID;
  }

};

#endif
