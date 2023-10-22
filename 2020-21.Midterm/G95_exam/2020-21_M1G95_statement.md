## Systems Architedcture

# 2020-21 Midterm 1 (Group 95)
_December 2020_

_Universidad Carlos III de Madrid_

---

### Section 1 (5 points)
Given the name of a text file, implement a function that calculates and 
returns the number of times each of the letters from A to Z (not counting the ñ and Ñ) starts a 
word. In addition, you should also return how many times each of the letters starts a new line. 
The function must handle possible errors properly and inform the user of them, returning the 
value of the error. 
* The function must NOT print anything on the screen.
* The function should check if the file exists and if it can be read.
* The function must not have any memory leaks.
* We assume there are 26 letters in the alphabet.
* The function should be case insensitive.
* The upper and lower case ñ will not be considered.
* Word delimiters in a text: space, tab, end of line and different punctuation marks.

You can define constants and new data types if you consider it necessary.


### Section 2 (5 points)
Implement a main program that receives as arguments the name of 1 or more text files. 
* If it does not receive at least 1 input argument, it should finish.
* The program will create as many children as text file names it has received as argument, and the 
necessary communication channels with them. Each child will process an argument of the program.
* It will wait for each child to send through the corresponding pipe, the result of processing its 
corresponding text file. The parent process will print this information, showing the number of times 
each letter of the alphabet is start of a word and of a line this file processed by this specific child.
* The paren proces will wait for all his children to finish, printing the exit status information for each of 
them.

Each child process:
* For the corresponding file, it will use the function in the previous section to calculate the number of 
times each letter starts a word and the number of times the letter starts a line.
* Through the corresponding pipe, it will send its parent process if any error has happened in the 
processing and if the processing was succesful, the process will send the result of processing the file.
* It will finish.