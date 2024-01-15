#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

pid_t child = 0; 

void handler1(int s){
	printf("Hello %i (my father) \n", getppid());
	sleep(1);
	kill(getppid(), SIGTSTP);
}

void handler2(int s){
	printf("Hello %i (my child) \n", child);
	sleep(1);
	kill(child, SIGTSTP);
}

void handler3(int s){
	kill(child,SIGTSTP);
}

int main(){
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if((child = fork())<0){ exit(EXIT_FAILURE); }
	else if(child == 0){
		signal(SIGTSTP, handler1);
		while(1) { pause(); }
	} else {
	    signal(SIGTSTP,handler2);
		signal(SIGINT,handler3);
		while(1) { pause(); }
	}
}
