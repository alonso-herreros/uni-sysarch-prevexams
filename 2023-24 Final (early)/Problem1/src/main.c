#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

struct time_record{
    char driver[4];
    double time;
    struct time_record *next;
} typedef TimeRecord;

void list_insert(TimeRecord **head, TimeRecord *new_element);
TimeRecord *list_remove(TimeRecord **head, TimeRecord *list_element);
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
        new_element->next = *head;
        *head = new_element;
        return;
    }
    new_element->next = last_lt->next;
    last_lt->next = new_element;
}

TimeRecord *list_remove(TimeRecord **head, TimeRecord *list_element)
{
    if (head==NULL || *head==NULL)  return NULL;
    if (list_element == NULL)  return *head;

    if (*head == list_element) {
        *head = (*head)->next;
        return *head;
    }

    for (TimeRecord *aux = *head; aux != NULL; aux = aux->next) {
        if (aux->next == list_element) {
            aux->next = list_element->next;
        }
    }

    return *head;
}

TimeRecord *list_getdriver(TimeRecord *head, char driver[4])
{
    for(TimeRecord *aux = head; aux!= NULL; aux = aux->next) {
        if (strcmp(driver, aux->driver) == 0) {
            return aux;
        }
    }
    return NULL;
}

TimeRecord *list_gettimelt(TimeRecord *head, double time)
{
    if (head->time > time)  return NULL;
    TimeRecord *aux;
    for(aux = head; aux!= NULL; aux = aux->next) {
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
        if (curr->time < newtime->time)  return;
        list_remove(list, curr);
    }
    list_insert(list, newtime);
}

int main(int argc, char **argv)
{
    // SECTION 1.2
}