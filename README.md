# CP386 Assignment 4

## Features
###### Question 1
This program implements the bankers algorithm, which is an algorithm that allows different "customers" to request resources and ensures that the system is left in a safe state such that deadlock doesn't occur. 

When the program is first ran the number of resources and how much of each resource is available will be initialized, this what the "bank" has available to allocate. Following the initalization of the bank's resources, the "customer's" demands will be loaded from reading the file _sample4_in.txt_. 

The program maintains 4 data structures throughout its runtime:
- **available**: How much of each resource the "bank" has available to offer.
- **maximum**: The maximum of each resouce that each customer needs.
- **allocated**: The amount of each resource that a specific customer is currently allocated.
- **need**: The amound of each resource that the customer still needs (maximum - allocated).

The program requires that the user enter commands to perform different functions, the commands are as follows:
- <RQ [int customer_number] [int Resource 1] [int Resource 2] ... [int Resource n]>: '**RQ**' command is used by the user to request resources for the desired customer. Requests can only be as large as the maximum resources needed for that customer. If the request leaves the system in a safe state then the request will be satisfied, otherwise the request will be denied.
- <RL [int customer_number] [int Resource 1] [int Resource 2] ... [int Resource n]>: ‘**RL**’ command is used to release the desired number of allocated resources from a given customer.
- \<Status\>: ‘**Status**’ command displays each of the data structures that are being maintained (available, maximum, allocated, and need).
-  \<Run\>: ‘**Run**’ command will execute each of the customer's processess in a safe sequence. 
- \<Exit\>: '**Exit**' command will end the programs.

###### Question 2
This program implements contiguous memory allocation using the Best-Fit algorithm. 

When the program is ran, the desired size of the available memory is given. This will represent the max memory available for allocation to each process.

The program maintains a linked list that keeps track of each process, as well as the begining address and the end address of the memory block that it has been allocated.

The program requires that the user input commands to perform the memory allocation, the commands are as follows:
- <RQ [process number] [size] [B]>: '**RQ**' command takes a process number in the form of 'P#', where # is an integer, and a given size, and attempts to find a hole large enough to fit the desired memory block. The 'B' indicates the use of the Best-Fit algorithm for memory allocation. If a hole is found that can fit the desired block then the memory will be allocated, otherwise the request will be denied.
- <RL [process number]>: '**RL**' command takes a given process number, 'P#' where # is an integer, and releases the memory that has been allocated to that process.
- \<Status\>: '**Status**' command displays how much memory is allocated, the blocks of memory and the processes they belong to, the amount of free memory, and finally the holes that have yet to be filled.
- \<Exit\>: '**Exit**' command will end the program.

## Makefile
The makefile provided is used to compile both Question1.c and Question2.c.

To use the makefile: 
1. Add it to the same directory where Question1.c and Question2.c are located.
2. Run the command _make_ (This will compile both Question1.c and Question2.c into executables Question1 and Question2, respectively).
3. To run the executable for Question1 do _make runq1_, this will cause the Question1 program to run with the given input value 10 5 7 8.
4. To run the executable for Question2 do _make runq2_, this will cause the Question2 program to run with the given input value 1000000.
5. Finally, perform _make clean_ to clear the directory of the Question1 and Question2 executables so only the original files before the _make_ will be present.

NOTE: make sure that the file _sample4_in.txt_ is present in the same directory as Question1 as the file is necassary for the program to run.

## Screenshots
###### Question 1
###### Question 2

## Individual Contribution
As I am in a group alone, I was the only contributor to the following programs and wrote all the code myself.

## Test Cases
###### Question 1
###### Question 2

## Use Examples
###### Question 1
###### Question 2

## About Developers
Alexander Van Rooy, Computer Science student studying at Wilfrid Laurier University

## License
