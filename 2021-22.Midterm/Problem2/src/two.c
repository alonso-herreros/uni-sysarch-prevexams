#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define INTSTR_SIZE 11 // max chars an int can take up
#define FIFO_PATH "./tmp/2021-22_M1_fifo"
#define FIFO_DIR "./tmp"


int main(int argc, char **argv)
{
    mkdir(FIFO_DIR, 0777);
    printf("Setting up... ");
    mkfifo(FIFO_PATH, 0666);
    printf("Waiting for 'one'... ");
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "FIFO open error");
        exit(EXIT_FAILURE);
    }
    printf("Setup complete.\n");

    int recvc = 0;
    for (int recv=0; recv != -1; read(fd, &recv, sizeof(int)) ) {
        if (recv==0)  continue;
        pid_t pid = 0;
        if ((pid = fork()) == -1) {
            fprintf(stderr, "Error forking (buy some new cutlery).\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            char recv_str[INTSTR_SIZE];
            sprintf(recv_str, "%d", recv);
            execl("/bin/echo", "echo", "The number is: ", recv_str, NULL);
        }
        else {
            int status;
            pid_t pid = wait(&status);
            printf("Child %d exited with status %d.\n", pid, status);
            recvc++;
        }
    }

    close(fd);

    printf("Total numbers received: %d\n", recvc);
    printf("Exiting due to termination signal from 'one'.\n");

    exit(EXIT_SUCCESS);
}
