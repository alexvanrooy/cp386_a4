# CP386 Assignment 4

## Features
###### Question 1
This program implements the bankers algorithm, which is an algorithm that allows different "customers" to request resources and ensures that the system is left in a safe state such that deadlock doesn't occur. 

When the program is first run the number of resources and how much of each resource is present will be initialized, this what the "bank" has available. Following the initalization of the bank's resources, the "customer's" demands will be loaded from reading the file _sample4_in.txt_. 

The program requires that the user enter commands to perform different functions, the commands are as follows:
- RQ
- RL
- Status
- Run
- Exit

###### Question 2

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
