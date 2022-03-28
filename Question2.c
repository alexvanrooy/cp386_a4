#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

int total_allocated;
int MAX;


char* readUserInput();
void requestCommand(char* input);



//this struct will be a linked list that holds the data for all the memory allocatons
struct Process {
	int process_id;
	int mem_start;
	int mem_end;
	struct Process* next;
};

struct Process* head = NULL;



int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Invalid Initialization\n");
		return 0;
	}

	total_allocated = 0;

	//initialize the head process
	head = (struct Process*)malloc(sizeof(struct Process));
	head->process_id = -1;

	MAX = atoi(argv[1]);
	printf("Allocated %d bytes of memory\n",MAX);

	while(1){
		printf("command>");
		char* command = readUserInput();
		char command_copy[strlen(command)];
		strcpy(command_copy,command);

		char* token;
		token = strtok(command, " ");


		if(strcmp(token, "Exit") == 0){
			break;
		}

		else if(strcmp(token, "RL") == 0){
			printf("RL COMMAND\n");
		}

		else if(strcmp(token, "RQ") == 0){
			requestCommand(command_copy);
		}

		else if(strcmp(token, "Status") == 0){
			printf("Status COMMAND\n");
		}

		else{
			printf("Invalid command, try one of the following: RQ, RL, Status, Exit\n");
		}


	}



	return 0;
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

void requestCommand(char* input){

	char* token;
	token = strtok(input, " "); //gets RQ, discard
	char* process_number = strtok(NULL, " ");
	if(process_number == NULL){
		printf("Invalid RQ command\n");
		return;
	}
	token = strtok(NULL, " "); // gets the size
	if(token == NULL){
		printf("Invalid RQ command\n");
		return;
	}
	int size = atoi(token);
	if(size == 0){
		printf("Cannot allocate 0 memory, request denied\n");
		return;
	}




	int count = 0;
	while(token != NULL){
		printf("%d: %s\n",count, token);
		count++;
		token = strtok(NULL, " ");
	}


	return;
}
