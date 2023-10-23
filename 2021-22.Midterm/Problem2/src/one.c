#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>


#define FIFO_PATH "./tmp/2021-22_M1_fifo"
#define FIFO_DIR "./tmp/"

static int keepAlive = 1;
static int tstp = 0;


void intHandler(int s) {
    keepAlive = 0;
}

void tstpHandler(int s) {
    tstp = 1;
}


int main(int argc, char **argv)
{
    mkdir(FIFO_DIR, 0777);
    printf("Setting up... ");
    mkfifo(FIFO_PATH, 0666);
    printf("Waiting for 'two'... ");
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "FIFO open error");
        exit(EXIT_FAILURE);
    }
    printf("Setup complete.\n");

    int tstp_count = 0;
    while (keepAlive) {
        signal(SIGINT, intHandler);
        signal(SIGTSTP, tstpHandler);
        pause();
        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);

        if (tstp) {
            tstp_count++;
            if (tstp_count % 5 == 0) {
                write(fd, &tstp_count, sizeof(int));
                printf(" (Multiple of 5)");
            }
            printf(" TSTPs: %d\n", tstp_count);
            tstp = 0;
        }
    }
    printf(" Exiting... ");

    printf("Sending termination to 'two'... ");
    int terminate = -1;
    write(fd, &terminate, sizeof(int)); // Send termination to process 2
    close(fd);

    printf("Done\n");
    exit (EXIT_SUCCESS);
}
