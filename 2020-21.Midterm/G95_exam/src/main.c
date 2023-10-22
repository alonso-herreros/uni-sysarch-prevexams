#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>


#define ALPHABET_N 26
#define ALPHABET_START 'A'
#define ALPHABET_END 'Z'
#define LC_OFFSET 'a' - 'A'
#define BUFFER_SIZE 1024
#define PIPE_W 1
#define PIPE_R 0


enum error {SUCCESS = 0,
    FILE_NOT_FOUND, FILE_PERMISSION_ERROR, FILE_READ_ERROR,
    FORK_ERROR, PIPE_ERROR, PIPE_W_ERROR, PIPE_R_ERROR
};

static const char *ERROR_MSGS[] = {
    "Success",
    "File not found",
    "File permission denied",
    "Error reading file",
    "Error forking",
    "Error creating pipes. Call a plumber",
    "Error writing to pipe",
    "Error reading from pipe"
};

typedef struct char_stat {
    char chr;
    int wordStarts;
    int lineStarts;
} CharStat;

int int_indexof(int *array, int arrsz, int x);
CharStat *count_chars(char *filename, int *error);
CharStat *init_char_stats();
int attempt_add_count(CharStat *char_stats, char c, int mode);
void print_char_counts(CharStat *char_stats);
pid_t count_chars_fork(char *filename, int *fd, int *error);
pid_t *count_chars_forkall(int filen, char **filepaths, int fds[filen][2], int *error);


int int_indexof(int *array, int arrsz, int x)
{
    for (int i=0; i<arrsz; i++) {
        if (array[i]==x) {
            return i;
        }
    }
    return -1;
}


/** @brief Counts the occurrences of each alphabet character in a file (case-insensitive)
 * 
 * Given a filename, this function counts the occurrences of each alphabet
 * character in the file, as well as how many times each one starts a line.
 * The counts for each character are stored in a char_stat struct, which contains
 * the character itself, the number of occurrences, and the number of times it
 * starts a line. The function returns an array of char_stat structs, one for
 * each character in the alphabet. The counts are case-insensitive, so 'A' and
 * 'a' are counted as the same character. The char_stat structs will be associated
 * with the uppercase version of the character.
 * 
 * @param filename The name of the file to read
 * @param error A pointer to an integer to store the error code if any
 * 
 * @return A pointer to an array of char_stat structs, or NULL if an error occurred
 * 
 * @warning The caller is responsible for freeing the array returned
*/
CharStat *count_chars(char *filename, int *error) {
    *error = SUCCESS;
    if (access(filename, F_OK) == -1) {
        *error = FILE_NOT_FOUND;
        return NULL;
    }
    if (access(filename, R_OK) == -1) {
        *error = FILE_PERMISSION_ERROR;
        return NULL;
    }

    CharStat *char_stats = init_char_stats();
    FILE *fp = fopen(filename, "r");
    char *line = calloc(BUFFER_SIZE, sizeof(char));
    size_t nchars = BUFFER_SIZE;

    while (getline(&line, &nchars, fp) != -1) {
        attempt_add_count(char_stats, line[0], 1);
        for (int i=1; line[i] != '\0'; i++) {
            char c = line[i];
            if(c<'A'||(c>'Z'&&c<'a')||c>'z') {
                attempt_add_count(char_stats, line[i+1], 0);
            }
        }
    }
    if (!feof(fp)) {
        *error = FILE_READ_ERROR;
        return NULL;
    }

    free(line);

    return char_stats;
}


/** @brief Initializes an array of char_stat structs with the alphabet characters and 0 counts.
 * 
 * This function initializes an array of char_stat structs, one for each character in the
 * alphabet, in uppercase. The counts for each character are set to 0.
 * 
 * @return A pointer to an array of char_stat structs
 * 
 * @warning The caller is responsible for freeing the array returned
*/
CharStat *init_char_stats() {
    CharStat *char_stats = malloc(ALPHABET_N * sizeof(CharStat));
    for (int i=0; i<ALPHABET_N; i++) {
        char_stats[i].chr = ALPHABET_START + i;
        char_stats[i].wordStarts = 0;
        char_stats[i].lineStarts = 0;
    }
    return char_stats;
}


