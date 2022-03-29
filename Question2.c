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
void releaseCommand(char* input);



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
	MAX = atoi(argv[1]);
	printf("Allocated %d bytes of memory\n",MAX);

	//initialize the head process

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
			releaseCommand(command_copy);
		}

		else if(strcmp(token, "RQ") == 0){
			requestCommand(command_copy);
		}

		else if(strcmp(token, "Status") == 0){
			struct Process* current = head;
			while(current != NULL){
				printf("P%d: [%d : %d]\n",current->process_id,current->mem_start,current->mem_end);
				current = current->next;
			}
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
	char* process_string = strtok(NULL, " ");
	if(process_string == NULL){
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
	token = strtok(NULL, " ");
	if(token == NULL){
		printf("Invalid RQ command\n");
		return;
	}
	if(strcmp(token, "B") != 0){
		printf("Unsupported Allocation Algorithm requested, try B (Best-Fit)\n");
		return;
	}

	int process_number = atoi(process_string + 1);

	//check to see if process already allocated a memory block
	struct Process* temp = head;
	while(temp != NULL){
		if(temp->process_id == process_number){
			printf("Process already allocated memory, request denied\n");
			return;
		}
		temp = temp->next;
	}

	//memory allocation process
	if(size > MAX){
		printf("No hole of sufficient size\n");
		return;
	}

	if(head == NULL){
		printf("Head is empty...allocating first block\n");

		head = malloc(sizeof(struct Process));
		head->mem_start = 0;
		head->mem_end = size - 1;
		head->next = NULL;
		head->process_id = process_number;
		total_allocated += size;
	}
	else{
		//struct Process* smallest_hole;
		struct Process* current = head;
		struct Process* previous = NULL;
		int current_hole_size = -1;
		int min_hole_size = -1;

		//check that the head mem_start is at 0, if not then check the size of the hole from 0 to head mem_start



		while(current != NULL){ //go through the list and fine the smallest hole
			//if previous == NULL check that the current mem_start is not == 0 cause then there is a hole from 0 to current mem_start

			//if previous != NULL then check the hole between previous mem_end and current mem_start
			previous = current;
			current = current->next;
		}

		//check that the previous mem_end is equal to max-1, if not then check the size of the hole from mem_end to max - 1
		if(previous->mem_end != MAX - 1){
			current_hole_size = (MAX - 1) - previous->mem_end;
			//add a check here to make sure that this hole is smaller than the previous small hole
			if(current_hole_size >= size){
				previous->next = malloc(sizeof(struct Process));
				previous->next->mem_start = previous->mem_end + 1;
				previous->next->mem_end = previous->next->mem_start + (size - 1);
				previous->next->next = NULL;
				previous->next->process_id = process_number;
			}
		}



	}

	return;
}

void releaseCommand(char* input){

	char* token;
	token = strtok(input, " ");

	if(token == NULL){
		printf("Invalid RL command\n");
		return;
	}

	char* process_string = strtok(NULL, " ");
	if(process_string == NULL){
		printf("Invalid RL command\n");
		return;
	}


	int process_number = atoi(process_string + 1);

	struct Process* current = head;
	struct Process* previous = NULL;

	if(head == NULL){
		printf("No memory has been allocated yet, release request denied\n");
		return;
	}

	//if the head is the memory to be freed
	if(head->process_id == process_number){
		head = head->next;
		free(current);
		printf("releasing memory for process P%d\n", process_number);
		return;
	}


	while(current != NULL){
		if(current->process_id == process_number){
			previous->next = current->next;
			free(current);
			printf("releasing memory for process P%d\n", process_number);
			break;
		}
		previous = current;
		current = current->next;
	}

	return;

}
