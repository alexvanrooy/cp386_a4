# CP386 Assignment 4 - Banker's Algorithm & Contiguous Memory Allocation

## Features
###### Question1.c
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

###### Question2.c
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

## Use Examples
###### Question1.c
For each of these examples assume there are 4 unique resources in the system

Requesting 1 of each resource for customer 0:
> RQ 0 1 1 1 1

Releasing some of the resources allocated to customer 0:
> RL 0 1 0 0 1

###### Question2.c
Requesting a contiguous block of memory for process P0 with a size of 10000 bytes using Best-Fit algorithm:
> RQ P0 10000 B

Releasing the memory block allocated to process P0:
> RL P0

## Screenshots
###### Question1.c
When the program is first executed:
>![image](https://user-images.githubusercontent.com/96751896/160735890-34abc80f-dc35-4c85-b958-e4debad53319.png)

Requesting resouces for some of the customers:
>![image](https://user-images.githubusercontent.com/96751896/160736147-28ec4e5c-1c8b-47cd-83c1-1bb914f468d7.png)

Releasing some of the resources allocated to the customers:
>![image](https://user-images.githubusercontent.com/96751896/160736444-0ec39a48-a574-4ad1-8d3c-531800d9840b.png)

Checking the status of the system:
>![image](https://user-images.githubusercontent.com/96751896/160736744-b0d7c3b7-f315-4a06-97ad-6c3d61aeb853.png)

Running the safe sequence:
>![image](https://user-images.githubusercontent.com/96751896/160736811-017c6273-a7a2-4481-8133-cb98ff796aab.png)

>![image](https://user-images.githubusercontent.com/96751896/160736930-849a44b9-2799-4d63-9a39-e48d36bc94ff.png)

###### Question2.c
When the program is first executed:
>![image](https://user-images.githubusercontent.com/96751896/160737405-161f5710-5ec2-4438-b770-e47e6c784a37.png)

Requesting blocks of memory for different processes:
>![image](https://user-images.githubusercontent.com/96751896/160737726-5623da75-555e-48bc-a147-b289ded7fc19.png)

Releasing a processes' block of memory:
>![image](https://user-images.githubusercontent.com/96751896/160737846-c78b8cf1-cd8e-4545-bec8-dfaa9e150dd8.png)

Reporting the regions of allocated memory and free memory:
>![image](https://user-images.githubusercontent.com/96751896/160737947-4f14974d-b909-47e3-af58-950fcdf99c1a.png)

## Individual Contribution
As I am working alone, I was the only contributor to the following programs and wrote all the code myself.

## About Developers
Alexander Van Rooy, Computer Science student studying at Wilfrid Laurier University

## License

MIT License

Copyright (c) 2022 Alexander Van Rooy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
