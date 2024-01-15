#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char *str = strdup("3.14 es pi");
	char *endptr;
	float val;
	val = strtof(str, &endptr);
	printf("val:%f%s\n" , val, endptr); 
}
