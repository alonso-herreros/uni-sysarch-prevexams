#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	char **array = (char **) malloc(sizeof(char *));
	array[0] = strdup("systems");
	char **aux = NULL;
	aux = (char **) realloc(array, 2*sizeof(char *));
	if(aux==NULL){
		exit(1);
	}
	array = aux;
	array[1] = strdup("architecture");
	printf("array[0]=%s , array[1]=%s\n", array[0], array[1]);
	free(array);
}