#include <stdio.h>
#define SIZE 5

int main(){
	int array[SIZE] = {1,2,3,4,5};
	int *ptr_1 = array;
	int **ptr_2 = &ptr_1;
	for(int i=0; i<SIZE;i++){
		printf("%d", *(*ptr_2+i));
		//printf("%d", **ptr_2[i]);
		//printf("%d", *ptr_1[i]);
		//printf("%d", **ptr_2->i);
	}
	printf("\n");
	return 0;
}