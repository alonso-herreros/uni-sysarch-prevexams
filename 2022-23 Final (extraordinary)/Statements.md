## **Systems Architecture**

# **Final Exam - December 20th 2023**

*Academic year 2021-2022*
*Telematics Engineering Department - Universidad Carlos III de Madrid*

---

## General instructions
The use of additional materials on paper or other devices, the use of headphones, communication with
other people, leaving the seat during the exam, or the use of additional software is not allowed.

# TEST
*(3 points, 30 minutes)*

### Instructions
There is only one correct answer. Unanswered questions do not add or subtract, correct answers add 0.3
points and incorrect answers subtract 0.1 points.

### ANSWER SHEET
Select your answer for each question. Questions unanswered here will NOT be considered

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---|---|---|---|---|---|---|---|----|
|   |   |   |   |   |   |   |   |   |    |

## Question 1
Given the following code, what is the output?

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char *str = strdup("3.14 is pi");
    char *endptr;
    float val;
    val = strtof(str, &endptr);
    printf("val:%f%s\n" , val, endptr);
}
```

* [ ] a) val:3.140000
* [ ] b) val:3.140000 is pi
* [ ] c) The code does not work and produces an error.
* [ ] d) The code works but provides a different output compared to the other options, and it has a memory
         leak of 10 bytes.

## Question 2
Given the following hash table that stores country data using the continent as a key, what is the missing
line to insert France into the table?

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char country_code[3];
    int population;
    struct node* next;
};

int main(){
    int size = 5;
    struct node** hash_table = (struct node **) calloc(sizeof(struct node*),size);
    struct node* spain = (struct node *) malloc(sizeof(struct node));
    strcpy(spain->country_code,"ESP");
    spain->population = 47;
    struct node* france = (struct node *) malloc(sizeof(struct node));
    strcpy(france->country_code,"FRA");
    france->population = 67;
    hash_table[0] = spain;
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
}
```

* [ ] a) hash_table[1] = france;
* [ ] b) hash_table[0]->next = france;
* [ ] c) hash_table[x] = france; Assuming x is a value that cannot be known beforehand due to the lack of
information about key indices.
* [ ] d) None of the other options is valid.

## Question 3
In the terminal, three commands are executed as shown below. What will happen after executing the third
command?

```text
vit121:~/Desktop/AS_2022/extra> ls -lisa
total 52
17202056539  0 drwxr-xr-x.  2 0291481 0291481    66 jun 10 12:47 .
25770316010  4 drwxr-xr-x. 21 0291481 0291481  4096 jun 10 11:49 ..
17193483248 20 -rwxr-xr-x.  1 0291481 0291481 16712 jun 10 12:00 q1
17202537696  4 -rw-r--r--.  1 0291481 0291481   203 jun 10 12:00 q1.c
17202537695 20 -rwxr-xr-x.  1 0291481 0291481 16760 jun 10 12:47 q2
17202537697  4 -rw-r--r--.  1 0291481 0291481   743 jun 10 12:47 q2.c
vit121:~/Desktop/AS_2022/extra> ls
q1  q1.c  q2  q2.c
vit121:~/Desktop/AS_2022/extra> ls | grep .c > q3
```

* [ ] a) The terminal will be blocked since q3 is a FIFO.
* [ ] b) A file will be written containing q1.c and q2.c.
* [ ] c) The pipe q3 (not FIFO) will be created, storing the concatenation of the outputs of ls and grep .c.
* [ ] d) The pipe q3 (not FIFO) will be created, storing the result of grep .c applied to the output of ls.

## Question 4
Given the following code, Which of the following sentences is correct?

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

pid_t child = 0;

void handler1(int s){
    printf("Hello %i (my father) \n", getppid());
    sleep(1);
    kill(getppid(), SIGTSTP);
}

void handler2(int s){
    printf("Hello %i (my child) \n", child);
    sleep(1);
    kill(child, SIGTSTP);
}

void handler3(int s){
    kill(child,SIGTSTP);
}

