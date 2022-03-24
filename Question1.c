#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>

#define FALSE 0
#define TRUE 1


int *available;
int** maximum;		//maximum demand of each customer
int** allocated;
int** need;

int resource_num;  //number of unique resources initialized when program starts
int customer_num;	//how many customers there are


int** readFile(char* file_name);
char* readUserInput();
void calculateNeed();
void statusCommand();
int safeState();

int main(int argc, char *argv[]){


	//initializes the available array
	resource_num = argc-1;


	available = (int*)malloc((argc - 1) * sizeof(int));

	for(int i = 1 ; i < argc; i++){
		available[i - 1] = atoi(argv[i]);
	}


	//read the file and populate the customer matrix
	maximum = readFile("sample4_in.txt");

	//initialize allocated matrix with values of 0
	allocated = malloc(sizeof(int*) * customer_num);

	for(int i = 0;  i < customer_num; i++){
		allocated[i] = malloc(sizeof(int) * resource_num);
	}

	for(int i = 0; i < customer_num; i++){
		for(int j = 0; j < resource_num; j++){
			allocated[i][j] = 0;
		}
	}

	//initialize need matrix
	need = malloc(sizeof(int*) * customer_num);

	for(int i = 0;  i < customer_num; i++){
		need[i] = malloc(sizeof(int) * resource_num);
	}



	//outputs the avaialble resources to the user
	printf("Number of Customers: %d\n", customer_num);
	printf("Currently Available resources:");

	for(int i = 0; i < resource_num; i++){
		printf(" %d",available[i]);
	}
	printf("\n");


	printf("Maximum resources from file:\n");


	for(int i = 0; i < customer_num; i++){
		for(int j = 0; j < resource_num; j++){
			printf("%d ", maximum[i][j]);
		}
		printf("\n");

	}

	calculateNeed();

	//main loop that asks user to enter command and executes requests

	while(1){
		printf("Enter Command: ");


		char* token;
		char* user_command = readUserInput();
		token = strtok(user_command," ");

		if(strcmp(user_command, "Exit") == 0){
			break;
		}
		else if(strcmp(token, "RQ") == 0){
			printf("RQ\n");
		}
		else if(strcmp(token, "RL") == 0){
			printf("RL\n");
		}
		else if(strcmp(user_command, "Status") == 0){
			printf("Status\n");
			statusCommand();
		}
		else if(strcmp(user_command, "Run") == 0){
			printf("Run\n");
			int is_safe = safeState();
			if(is_safe == FALSE){
				printf("state is not safe\n");
			}
			else{
				printf("state is safe\n");
			}
		}
		else{
			printf("Invalid  input,  use  one  of  RQ,  RL, Status, Run, Exit\n");
		}

	}


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
			token = strtok(NULL, ",");
			current_resource++;
		}

		current_customer++;

	}

	return customer_array;
}


char* readUserInput(){

	int current_size = 100;

	char *user_input = malloc(current_size);

	if(user_input != NULL){
		int c = EOF;
		int i = 0;

		while( (c = getchar()) != '\n' && c != EOF){
			user_input[i] = (char) c;
			i++;

			if(i == current_size){
				current_size = i + 100;
				user_input = realloc(user_input, current_size);

			}
		}

		user_input[i] = '\0';

	}
		return user_input;

}

void calculateNeed(){
	for(int i = 0; i < customer_num; i++){
		for(int j = 0; j < resource_num; j++){
			need[i][j] = maximum[i][j] - allocated[i][j];
		}
	}
	return;
}

void statusCommand(){
	printf("Available Resources:\n");
	for(int i = 0; i < resource_num; i++){
		printf("%d ",available[i]);
	}
	printf("\n");

	printf("Maximum Resources:\n");
	for(int i = 0; i < customer_num; i++){
		for(int j = 0; j < resource_num; j++){
			printf("%d ",maximum[i][j]);
		}
		printf("\n");
	}

	printf("Allocated Resources:\n");
	for(int i = 0; i < customer_num; i++){
		for(int j = 0; j < resource_num; j++){
			printf("%d ",allocated[i][j]);
		}
		printf("\n");
	}

	printf("Need Resources:\n");
	for(int i = 0; i < customer_num; i++){
		for(int j = 0; j < resource_num; j++){
			printf("%d ",need[i][j]);
		}
		printf("\n");
	}

	return;
}

// returns 0 if false and 1 if true
int safeState(){

	//initialize finish[] to FALSE
	int* finish = malloc(sizeof(int)*customer_num);
	for(int i = 0; i < customer_num; i++){
		finish[i] = FALSE;
	}

	//make array copy of available into array work
	int* work = malloc(sizeof(int*) * resource_num);

	//fill work with the values in available
	for(int i = 0; i < resource_num; i++){
		work[i] = available[i];
	}

	//main loop

	int found = TRUE;

	while(found == TRUE){
		int index = -1;
		for(int i = 0; i < customer_num; i++){
			if(finish[i] == FALSE){
				int less = TRUE;
				for(int j = 0; j < resource_num; j++){
					if(need[i][j] > work[j]){
						less = FALSE;
						break;
					}
				}
				if(less == TRUE){
					index = i;
					break;
				}
			}
		}
		if(index == -1){
			found = FALSE;
		}
		else{
			//work = work + allocated
			for(int i = 0; i < resource_num; i++){
				work[i] = work[i] + allocated[index][i];
			}
			finish[index] = TRUE;
		}
	}


	int is_safe = TRUE;

	for(int i = 0; i < customer_num; i++){
		if(finish[i] == FALSE){
			is_safe = FALSE;
			break;
		}
	}

	free(work);
	free(finish);

	return is_safe;
}

