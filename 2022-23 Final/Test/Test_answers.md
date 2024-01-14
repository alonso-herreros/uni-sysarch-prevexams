# TEST

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 |
|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|----|----|----|----|
| c | c | a | b |   | b | d | b | c | d  |    | a  | a  | a  | a  | a  | a  | b  | a  | a  |

## Question 1

* [ ] a) (x,y) = (3,6)
* [ ] b) (x,y) = (4,8)
* [X] c) The code does not compile
* [ ] d) Segmentation Fault

## Question 2

* [ ] a) `printf("%d", *(*ptr_2+i));`
* [ ] b) `printf("%d", **ptr_2[i]);`
* [X] c) `printf("%d", *ptr_1[i]);`
* [ ] d) `printf("%d", **ptr_2->i);`

## Question 3

* [X] a) `Val: 123 | Endptr: a`
* [ ] b) `Val: 123 | Endptr: ` (the value of endptr is \0 and nothing is printed since \0 is a non-printable
         character)
* [ ] c) `Val: -1 | Endptr: 0`
* [ ] d) The process terminates when the strtol line is reached since the text is not a number.

## Question 4

* [ ] a) The code works perfectly, no memory leaks and the output is a 1.
* [ ] b) The code works perfectly, the output is a 1, but there is a memory leak (3 allocs, 2 frees)
* [ ] c) The code works perfectly, the output is a 1, but there are two memory leaks (3 allocs, 1 free)
* [ ] d) The code does not work because it is not possible to perform operations of the type `operation =
         functionName`

## Question 5

* [ ] a) Only A is printed
* [ ] b) Only B is printed
* [ ] c) AB is printed
* [ ] d) Neither A nor B is printed because an error occurs before the while is reached.

## Question 6

* [ ] a) git push
* [X] b) git pull
* [ ] c) git commit -m “example1_created.c”
* [ ] d) git commit -m “example1_created.c” and afterwards, git push

## Question 7

* [ ] a) A possible output of the terminal is “root 1 2 3 4”.
* [ ] b) A possible output of the terminal is “root 1 1 2 2 3 3 4”.
* [ ] c) A possible output of the terminal is “root 1 2 2 2 3 3 4”.
* [X] d) A possible output of the terminal is “root 1 2 2 3 3 4 4”.

## Question 8

* [ ] a) The child process becomes a zombie once i==5
* [X] b) The child process becomes an orphan once i==5
* [ ] c) The child process dies once i==5, because it is killed by the father
* [ ] d) The father and the son die once i==5, since the father kills the son and then the father ends

## Question 9

* [ ] a) The parent process enters the while(1) loop after 3 seconds and then waits indefinitely while the
child process prints “question 9” until there is a SIGINT signal.
* [ ] b) The child process becomes a zombie once the SIGALRM signal is triggered.
* [X] c) The child process prints “question 9” for 3 seconds and then terminates successfully, just before
the parent.
* [ ] d) The parent process terminates after 3 seconds and then the child process becomes orphan and
continues to display the text “question 9”.

## Question 10

* [ ] a) Write the text “question 10” in the file q10, overwriting the current content of the file.
* [ ] b) Write the text “question 10” in the file q10, adding the content at the end of the file.
* [ ] c) A permissions error occurs if it is executed by the user himself
* [X] d) A blockage occurs in the terminal

## Question 11

* [ ] a) Memory space
* [ ] b) Id
* [ ] c) Stack
* [ ] d) Registers

## Question 12

* [X] a) None of the others
* [ ] b) Multiple extensión
* [ ] c) Mutua from Texas
* [ ] d) Multiple exclusion

## Question 13

* [X] a) It can encapsulate an integer type variable
* [ ] b) It can limit the use of a static method
* [ ] c) It can be used in an instance of a class as a lock
* [ ] d) A class can be used as a lock

## Question 14

* [X] a) Compilation error
* [ ] b) 6
* [ ] c) 8
* [ ] d) 4

## Question 15

* [X] a) It wait for a notify
* [ ] b) It waits for the end of the process
* [ ] c) It waits for the end of the program
* [ ] d) It waits for the end of its descendant processes

## Question 16

* [X] a) A semaphore light initialized to 1 is used
* [ ] b) A semaphore initialized to 0 is used
* [ ] c) A semaphore initialized to N, with n>1, is used
* [ ] d) It is not possible to build a mutex with semaphores

## Question 17

* [X] a) semaforo.relase();
* [ ] b) semaforo.acquire();
* [ ] c) semaforo.notify();
* [ ] d) synchronized(semaforo) {notify();}

## Question 18

* [ ] a) Signal-and-continue
* [X] b) Signal-and-wait
* [ ] c) Signal-and-exit
* [ ] d) Signal-and-release

## Question 19

* [X] a) All their methods must be public
* [ ] b) They encapsulate critical resources
* [ ] c) They contain condition variables
* [ ] d) They must be defined in a class

## Question 20

* [X] a) 1320
* [ ] b) 0123
* [ ] c) 3210
* [ ] d) 3120
