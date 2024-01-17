#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

pid_t pidex = 0;
pid_t pid = 0;
int status;

void handler(int signal){
	kill(pidex, SIGINT);
	pid = wait(&status);
	exit(EXIT_SUCCESS);
}

int main(){
	if ((pidex = fork())<0){
		exit(EXIT_FAILURE);
	}else if (pidex == 0){
		while(1){
			printf("question 9\n");
		}
	}else{
		signal(SIGALRM, handler);
		alarm(3);
		while(1){
			pause();
		}
	}
	return 0;
}