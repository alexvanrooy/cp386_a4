/*
 * Alexander Van Rooy GitHub login ID: alexvanrooy
 * URL of GitHub repository: https://github.com/alexvanrooy/cp386_a4
 */


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
void statusCommand();



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
			statusCommand();
			/*
			struct Process* current = head;
			printf("Partitions [Allocated memory = %d]:\n",total_allocated);
			while(current != NULL){
				printf("Address {%d:%d} Process P%d\n",current->mem_start, current->mem_end, current->process_id);
				current = current->next;
			}
			printf("\n");

			printf("Holes [Free memory = %d]:\n",MAX - total_allocated);

			current = head;
			struct Process* previous = NULL;
			if(head->mem_start != 0){
				int hole_size = current->mem_start;
				printf("Address {0:%d} len = %d\n",current->mem_start - 1, hole_size);
			}
			while(current != NULL){
				int hole_size;
				if(previous != NULL){
					hole_size = current->mem_start - (previous->mem_end + 1);
					if(hole_size > 0){
						printf("Address {%d:%d} len = %d\n",previous->mem_end + 1, current->mem_start - 1, hole_size);
					}
				}
				previous = current;
				current = current->next;
			}
			if(previous->mem_end < MAX - 1){
				int hole_size = MAX - (previous->mem_end + 1);
				printf("Address {%d:%d} len = %d\n",previous->mem_end + 1, MAX - 1, hole_size);
			}
			*/
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

	if(head == NULL){									//for the first memory allocation
		head = malloc(sizeof(struct Process));
		head->mem_start = 0;
		head->mem_end = size - 1;
		head->next = NULL;
		head->process_id = process_number;
		total_allocated += size;
		printf("Successfully allocated %d to process P%d\n",size, process_number);
	}
	else{												//for all memory allocations after the first one
		struct Process* smallest_hole = NULL;
		struct Process* current = head;
		struct Process* previous = NULL;
		int current_hole_size;
		int min_hole_size = -1;

		while(current != NULL){ //go through the list and fine the smallest hole
			//if previous == NULL check that the current mem_start is not == 0 cause then there is a hole from 0 to current mem_start
			if(previous == NULL){
				current_hole_size = current->mem_start;
				if(current_hole_size >= size){
					if(min_hole_size == -1 || current_hole_size < min_hole_size){
						min_hole_size = current_hole_size;
						smallest_hole = previous;
					}
				}
			}


			else if(previous != NULL){													//finding smallest hole in the middle of the list
				current_hole_size = current->mem_start - (previous->mem_end + 1);

				if(min_hole_size == -1 && current_hole_size >= size){
					min_hole_size = current_hole_size;
					smallest_hole = previous;
				}

				//if previous != NULL then check the hole between previous mem_end and current mem_start
				else if(current_hole_size >= size && current_hole_size < min_hole_size){
					min_hole_size = current_hole_size;
					smallest_hole = previous;
				}

			}

			previous = current;
			current = current->next;
		}


		if(previous->mem_end != MAX - 1){								//finding smallest hole between the MAX size and the last memory allocation
			current_hole_size = (MAX - 1) - previous->mem_end;
			//add a check here to make sure that this hole is smaller than the previous small hole
			if(current_hole_size < min_hole_size || min_hole_size == -1){
				if(current_hole_size >= size){
					previous->next = malloc(sizeof(struct Process));
					previous->next->mem_start = previous->mem_end + 1;
					previous->next->mem_end = previous->next->mem_start + (size - 1);
					previous->next->next = NULL;
					previous->next->process_id = process_number;
					total_allocated += size;
					printf("Successfully allocated %d to process P%d\n",size, process_number);
					return;
				}
			}

		}

		//if the smallest hole is between 0 and the head mem_start
		if(min_hole_size != -1 && smallest_hole == NULL){
			struct Process* new_allocation = malloc(sizeof(struct Process));
			struct Process* temp = head;
			new_allocation->next = temp;
			new_allocation->mem_start = 0;
			new_allocation->mem_end = size - 1;
			new_allocation->process_id = process_number;
			head = new_allocation;
			total_allocated += size;
			printf("Successfully allocated %d to process P%d\n",size, process_number);
			return;


		}

		if(min_hole_size == -1){
			printf("No hole of sufficient size\n");
			return;

		}



		//creates the new memory allocation
		struct Process* new_allocation = malloc(sizeof(struct Process));
		new_allocation->next = smallest_hole->next;
		smallest_hole->next = new_allocation;

		new_allocation->mem_start = (smallest_hole->mem_end + 1);
		new_allocation->mem_end = new_allocation->mem_start + (size - 1);
		new_allocation->process_id = process_number;
		total_allocated += size;
		printf("Successfully allocated %d to process P%d\n",size, process_number);

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
		total_allocated -= (current->mem_end + 1) - current->mem_start;
		free(current);
		printf("releasing memory for process P%d\n", process_number);
		return;
	}


	while(current != NULL){
		if(current->process_id == process_number){
			previous->next = current->next;
			total_allocated -= (current->mem_end + 1) - current->mem_start;
			free(current);
			printf("releasing memory for process P%d\n", process_number);
			break;
		}
		previous = current;
		current = current->next;
	}

	return;

}

void statusCommand(){
	struct Process* current = head;
	printf("Partitions [Allocated memory = %d]:\n",total_allocated);
	while(current != NULL){
		printf("Address [%d:%d] Process P%d\n",current->mem_start, current->mem_end, current->process_id);
		current = current->next;
	}
	printf("\n");

	printf("Holes [Free memory = %d]:\n",MAX - total_allocated);
	if(MAX - total_allocated == MAX){
		return;
	}

	current = head;
	struct Process* previous = NULL;
	if(head->mem_start != 0){
		int hole_size = current->mem_start;
		printf("Address [0:%d] len = %d\n",current->mem_start - 1, hole_size);
	}
	while(current != NULL){
		int hole_size;
		if(previous != NULL){
			hole_size = current->mem_start - (previous->mem_end + 1);
			if(hole_size > 0){
				printf("Address [%d:%d] len = %d\n",previous->mem_end + 1, current->mem_start - 1, hole_size);
			}
		}
		previous = current;
		current = current->next;
	}
	if(previous->mem_end < MAX - 1){
		int hole_size = MAX - (previous->mem_end + 1);
		printf("Address [%d:%d] len = %d\n",previous->mem_end + 1, MAX - 1, hole_size);
	}
}



