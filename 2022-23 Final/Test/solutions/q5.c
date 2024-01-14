#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	FILE *fd;
	char *buffer;
	ssize_t readc=0;
	size_t n=0;
	fd = fopen("q5.txt", "r");
	while((readc=getline(&buffer,&n,fd)!=-1)){
		// Eliminate \r\n
		//buffer[strcspn(buffer, "\r\n")] = 0;
		//printf("%s\n", buffer);
		if(strcmp(buffer,"c1") == 0){
			printf("A");
		}
	}
	free(buffer);
	fclose(fd);
	printf("B\n");
	return 0;
}
