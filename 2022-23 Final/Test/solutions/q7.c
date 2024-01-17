#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	pid_t childpid,childpid2,childpid3;
	childpid = fork();
	childpid2 = fork();
	childpid3 = fork();
	if (childpid2 == 0){
		if(childpid3 == 0){
			printf("4 ");
			exit(EXIT_SUCCESS);
		}
		printf("2 ");
		exit(EXIT_SUCCESS);
	}
	if (childpid3 == 0){
		printf("3 ");
		exit(EXIT_SUCCESS);
	}
	if (childpid == 0){
		printf("1 ");
		exit(EXIT_SUCCESS);
	}
	printf("root ");
}
