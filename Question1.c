/*
 * Alexander Van Rooy GitHub login ID: alexvanrooy
 * URL of GitHub repository: https://github.com/alexvanrooy/cp386_a4
 */


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>
#include <pthread.h>

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
int requestCommand(char* input);
int releaseCommand(char* input);
int* findSafeSequence();
void runCommand();
void *runThread(void *customer_id);

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

		char command_copy[strlen(user_command)];
		strcpy(command_copy, user_command);


		token = strtok(user_command," ");


		if(strcmp(user_command, "Exit") == 0){
			break;
		}
		else if(strcmp(token, "RQ") == 0){
			int request_success = requestCommand(command_copy);

			if(request_success == TRUE){
				printf("State is safe, and request is satisfied\n");
			}
			else{
				printf("State is unsafe, and request is denied\n");
			}
		}
		else if(strcmp(token, "RL") == 0){
			int successful_release = releaseCommand(command_copy);
			if(successful_release == TRUE){
				printf("The  resources  have  been  released successfully\n");
			}
			else{
				printf("The resources not been released\n");
			}


		}
		else if(strcmp(user_command, "Status") == 0){
			statusCommand();
		}
		else if(strcmp(user_command, "Run") == 0){
			runCommand();
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

int requestCommand(char* input){
	char* token;
	token = strtok(input, " "); //this is the command name (discard it)
	token = strtok(NULL, " "); // this is the customer number
	if(token == NULL){
		return FALSE;
	}

	int customer_number = atoi(token);

	if(customer_number >= customer_num){		//requested a customer number that is not in the available customers
		return FALSE;
	}

	int request[resource_num];

	//fill the request vector with the values from the input
	int count = 0;
	token = strtok(NULL, " ");

	while(token != NULL){
		if(count >= resource_num){	//there are more resources requested than there are resources in the system
			return FALSE;
		}

		request[count] = atoi(token);
		count++;
		token = strtok(NULL, " ");
	}


	//check that request is less than need
	for(int i = 0; i < resource_num; i++){
		if(request[i] > need[customer_number][i]){
			return FALSE;
		}
	}


	//check that request <= available
	for(int i = 0; i < resource_num; i++){
		if(request[i] > available[i]){
			return FALSE;
		}
	}

	//pretend to allocate resources then check if state is safe
	for(int i = 0; i < resource_num; i++){
		available[i] = available[i] - request[i];
		allocated[customer_number][i] = allocated[customer_number][i] + request[i];
		need[customer_number][i] = need[customer_number][i] - request[i];
	}

	int is_safe = safeState();

	if(is_safe == FALSE){		//restore old values

		for(int i = 0; i < resource_num; i++){
			available[i] = available[i] + request[i];
			allocated[customer_number][i] = allocated[customer_number][i] - request[i];
			need[customer_number][i] = need[customer_number][i] + request[i];
		}
	}



	return is_safe;
}

int releaseCommand(char* input){
	char* token;
	token = strtok(input, " "); //this is the command name (discard it)
	token = strtok(NULL, " "); // this is the customer number

	if(token == NULL){
		return FALSE;
	}

	int customer_number = atoi(token);

	if(customer_number >= customer_num){		//requested a customer number that is not in the available customers
		return FALSE;
	}

	int request[resource_num];

	for(int i = 0; i < resource_num; i++){
		request[i] = 0;
	}

	//fill the request vector with the values from the input
	int count = 0;
	token = strtok(NULL, " ");

	while(token != NULL){
		if(count >= resource_num){	//there are more resources requested than there are resources in the system
			return FALSE;
		}

		request[count] = atoi(token);
		count++;
		token = strtok(NULL, " ");
	}



	//check that the request <= allocated
	for(int i = 0; i < resource_num; i++){
		if(request[i] > allocated[customer_number][i]){
			return FALSE;
		}
	}


	//free the resources and change all the data structures
	for(int i = 0; i < resource_num; i++){
		allocated[customer_number][i] = allocated[customer_number][i] - request[i];
		need[customer_number][i] = need[customer_number][i] + request[i];
		available[i] = available[i] + request[i];
	}



	return TRUE;

}

int* findSafeSequence(){

	int* safe_sequence = malloc(sizeof(int)*customer_num);

	for(int i = 0; i < customer_num; i++){
		safe_sequence[i] = -1;
	}

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

	int order = 0;
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
			safe_sequence[order] = index;
			order++;
		}
	}


	free(work);
	free(finish);

	return safe_sequence;

}

void runCommand(){
	int is_safe = safeState();
	if(is_safe == FALSE){
		printf("State is not safe, Run request denied\n");
		return;
	}

	int* safe_sequence = findSafeSequence();

	printf("Safe Sequence is: ");
	for(int i = 0; i < customer_num; i++){
		printf("%d ",safe_sequence[i]);
	}
	printf("\n");

	for(int i = 0; i < customer_num; i++){
		printf("--> Customer/Thread %d\n",safe_sequence[i]);
		pthread_t t_id;
		int current_id = safe_sequence[i];
		int *id_p = &current_id;
		pthread_create(&t_id, NULL, runThread,(void *)id_p);
		pthread_join(t_id, NULL);
	}

	free(safe_sequence);
	return;
}


void *runThread(void *input){
	int customer_id = *((int *)input);

	printf("   Allocated resources: ");
	for(int i =0; i < resource_num; i++){
		printf(" %d",allocated[customer_id][i]);
	}
	printf("\n");

	printf("   Needed: ");
		for(int i =0; i < resource_num; i++){
			printf(" %d",need[customer_id][i]);
		}
	printf("\n");

	printf("   Available: ");
		for(int i =0; i < resource_num; i++){
			printf(" %d",available[i]);
		}
	printf("\n");
	printf("   Thread has started\n");
	//add the allocated to the available and reset need back to maximum
	for(int i = 0; i < resource_num; i++){
		available[i] = available[i] + allocated[customer_id][i];
		allocated[customer_id][i] = 0;
		need[customer_id][i] = maximum[customer_id][i];
	}
	printf("   Thread has finished\n");
	printf("   Thread is releasing resources\n");
	printf("   New Available: ");
	for(int i = 0; i < resource_num; i++){
		printf("%d ",available[i]);
	}
	printf("\n");


	return NULL;
}
