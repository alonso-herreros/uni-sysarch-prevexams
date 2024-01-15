#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define IP_SIZE 20
#define MAC_SIZE 20
#define TRACE printf ("%S:%d\n", __FILE__, __LINE__)

#define FILE_NAME "Nodes.dat"

typedef struct Node
    {
    char ip[IP_SIZE];
    char mac[MAC_SIZE];
    struct Node *next;
    } Node;

// Verify_args debe comprobar que la invocación al programa es correcta. 
void Verify_args(int ac, char ** av);

// New_node debe construir un nuevo nodo a partir de la información de los argumentos 
Node* New_node(const char*ip, const char *mac);
// Add debe añadir el nodo apuntado por p_node a la lista que comienza en p_first 
Node* Add(Node *p_first, Node *p_node);

// Read debe leer el archivo dado construyendo la cadena que devuelve con el puntero al 
// primer nodo de la lista. 
Node* Read(const char *file_name);
// Save debe salvar la lista que empieza en p_first en el archivo dado. 
void Save(Node *p_first, const char*file_name);

// Display presenta por pantalla la lista que comienza en p_first. 
void Display (Node *p_first);
// Destroy debe liberar la memoria ocupada por la lista.
void Destroy (Node *p_first);

int main (int ac, char ** av)
    {
    Node *p_first = NULL;
    Node *p_node;
    Verify_args(ac, av);

    p_first = Read(FILE_NAME);
    Display(p_first);
    p_node = New_node(av[1], av[2]);
    p_first = Add(p_first, p_node);
    Display(p_first);
    Save(p_first, FILE_NAME);
    Destroy(p_first);
    }

void Verify_args(int ac, char ** av)
    {
    if (ac != 3)
        {
        printf("usage: %s <ip> <mac>\n", av[0]);
        exit (EXIT_SUCCESS);
        }
    }

Node* New_node(const char *ip, const char *mac)
    {
    Node *p_node = malloc(sizeof(Node));
    strncpy(p_node->ip, ip, IP_SIZE);
    strncpy(p_node->mac,mac, MAC_SIZE) ;
    p_node->next = NULL;
    return(p_node) ;
    }


void Display(Node *p_first)
    {
    puts("--------Node list--------");
    if (p_first == NULL) puts("Empty");
    else
        {
        for (Node *p = p_first; p; p=p->next)
        printf("ip=\"%s\" mac=\"%s\" \n", p->ip, p->mac);
        }
    puts("-------------------------");
    }

Node *Read(const char *file_name)
{
    FILE *f = fopen(file_name, "rb");

    Node *head = (Node *) calloc(sizeof(Node), 1);
    Node *curr = head;
    Node *last = NULL;
    for (int nread; !feof(f); curr = (Node *) calloc(sizeof(Node), 1)) {
        nread = fread(curr, sizeof(Node), 1, f);
        if (nread != sizeof(Node)) {
            free(curr);
            curr = NULL;
            continue;
        }
        if (last != NULL)  last->next = curr;
        last = curr;
    }
    if (curr != NULL && curr->ip[0] != 0)  free(curr);
    fclose(f);
    return head;
}

void Save(Node *p_first, const char*file_name)
    {
    FILE *f = fopen(file_name,"wb");
    if (p_first != NULL)
        {
        for (Node *p = p_first; p; p=p->next)
            fwrite(p,sizeof(Node),1,f);
        }
    fclose(f);
    }
