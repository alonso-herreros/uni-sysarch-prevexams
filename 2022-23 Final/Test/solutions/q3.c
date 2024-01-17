#include <stdlib.h>
#include <stdio.h>

int main(){
	char text[5]="123a";
	int base = 10;
	char *endptr;
	int val = strtol(text, &endptr, base);
	printf("Val: %d | Endptr: %s\n", val, endptr);
	return 0;
}