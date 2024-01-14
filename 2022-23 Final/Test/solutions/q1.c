#include <stdio.h>
#define Q1 5 // Comentando esta línea daría Warning pero compilaría
#include "q1.h"
#define TAM 4

int main(){
	struct point array[TAM];
	int i = 0;
	for(i=0; i<TAM; i++){
		array[i].x = i;
		array[i].y = 2*i;
	}
	printf("(x,y) = (%d,%d)\n", array[TAM-1].x, array[TAM-1].y);
	return 0;
}