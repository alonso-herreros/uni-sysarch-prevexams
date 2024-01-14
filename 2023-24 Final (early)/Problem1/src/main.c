#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>

#define PIPE_R 0
#define PIPE_W 1

#define PROMPT "Introduce the time with format '<driver>,<time>' with the 3 initials of the drivers and the time in seconds (e.g.:'SAI,61.756'):\n"


struct time_record{
    char driver[4];
    double time;
    struct time_record *next;
} typedef TimeRecord;

void dbgprintf(const char *format, ...) {
    static int enabled = 0;
    if (format[0] == 1) {
        enabled = 1;
        format = "Logging set to debug mode\n";
    }
    if (enabled) {
        va_list args;
        va_start(args, format);
        printf("[DBG] ");
        vprintf(format, args);
    }
}

void parent(int pipefd[2], pid_t child_pid);
int query_record(TimeRecord **record);

void child(int pipe[2]);
void sigint_handler(int sig);

void list_insert(TimeRecord **head, TimeRecord *new_element);
int list_remove(TimeRecord **head, TimeRecord *list_element);
TimeRecord *list_getdriver(TimeRecord *head, char driver[4]);
TimeRecord *list_gettimelt(TimeRecord *head, double time);

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

void list_insert(TimeRecord **head, TimeRecord *new_element)
{
    TimeRecord *last_lt = list_gettimelt(*head, new_element->time);
    if (last_lt == NULL) {
        dbgprintf("Best time ever.\n");
        new_element->next = *head;
        *head = new_element;
        dbgprintf("Inserted.\n");
        return;
    }
    dbgprintf("Inserting after %s,%f\n", last_lt->driver, last_lt->time);
    new_element->next = last_lt->next;
    last_lt->next = new_element;
    dbgprintf("Inserted.\n");
}

int list_remove(TimeRecord **head, TimeRecord *list_element)
{
    if (head==NULL || *head==NULL)  return -1;
    if (list_element == NULL)  return 0;

    if (*head == list_element) {
        *head = (*head)->next;
        return 1;
    }

    for (TimeRecord *aux = *head; aux != NULL; aux = aux->next) {
        if (aux->next == list_element) {
            aux->next = list_element->next;
        }
    }
    return 1;
}

TimeRecord *list_getdriver(TimeRecord *head, char driver[4])
{
    dbgprintf("Finding %s\n", driver);
    for(TimeRecord *aux = head; aux != NULL; aux = aux->next) {
        if (strcmp(driver, aux->driver) == 0) {
            return aux;
        }
    }
    return NULL;
}

TimeRecord *list_gettimelt(TimeRecord *head, double time)
{
    dbgprintf("Finding last time better than %f\n", time);
    if (head == NULL || head->time > time)  return NULL; // Best time ever
    dbgprintf("Not best time\n");
    TimeRecord *aux;
    for(aux = head; aux->next != NULL; aux = aux->next) {
        if (aux->next->time > time) {
            return aux;
        }
    }
    return aux;
}

void Add(TimeRecord **list, TimeRecord *newtime)
{
    TimeRecord *curr = list_getdriver(*list, newtime->driver);
    if (curr != NULL) {
        dbgprintf("Found existing record for %s\n", newtime->driver);
        if (curr->time < newtime->time)  return;
        dbgprintf("Updating record for %s\n", newtime->driver);
        list_remove(list, curr);
    }
    dbgprintf("Inserting %s,%f.\n", newtime->driver, newtime->time);
    list_insert(list, newtime);
}


void parent(int pipefd[2], pid_t child_pid)
{
    close(pipefd[PIPE_R]);
    TimeRecord *record = (TimeRecord *) malloc(sizeof(TimeRecord));

    int status = 0;
    while (status >= 0) {
        status = query_record(&record);
        if (status == 1) {
            write(pipefd[PIPE_W], record, sizeof(TimeRecord));
            usleep(200e3);
        }
    }
    
    dbgprintf("Exiting... \n");
    kill(child_pid, SIGINT);
    int child_status;
    printf("Child ended with %d status", wait(&child_status));

    close(pipefd[PIPE_W]);
    free(record);
    dbgprintf("Parent terminated.\n");
    exit(EXIT_SUCCESS);
}

int query_record(TimeRecord **record)
{
    printf(PROMPT);
    char name[4];
    double time;

    if (scanf("%3s,%lf", name, &time) != 2) { // Unexpected input
        if (feof(stdin)) { // CTRL+D
            return -1;
        }
        else { // Wrong input
            printf("Invalid input.\n");
            return 0;
        }
    }

    strcpy((*record)->driver, name);
    (*record)->time = time;

    return 1;
}


void child(int pipefd[2])
{
    signal(SIGINT, sigint_handler);
    close(pipefd[PIPE_W]);

    TimeRecord *head = NULL;

    while(1) {
        TimeRecord *record = (TimeRecord *) malloc(sizeof(TimeRecord));
        read(pipefd[PIPE_R], record, sizeof(TimeRecord));
        dbgprintf("RCV record @%p: %s, %.3f\n", record, record->driver, record->time);

        Add(&head, record);
        dbgprintf("add OK\n");
        Print_list(head);
    }

    dbgprintf("How did we here?");
    exit(EXIT_FAILURE);
}

void sigint_handler(int sig)
{
    if (sig == SIGINT) {
        dbgprintf("Child terminated.\n");
        exit(EXIT_SUCCESS);
    }
}


int main(int argc, char **argv)
{
    if (argc==2 && strcmp(argv[1], "--debug-logging")==0) {
        dbgprintf("\1");
    }
    
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        fprintf(stderr, "Error making pipes. Call a plumber.\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "Error forking. Call a chef.\n");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) child(pipefd);
    else parent(pipefd, pid);
}
