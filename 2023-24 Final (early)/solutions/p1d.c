#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

struct time_record{
	char driver[4];
	double time;
	struct time_record *next;
} typedef TimeRecord;

void Print_list(TimeRecord *list){
	TimeRecord *aux = list;
	int pos = 1;
	while(aux != NULL){
		printf("%d: %s | %.3f\n", pos, aux->driver, aux->time);
		aux = aux->next;
		pos += 1;
	}
}

void Free_list(TimeRecord *list){
	TimeRecord *aux = list;
	while(aux != NULL){
		list = list->next;
		free(aux);
		aux = list;
	}
}

void Add(TimeRecord **list, TimeRecord *newtime){
	if(*list == NULL){
		newtime -> next = NULL;
		*list = newtime;
	} else {
		// If driver is in the leaderboard update time
		TimeRecord *aux = *list;
		TimeRecord *prev = *list;
		int finished = 0;
		while(aux != NULL){
			if(strcmp(newtime->driver,aux->driver)==0){ // driver found
			// delete time if it is better to add it later in correct position and finish the loop
				if(newtime->time < aux->time){
					if(aux == *list){ // it is the first element
						*list = (*list)->next;
						free(aux);
					} else { // it is an element in the middle
						prev->next = aux->next;
						free(aux);
					}
				} else {
					finished = 1; // no need to add as time is worse and no need to continue
					free(newtime);
				}
				break;
			}
			prev = aux;
			aux = aux->next;
		}
		if(!finished){ // If driver is not in the leaderboard, add it in the corresponding position
			aux = *list;
			prev = *list;
			// Check if it is the best time
			if(newtime->time < aux->time){ // best time so add it in the first position
				newtime -> next = *list;
				*list = newtime;
			} else {
				// Add it in the middle
				int added = 0;
				while(aux != NULL){
					if(newtime->time < aux->time){
						prev->next = newtime;
						newtime->next = aux;
						added = 1;
						break;
					}
					prev = aux;
					aux = aux->next;
				}
				// Case when the time is the worst
				if(added == 0){
					prev->next = newtime;
				}
			}
		}
	}
}

int main(int argc, char **argv){
	pid_t child;
	int fd[2];
	if(pipe(fd)){
		perror("Error while creating pipe");
		exit(EXIT_FAILURE);
	}
	
	child = fork();
	if(child < 0){
		perror("Error while creating child\n");
		exit(EXIT_FAILURE);
	}
	if(child == 0){
		TimeRecord* list = NULL;
		TimeRecord *aux = NULL;
		close(fd[1]);
		int value = 0;
		while(1){
			aux = (TimeRecord *) malloc(sizeof(TimeRecord));
			value = read(fd[0], aux, sizeof(TimeRecord));
			if(value == 0){
				break;
			}
			Add(&list, aux);
			Print_list(list);
		}
		free(aux);
		Free_list(list);
		_exit(EXIT_SUCCESS);
	} else {
		ssize_t number = 0;
		size_t n_alloc = 0;
		char *token;
		char *buffer = NULL;
		char *saveptr=NULL;
		close(fd[0]);
		printf("Introduce the time with format driver,time with the initials of the drivers and the time in seconds (e.g,., 'SAI,61.756'):");
		while ((number = getline(&buffer, &n_alloc, stdin)) != -1){
			token = strtok_r(buffer, ",", &saveptr);
			TimeRecord new_time;
			memset(&new_time.driver,0,sizeof(TimeRecord));
			strcpy(new_time.driver,token);
			new_time.driver[3] = 0;
			token = strtok_r(NULL, ",", &saveptr);
			double time = atof(token);
			new_time.time = time;
			write(fd[1], &new_time, sizeof(TimeRecord));
			usleep(200);
			printf("Introduce the time with format driver,time with the initials of the drivers and the time in seconds (e.g,., 'SAI,61.756'):");
		}
		printf("\n");
		close(fd[1]);
		free(buffer);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	
}