int main(){
    signal(SIGTSTP, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    if((child = fork())<0){ exit(EXIT_FAILURE); }
    else if(child == 0){
        signal(SIGTSTP, handler1);
        while(1) { pause(); }
    } else {
                    signal(SIGTSTP,handler2);
        signal(SIGINT,handler3);
        while(1) { pause(); }
    }
}
```

* [ ] a) After performing a CTRL-C, the parent sends a greeting message to the child, then the child
         replies, and both processes then terminate.
* [ ] b) After performing a CTRL-C, the parent sends a greeting message to the child, then the child sends a
         greeting message back to the parent, and these greetings continue to be sent indefinitely in turns.
* [ ] c) After performing a CTRL-C, the child sends a greeting message to the parent, then the parent sends a
         greeting message back to the child, and these greetings continue to be sent indefinitely in turns.
* [ ] d) After performing a CTRL-C, the child dies because it is not associated with handler3 and, as there
         is no wait, it becomes a zombie.

## Question 5
What is the command `git checkout` for?

* [ ] a) To create a new branch.
* [ ] b) To update the local repository copy to have the content of the remote.
* [ ] c) To upload all new content from the local repository to the remote repository.
* [ ] d) To configure the user and email to be used in the Git account.

## Question 6
Given the following code, what happens when it is executed?

```c
class T1 extends Thread{
    public void run() {
        for(int i=0; i<10; i++)
            System.out.println("tic");
    }
}

class T2 implements Runnable{
    public void run() {
        for(int i=0; i<10; i++)
            System.out.println("toc");
    }
}

public class Q6 {
    public static void main(String[] args) {
        T1 t1 = new T1();
        T2 t2 = new T2();
        t1.start();
        t2.start();
    }
}
```

* [ ] a) Tic and toc will be displayed 10 times each, appearing alternately (first tic, then toc, and so on).
* [ ] b) Tic and toc will be displayed 10 times each, but they will not be synchronized.
* [ ] c) The code does not work because T2 does not inherit from Thread.
* [ ] d) The code does not work because T2 is not started correctly.

## Question 7
Given the following code in which there are waiters serving one dish each and diners take a dish and leave,
what can we say about the synchronization of this code?

```c
public class Q7 extends Thread {
    private String profile;
    private int dishes_available;

    public Q7(String profile) {
        this.profile = profile;
    }

    public void run() {
        if(profile.equals("waiter")) { // Waiter
            synchronized(Q7.class) {
            dishes_available++;
            System.out.println("A new dish is available. Total:" + dishes_available);
            Q7.class.notify();
            }
        }
        if(profile.equals("guest")) { // Guest
            synchronized(Q7.class) {
                while(dishes_available==0) {
                    System.out.println("Wait");
                    try {Q7.class.wait();} catch (InterruptedException e) {}
                }
                dishes_available--;
                System.out.println("A dish has been eaten. Total: " + dishes_available);
            }
        }
    }

    public static void main(String args[]) {
        Q7[] waiters = new Q7[10];
        Q7[] guests = new Q7[10];
        for(int i=0; i<10;i++) {
            waiters[i] = new Q7("waiter");
            guests[i] = new Q7("guest");
            guests[i].start();
            waiters[i].start();
        }
    }
}
```

* [ ] a) It does not synchronize properly because the shared variable is not actually shared among all thread¡
s.¿
* [ ] b) It does not synchronize properly because in this case, the Q7 class should use locks with "this" inst¡ead of class locks, as it is currently programmed.
* [ ] c) It does not synchronize properly because the code in the main should be enclosed in synchronized.
* [ ] d) The code works perfectly and synchronizes properly.

## Question 8
The previous problem is transformed into using semaphores, but now it is restricted so that each waiter can
only serve 10 dishes, and each diner eats 10 times. Considering this, we have the following code. What is
the initialization value of the semaphores?

```c
public class Q8 extends Thread {
private String profile;
    private int ident;
    HIDDEN Semaphore semA = new Semaphore(__________);
    HIDDEN Semaphore semB = new Semaphore(__________);
    HIDDEN int dishes_available;

    public Q8(String profile, int ident) {
        this.profile = profile;
        this.ident=ident;
    }

    public void run() {
        if(profile.equals("waiter")) { // Waiter
            for(int i=0;i<10;i++) {
                try{semA.acquire();} catch (InterruptedException e) {}
                __________________ (1)
                __________________ (2)
                __________________ (3)
            }
        }
        if(profile.equals("guest")) { // Guest
                    int eaten_times = 0;
                while(eaten_times<10) {
                    try {semA.acquire();} catch (InterruptedException e) {}
                    if(______________ (4) > 0) {
                        dishes_available--;
                        eaten_times++;
                        _______________ (5)
                    } else {
                        _______________ (6)
                        _______________ (7)
                    }
                    }
        }
    }

    public static void main(String args[]) {
        Q8[] waiters = new Q8[10];
        Q8[] guests = new Q8[10];
        for(int i=0; i<10;i++) {
            waiters[i] = new Q8("waiter",i);
            guests[i] = new Q8("guest",i);
            guests[i].start();
            waiters[i].start();
        }
    }
}
```

* [ ] a) semA = 1, semB = 0
* [ ] b) semA = 0, semB = 1
* [ ] c) semA = 1, semB = 10
* [ ] d) semA = 10, semB = 0

## Question 9
Following the code above, in which of the available slots is it possible that there is a semB.acquire()?

* [ ] a) Slot 2
* [ ] b) Slot 4
* [ ] c) Slot 6
* [ ] d) Another slot

## Question 10
Which of the following statements about monitors is false?

* [ ] a) Condition variables control the progress of threads in the critical section.
* [ ] b) Monitors in Java are implemented with Signal-and-Continue.
* [ ] c) All variables that are part of the critical resource must be private.
* [ ] d) All methods in the monitor must be synchronized.

# PROBLEMS
*(7 points, 180 minutes)*

## PROBLEM 1
*(4 points, 90 minutes)*

The PT-10L20-XA router from the company PocoTráfico S.A., for the purpose of this exercise, is
simply dedicated to receiving messages and forwarding them to their destination. To do this, it examines the
destination IP address of the message and determines which physical device it needs to be transmitted to, for
which it needs to know its MAC address.

This is solved by implementing a list of (IP, MAC) pairs in the Nodes.dat file (which is a binary file).

There is a program written in the C language called Add that adds pairs to this file.

An example of how this program works is as follows:

```txt
[PT-10L20-XA]$ ./Add
usage: ./Add <ip> <mac>
[PT-10L20-XA]$ ./Add 147.6.170.251 FB:7D:30:22:30:3C
--------Node list--------
Empty
-----------------------
--------Node list--------
ip="147.6.170.251" mac="FB:7D:30:22:30:3C"
-----------------------
[PT-10L20-XA]$ ./Add 198.62.208.208 08:D0:96:1C:D1:9C
--------Node list--------
ip="147.6.170.251" mac="FB:7D:30:22:30:3C"
-----------------------
--------Node list--------
ip="147.6.170.251" mac="FB:7D:30:22:30:3C"
ip="198.62.208.208" mac="08:D0:96:1C:D1:9C"
-----------------------
[PT-10L20-XA]$ ./Add 161.151.224.179 57:FC:4D:3D:88:3A
--------Node list--------
ip="147.6.170.251" mac="FB:7D:30:22:30:3C"
ip="198.62.208.208" mac="08:D0:96:1C:D1:9C"
-----------------------
--------Node list--------
ip="147.6.170.251" mac="FB:7D:30:22:30:3C"
ip="198.62.208.208" mac="08:D0:96:1C:D1:9C"
ip="161.151.224.179" mac="57:FC:4D:3D:88:3A"
-----------------------
[PT-10L20-XA]$ ./Add 182.101.216.94 4C:10:83:A4:1B:E6
--------Node list--------
ip="147.6.170.251" mac="FB:7D:30:22:30:3C"
ip="198.62.208.208" mac="08:D0:96:1C:D1:9C"
ip="161.151.224.179" mac="57:FC:4D:3D:88:3A"
-----------------------
--------Node list--------
ip="147.6.170.251" mac="FB:7D:30:22:30:3C"
ip="198.62.208.208" mac="08:D0:96:1C:D1:9C"
ip="161.151.224.179" mac="57:FC:4D:3D:88:3A"
ip="182.101.216.94" mac="4C:10:83:A4:1B:E6"
-----------------------
```

PataPalo S.L. has obtained fragments of the Add program's code and needs an expert like you to complete the
program. They have committed to paying you 10 gold doubloons if you succeed.
However, it won't be easy, as there are some mandatory restrictions that must be followed, or else you won't
get a single coin.

* Respect the original code and use the functions, variables, types, constants, etc. that have been pirated
  whenever possible. Use the functions, even if you haven't answered the questions where they
  are implemented.
* Respecting the original program means, among other things, reading the data file into a linked list of
  Nodes, adding the new node to the end of the list, and saving the list to the file.
* You can use the functions from ASlib.

The first pirated piece is the header of the Add.c file:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define IP_SIZE 20
#define MAC_SIZE 20
#define TRACE printf ("%S:%d\n", __FILE__, __LINE__)

#define FILE_NAME "src/Nodes.dat"
```

Also, we have the node type:

```c
typedef struct Node
    {
    char ip[IP_SIZE];
    char mac[MAC_SIZE];
    struct Node *next;
    } Node;
```

And the functions declarations:

```c
void Verify_args(int ac, char ** av);

Node* New_node(const char*ip, const char *mac);
Node* Add(Node *p_first, Node *p_node);

Node* Read(const char *file_name);
void Save(Node *p_first, const char*file_name);

void Display (Node *p_first);
void Destroy (Node *p_first);
```

* Verify_args debe comprobar que la invocación al programa es correcta.
* New_node debe construir un nuevo nodo a partir de la información de los argumentos
* Add debe añadir el nodo apuntado por p_node a la lista que comienza en p_first
* Read debe leer el archivo dado construyendo la cadena que devuelve con el puntero al primer nodo de la
  lista.
* Save debe salvar la lista que empieza en p_first en el archivo dado.
* Display presenta por pantalla la lista que comienza en p_first.
* Destroy debe liberar la memoria ocupada por la lista.

We are provided the following code as well:

```c
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
```

```c
void Verify_args(int ac, char ** av)
    {
    if (ac != 3)
        {
        printf("usage: %s <ip> <mac>\n", av[0]);
        exit (EXIT_SUCCESS);
        }
    }
```

```c
Node* New_node(const char *ip, const char *mac)
    {
    Node *p_node = malloc(sizeof(Node));
    strncpy(p_node->ip, ip, IP_SIZE);
    strncpy(p_node->mac,mac, MAC_SIZE) ;
    p_node->next = NULL;
    return(p_node) ;
    }
```

```c
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
```

```c
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
```

### Section 1.1
*(0.7 points)*

`Node *Read(const char *filename)`

Write this function that should read the list of nodes from the binary file.

A hint: As when saving the nodes, it has been made as is, when reading them, the last node
will still have next==NULL, and the others will not.

### Section 1.2
*(0.7 points)*

`Node * Add(Node * p_first, Node*p_node)`

Write this function that must add the node given by p_node to the list given by p_first.

Note that Add must return the pointer to the first node in the resulting list.

### Section 1.3
*(0.3 points)*

`void Destroy(Node *p_first)`

Write this function that should free the memory occupied by the list given in the argument.

### ADDENDA

The chief engineering officer at PocoTráfico is a cunning security engineer and has left a bug embedded in
the code, which has cleverly been pirated.  
Now it's time to undo it.

The problem is that, due to hardware limitations, it's not possible for the process triggered when executing
Add to perform both the insertion operation in the file and displaying the status of the list.  
The solution is to create a subprocess that will be responsible for listing the information on the screen.

Communication between both processes will be done using signals (SIGUSR1 and SIGINT).  
When the child process receives a SIGUSR1, it reads and prints the file, and when it finishes, it sends
SIGUSR1 to the parent.  
When the child process receives SIGINT, it terminates.

Let's make this modification by answering the following questions.  
In each question, add the necessary variables as needed.  
You can assume the existence of the remaining functions.

Remember that if a signal is sent and the receiver is not running or has not programmed that signal, it will
be lost. A 1-second pause will be sufficient in this case.

### Section 1.4
*(0.3 points)*

`Child_handler()`

Write this function that should capture the signals received by the child.

### Section 1.5
*(0.7 points)*

`Parent_handler()`

Write this function that should capture the signals received by the parent

### Section 1.6
*(0.3 points)*

`Child_process()`

Write here the code of the child process, to cover the described needs.

### Section 1.7
*(1 point)*

Rewrite the main method according to the new needs, including orderly completion.
In case you want to copy-paste it the original code is:

```c
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
```

## PROBLEM 2
*(1 point, 20 minutes)*

Given the following software solution for the critical section problem, indicate which of the three
fundamental requirements it satisfies and provide a reasoned justification for each answer. Assume that
"turn" is a shared variable that is initialized at the beginning, and the code is executed by two processes,
P0 and P1, as follows:

| Process P0 code |
| --- |

```c
do {
    while (turn == 1);
    // critical section
    turn = 1;
    // reminder section
} while (true);
```

| Process P1 code |
| --- |

```c
do {
    while (turn == 0);
    // critical section
    turn = 0;
    // reminder section
} while (true);
```

## PROBLEM 3
*(2 points, 70 minutes)*

In a library, we have writers who are responsible for writing books, and readers who are responsible for
reading the books written by these writers. However, there is only one computer with writing software, so
only one writer can write at a time. To read, there are three separate reading stations that are independent
of the writing station (in fact, a reader cannot use the writing station to read, even if it is available).
Each reader who visits the library's mission is to read all the books written by the writers,
althoughthey cannot be read until they are written. Furthermore, since the books have a certain
relationship, they must be read in the order of writing (i.e., the second book written is read after the
first, the thirdafter the second, and so on, regardless of the authors). Each book can only be read once,
and to be fair, each time a reader requests a turn to read, they can only read one book.

Taking this into account, you are asked to implement this problem using semaphores. To do this, you should
implement a class that models the writer threads (`Writer`), another class that models the reader threads
(`Reader`), and a `Library` class that contains the `main` method. As additional information, each writer
will write 5 books each time they go to the library, and there will be a simulated writing time of 200 ms and
a reading time of 100 ms. For the `main` method, consider 3 writers and 10 readers, so that each
reader has to read 15 books. Furthermore, it should be ensured that the program terminates correctly,
meaning that all threads must be closed once each one completes its mission (the writer writes 3 books and
the reader reads 15 books).

Note: To try to be fair in the turn of writing and reading, you can make the FIFO queues by adding true as
a second parameter to the necessary semaphores.
