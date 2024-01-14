#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fd = fopen("q3file.txt", "r");
	fseek(fd, 2L, SEEK_SET);
	int val1 = fgetc(fd) - '0';
	rewind(fd);
	int val2 = fgetc(fd) - '0';
	fseek(fd, -3L, SEEK_END);
	int val3 = ftell(fd);
	int result = val1 + val2 + val3;
	printf("%d (%d+%d+%d)\n", result, val1, val2, val3);
	return 0;
}