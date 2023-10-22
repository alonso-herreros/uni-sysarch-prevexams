#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


#define BUFFER_SZ 1024
#define PIPE_W 1
#define PIPE_R 0


enum errors {
    SUCCESS = 0, NOT_A_WORD,
    FILE_NOT_FOUND, FILE_NOT_PERMISSION, FILE_READ_ERROR,
    FORK_ERROR, PIPE_ERROR, PIPE_W_ERROR, PIPE_R_ERROR
};

static const char *ERROR_MSGS[] = {
    "Success",
    "Word provided is not a word (contains non-alphanumerical characters)",
    "File not found",
    "File read access not granted",
    "Error while reading from file",
    "Error forking",
    "Error setting up pipes. Call a plumber",
    "Error writing to pipe.",
    "Error reading from pipe."
};


typedef struct word_count {
    int count;
    int including_lines;
    int total_lines;
} WordCount;

int int_indexof(int *arr, int arrsz, int x);
WordCount count_word(char *word, char *filepath, int* error);
static int process_char(char c, char *word);
pid_t *count_word_forkall(char *word, char **filenames, int filec, int fd[filec][2], int *error);
pid_t count_word_fork(char *word, char *filename, int fd[2], int *error);


int int_indexof(int *arr, int arrsz, int x)
{
    for (int i=0; i<arrsz; i++) {
        if (arr[i]==x) return i;
    }
    return -1;
}


/** @brief Count the amount of times a word appears in a file, the number of lines,
 * and the number of lines that include this word.
 * 
 * Given a word and a filepath, attempt to read the indicated files, and count:
 * * The number of thimes a word appears in the file
 * * The number of lines that include the given word
 * * The total number of lines in the file
 * 
 * @param word The word to look for in the file
 * @param filepath The file to scan
 * 
 * @return a WordCount object
 */
WordCount count_word(char *word, char *filepath, int *error)
{
    WordCount wc = {0};
    for (int i=0; word[i] != '\0'; i++) { // Word check
        char c = word[i];
        if (c<'0' || (c>'9'&&c<'A') || (c>'Z'&&c<'a') || c>'z') { // Not alphanumerical
            *error = NOT_A_WORD;
            return wc;
        }
    }
    if (access(filepath, F_OK) == -1) { // FIle existence check
        *error = FILE_NOT_FOUND;
        return wc;
    }
    if (access(filepath, R_OK) == -1) { // File read access check
        *error = FILE_NOT_PERMISSION;
        return wc;
    }

    FILE *fp = fopen(filepath, "r");
    char c;
    while((c = fgetc(fp))) {
        int analysis = process_char(c, word);
        if (analysis&1) {
            wc.total_lines++;
            if (analysis&2)  wc.including_lines++;
        }
        if (analysis&4) wc.count++;
        if (c==EOF)  break;
    }

    fclose(fp);

    return wc;
}

/** @brief Given a character and a word, process it according to this exercise.
 * 
 * @param c The character to process
 * @param word The word to try to find
 * 
 * @return A flag with the analysis result:
 * * 1 if the character is a newline,
 * * 2 if the current line includes the word
 * * 4 if the character just completed the word.
 * * 8 if the character is EOF.
 */
static int process_char(char c, char *word)
{
    static int progress = 0; // 0 means we may start scanning the next char
    static int included_in_line = 0;
    static int found = 0;
    
    int out = 0;

    if (c<'0' || (c>'9'&&c<'A') || (c>'Z'&&c<'a') || c>'z') { // Not alphanumerical
        if (found) { // The last character was the end of the target word
            included_in_line = 1;
            out += 4; // Word found
        }
        progress = 0; // We may start scanning next char
    }
    else if (progress != -1) {
        found = 0; // Reset this
        if (c == word[progress]) { // On the right track
            progress++; 
            if (word[progress] == '\0')  found = 1; // We'll check if next char is \s
        }
        else  progress = -1; // -1 means the next char is not the start of a word
    }

    out += 2*included_in_line;

    if (c=='\n') {
        out += 1; // Newline found
        included_in_line = 0; // This execution will still say this was true though
    }
    else if (c==EOF) {
        out += 1+8; // No need to worry about resets
    }

    return out;
}


int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Not enough arguments (2 expected)\n");
        exit(EXIT_FAILURE);
    }

    int error;

    int fds[argc-2][2];
    pid_t pids[argc-2]; // = count_word_forkall(argv[1], &(argv[2]), argc-2, fds, &error);

    pids[0] = count_word_fork(argv[1], argv[2], fds[0], &error);
    int i =0 ;
    int status;
    int pid = wait(&status);
    printf("Process %d finished with status %d (%s)\n",
        pid, status, status? "error":"success"
    );
    if (status) {
        int errorn = 0;
        close(fds[i][PIPE_W]);
        read(fds[i][PIPE_R], &errorn, sizeof(int));
        close(fds[i][PIPE_R]);

        printf("  Error: %s", ERROR_MSGS[errorn]);
    }
    else {
        WordCount wc;
        close(fds[i][PIPE_W]);
        read(fds[i][PIPE_R], &wc, sizeof(WordCount));
        close(fds[i][PIPE_R]);

        // printf("Word '%s' in file '%s'.\n");
        printf("  Found %d times in %d out of %d lines\n",
            wc.count, wc.including_lines, wc.total_lines
        );
    }
    for (int i=0; i<argc-2; i++) {
    }

    exit(EXIT_SUCCESS);
}


pid_t *count_word_forkall(char *word, char **filenames, int filec, int fds[filec][2], int *error)
{
    pid_t *pids = calloc(filec, sizeof(pid_t));

    for (int i=0; i<filec; i++) {
        
    }
    
    return pids;
}


pid_t count_word_fork(char *word, char *filename, int fd[2], int *error)
{
    if (pipe(fd) == -1) {
        *error = PIPE_ERROR;
        return -2;
    }

    pid_t pid;
    if ((pid = fork()) == -1) {
        *error = FORK_ERROR;
        return -1;
    }
    else if(pid==0) {
        WordCount wc = count_word(word, filename, error);
        close(fd[PIPE_R]);
        if (*error) {
            write(fd[PIPE_W], error, sizeof(int));
            _exit(EXIT_FAILURE);
        }
        int written = write(fd[PIPE_W], &wc, sizeof(WordCount));
        close(fd[PIPE_W]);
        if (written == -1) {
            _exit(EXIT_FAILURE);
        }
        _exit(EXIT_SUCCESS);
    }
    return pid;
}

