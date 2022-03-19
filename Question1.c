#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>


int *available;
int resource_num;
int customer_num;
int** test;


int** readFile(char* file_name);

int main(int argc, char *argv[]){


	//initializes the available array
	resource_num = argc-1;
	available = (int*)malloc((argc - 1) * sizeof(int));

	for(int i = 1 ; i < argc; i++){
		available[i - 1] = atoi(argv[i]);
	}


	//read the file and populate the customer matrix
	test = readFile("sample4_in.txt");


	//outputs the avaialble resources to the user
	printf("Number of Customers: %d\n", customer_num);
	printf("Currently Available resources:");

	for(int i = 0; i < resource_num; i++){
		printf(" %d",available[i]);
	}
	printf("\n");


	printf("Maximum resources from file:\n");


	for(int i = 0; i < customer_num; i++){
		for(int j = 0; j < resource_num - 1; j++){
			printf("%d ", test[i][j]);
		}
		printf("\n");

	}

	//main loop that asks user to enter command and executes requests






	return 0;
}



int** readFile(char* file_name){

	FILE *in = fopen(file_name, "r");


	//counts how many customers there are
	int customers = 0;

	while(!feof(in)){

		char str[256];
		fscanf(in, "%s", str);		//reads a line in the file
		customers++;

	}

	customer_num = customers;

	int** customer_array = malloc(sizeof(int*) * customers);

	for(int i = 0;  i < customers; i++){
		customer_array[i] = malloc(sizeof(int) * resource_num);
	}

	rewind(in);

	int current_customer = 0;

	while(!feof(in)){

		char str[256];
		fscanf(in, "%s", str);		//reads a line in the file

		char* token;
		token = strtok(str, ",");

		int current_resource = 0;
		while(token != NULL){


			customer_array[current_customer][current_resource] = atoi(token);
			//printf("%s\n",token);
			token = strtok(NULL, ",");
			current_resource++;
		}

		current_customer++;

	}

	return customer_array;
}
