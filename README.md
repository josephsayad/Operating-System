# Programming Assignment: Simulate OS 

## About the Project

Write a program that simulates some aspects of an operating system. The simulation will be based upon text inputs the program receives from a user.

## Project Design

### Memory

Memory Managment



### Scheduling

Short Term Scheduler

To simulate multilevel scheduling, where a FCFS algorithm is used in each level, the program will use a vector of linked lists. 

The data structure to use for the priority levels is a vector: it allows for accessing a level in O(1) time. 

A FIFO abstract data type - such as a queue - would be a good choice to hold processes of a distinct priority. However, when issued the [S r] command, we will need to iterate over the processes. Instead, we'll use a linked list. Iterating over one level is O(N) time. Insertion and termination of process is of O(1) time complexity if: we use the C++ std::list. An iterator to the last element allows constant time adding of processes. 

### IO Devices 

Pushing from CPU to Printer

Step 1: Request that scheduler returns process currently using CPU.
Step 2: Push process to one of the N printers.

## How To Compile the Program

### Expected execution structure

The resulting program will compile, and execute via the following commands:

	make all
	./SimulateOS
