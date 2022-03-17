#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>


int *available;
int resource_num;
int **customers;

void readFile(char* file_name);

int main(int argc, char *argv[]){


	//initializes the available array
	resource_num = argc-1;
	available = (int*)malloc((argc - 1) * sizeof(int));

	for(int i = 1 ; i < argc; i++){
		available[i - 1] = atoi(argv[i]);
	}

	for(int i = 0; i < resource_num;i++ ){
		printf("NUMBER: %d\n", available[i]);
	}

	//read the file and populate the customer matrix
	readFile("sample4_in.txt");







	return 0;
}



void readFile(char* file_name){

	FILE *in = fopen(file_name, "r");

	printf("Read File\n");


	return;
}
