#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>

int MAX;


char* readUserInput();

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Invalid Initialization\n");
		return 0;
	}

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
			printf("RQ COMMAND\n");
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