/** @brief Attempt to increase the count for the given char in the given char_stat array.
 * 
 * Given a char_stat array and a character, this function attempts to increase the
 * count for that character in the array. If the character is not an alphabet character,
 * the function does nothing. If the character is an alphabet character, the function
 * increases the word starts count for that character in the array. If the character is
 * lowercase, the function increases the count for the uppercase version of the character.
 * If mode is 1, the function also increases the line starts count for the character in the
 * array.
 * 
 * @param char_stats The char_stat array to update
 * @param c The character to update the count for
 * @param mode Whether to update the lineStarts count as well
 * 
 * @return 1 if the character count was successfully increased, 0 if nothing happened
*/
int attempt_add_count(CharStat *char_stats, char c, int mode) {
    c = toupper(c);
    if (c < ALPHABET_START || c > ALPHABET_END) {
        return 0;
    }
    char_stats[c-ALPHABET_START].wordStarts++;
    if (mode == 1) char_stats[c-ALPHABET_START].lineStarts++;
    
    return 1;
}


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("%s expects at least one argument.\n Try: %s <filename>\n", argv[0], argv[0]);
        return 1;
    }

    pid_t *pids;
    int fds[argc-1][2];
    int error;
    pids = count_chars_forkall(argc-1, &(argv[1]), fds, &error);
    if (error) {
        printf("error %s", ERROR_MSGS[error]);
        exit(EXIT_FAILURE);
    }
    
    int result;
    for (int i=0; i<argc-1; i++) {
        int pid = wait(&result);
        if (result) {
            printf("Process %d errored (exit %d).\n", pid, result);
            read(fds[i][PIPE_R], &error, sizeof(int));
            printf("  Error %d (%s)\n ", error, ERROR_MSGS[error]);
            continue;
        }

        printf("\nProcess %d ended successfully (exit: %d)\n", pid, result);
        printf("File: %s\n", argv[int_indexof(pids, argc-1, pid)+1]);
        CharStat char_stats[ALPHABET_N];
        // wait(NULL);
        close(fds[i][PIPE_W]);
        int read_n = read(fds[i][PIPE_R], char_stats, ALPHABET_N*sizeof(CharStat));
        close(fds[i][PIPE_R]);
        if (read_n < ALPHABET_N*sizeof(CharStat)){
            printf("Error: %s\n", ERROR_MSGS[PIPE_ERROR]);
        }

        print_char_counts(char_stats);
    }

    return 0;
}


void print_char_counts(CharStat *char_stats) {
    printf("Char - Word starts : Line starts\n");
    for (char c=ALPHABET_START; c <= ALPHABET_END; c++) {
        CharStat cs = char_stats[c-ALPHABET_START]; // Letter 'A' must be at 0
        printf("  %c  -      %6d : %d\n", cs.chr, cs.wordStarts, cs.lineStarts);
    }
}


/** @brief Creates `filen` children processes to count the characters in each file given.
 * 
 * Assuming `filepaths` contains `filen` `char*` entries, this function creates a child
 * process and a pipe for the child process to write to. Each child will call `count_chars`
 * and write the resulting `CharStat`. 
 * 
 * @param filen The number of file paths passed
 * @param filepaths A `char*` array containing `filen` filepaths.
 * @param fds File descriptors to use as pipes.
 * @param error Pointer to int to store error code in.
 * 
 * @return A malloc'd `filen`-long `pid_t` array with the process IDs of each created child.
 * 
 * @warning The caller must free the returned array.
*/
pid_t *count_chars_forkall(int filen, char **filepaths, int fds[filen][2], int *error)
{
    pid_t *pids = calloc(filen, sizeof(pid_t));
    int error_last = (*error = SUCCESS); // Reset both
    for (int i=0; i<filen; i++) {
        pids[i] = count_chars_fork(filepaths[i], fds[i], &error_last);
        *error = error_last? error_last : *error;
    }
    return pids;
}


pid_t count_chars_fork(char *filename, int *fd, int *error)
{
    *error = SUCCESS;
    if (pipe(fd) < 0) {
        *error = PIPE_ERROR;
        return -2;
    }

    pid_t pid;
    if ((pid=fork()) < 0) {
        *error = FORK_ERROR;
        return -1;
    }
    else if (pid == 0) { // Child process
        CharStat *char_stats = count_chars(filename, error);
        close(fd[PIPE_R]);
        if (!*error) {
            int written = write(fd[PIPE_W], char_stats, ALPHABET_N*sizeof(CharStat));
            close(fd[PIPE_W]);
            if (written != -1)  _exit(EXIT_SUCCESS);
        }
        write(fd[PIPE_W], error, sizeof(int));
        _exit(EXIT_FAILURE);
    }


    return pid;
}
