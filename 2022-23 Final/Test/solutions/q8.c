#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

pid_t pidex = 0;

int main(){
	int i=0;
	if ((pidex = fork())<0){
		exit(EXIT_FAILURE);
	}else if (pidex == 0){
		while(1){
			printf("final exam\n");
			i++;
			if(i == 5){
				kill(getppid(), SIGINT);
			}
		}
	}else{
		while(1){
			pause();
		}
	}
	return 0;
}