#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handler(int signal){
	kill(0,SIGQUIT);
}

int main(int argc, char **argv){
	pid_t child;
	child = fork();
	if(child<0){
		exit(EXIT_FAILURE);
	} else if(child==0){
		signal(SIGINT, SIG_IGN);
		kill(0,SIGINT);
	} else {
		signal(SIGQUIT, handler);
		signal(SIGINT, handler);
		while(1);
	}
}