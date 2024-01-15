
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ASlib.h"

#define IP_SIZE 20
#define MAC_SIZE 20

#define FILE_NAME "Nodes.dat"

typedef struct Node
    {
    char ip[IP_SIZE];
    char mac[MAC_SIZE];
    struct Node *next;
    } Node;


void  Verify_args(int ac, char**av);

Node* New_node(const char*ip, const char *mac);
Node* Add(Node *p_first, Node *p_node);

Node* Read(const char *file_name);  
void  Save(Node *p_first, const char*file_name);

void  Display(Node *p_first);
void  Destroy(Node *p_first);

/*
int main (int ac, char**av)
    {
    Node *p_first = NULL;
    Node *p_node;
    Verify_args(ac, av);
        
    p_first = Read (FILE_NAME);
    Display (p_first);
    p_node = New_node(av[1],av[2]);
    p_first = Add(p_first, p_node);
    Display (p_first);
    Save(p_first,FILE_NAME);
    Destroy(p_first);
    }
*/

//--------------------------------------------------
void Verify_args(int ac, char**av)
    {
    if (ac != 3)
        {
        printf("usage: %s <ip> <mac>\n", av[0]);
        exit(EXIT_SUCCESS);
        }
    }
    
Node* New_node(const char *ip, const char *mac)
    {
    Node *p_node = malloc(sizeof(Node));
    strncpy(p_node->ip,ip,IP_SIZE);
    strncpy(p_node->mac,mac,MAC_SIZE);
    p_node->next = NULL;
    return(p_node);
    }
    
//---------------------------------------------------------------------
Node* Read(const char *file_name)
    {
    Node *p_first = NULL;
    Node *p_node, *p;
    
    if (access(file_name,F_OK) != 0) return(NULL);
    FILE *f = fopen(file_name,"rb");
    
    do
        {
        p_node = malloc(sizeof(Node));
        fread(p_node, sizeof(Node), 1,f);
        p = p_node->next;
        p_node->next = 0;
        p_first = Add(p_first,p_node);
        } 
        while (p != NULL); 
        
    fclose(f);
    
    return(p_first);
    }    
    
Node* Add(Node*p_first, Node*p_node)
    {
    Node *p;
    if (p_first == NULL) return (p_node);
    for (p = p_first; p->next; p=p->next);
    p->next = p_node;
    p_node->next = NULL;
    return (p_first);
    }
    
void  Display(Node *p_first)
    {
    puts("--------Node list----------");
    if (p_first == NULL) puts("Empty");
    else
        {
        for (Node *p = p_first; p; p=p->next)
            printf("ip=\"%s\" mac=\"%s\" \n",p->ip,p->mac);
        }
    puts("-------------------------");
    }

void  Save(Node *p_first, const char*file_name)
    {
    FILE *f = fopen(file_name,"wb");
    if (p_first != NULL) 
        {
        for (Node *p = p_first; p; p=p->next)
            fwrite(p,sizeof(Node),1,f);
        }
    fclose(f);
    }
void  Destroy(Node *p_first)
    {
    Node *p, *p_next;
    for (p=p_first; p; p = p_next)
        {
        p_next = p->next;
        free(p);
        }
    }
    
//--------------Modificacion 
char *ip, *mac;
pid_t child_pid;
int estado;

void Child_handler(int s)
    {
    Node *p_first = Read(FILE_NAME);
    Display(p_first);
    Destroy(p_first);
    kill(getppid(),SIGUSR1);
    } 
    
void Parent_handler(int s)
    {
    if (estado == 0)
        {
        Node *p_first = Read(FILE_NAME);
        Node *p_node = New_node(ip,mac);
        Add (p_first, p_node);
        Save(p_first, FILE_NAME);
        Destroy(p_first);
        estado = 1;
        kill(child_pid,SIGUSR1);
        }
    else 
        {
        kill(child_pid,SIGINT);
        }
    } 
  
void Child_process()
    {
    void *p;
    p = signal (SIGUSR1,Child_handler);
    while(1);
    }  
  
int main (int ac, char**av)
    {
    int status ;
    
    Verify_args(ac, av);
    ip = av[1];
    mac = av[2];
    
    child_pid = fork();
    if (child_pid <0)
        {
        perror("Error en el fork");
        exit (EXIT_FAILURE);
        }
    if (child_pid == 0) Child_process();
    
    //Parent process
    signal(SIGUSR1,Parent_handler);
    
    Pausa (1000,1000);
    kill(child_pid,SIGUSR1);
    
    wait (&status);
    exit(EXIT_SUCCESS);
    }
        
