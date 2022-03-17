#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int *available;
int resource_num;

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







	return 0;
}
