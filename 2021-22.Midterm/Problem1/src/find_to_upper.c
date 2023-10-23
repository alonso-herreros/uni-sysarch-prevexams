#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


#define BUFFER_SIZE 1024


enum errors {
    SUCCESS = 0,
    ARGC_ERROR, ARG_MAY_ERROR, FILE_NOT_FOUND, FILE_NOT_PERMISSION
};

static const char *ERR_MSGS[] = {
    "Success.\n",
    "Wrong number of arguments (%d received, %d-%d expected)\n",
    "The third argument must be \"MAY\" or be omitted (%s found).\n",
    "File '%s' not found.\n",
    "Couldn't read file '%s' (access denied).\n"
};


int main(int argc, char **argv) {
    // Arg checks
    if (argc < 3 || argc > 4) { // Number of args
        fprintf(stderr, ERR_MSGS[ARGC_ERROR], argc, 2, 3);
        exit(EXIT_FAILURE);
    }

    int may = 0;
    if (argc == 4) { // Third argument must be MAY or else omitted
        if (strcmp(argv[3], "MAY") == 0)  may = 1;
        else {
            fprintf(stderr, ERR_MSGS[ARG_MAY_ERROR], argv[3]);
            exit(EXIT_FAILURE);
        }
    }

    char *filename = argv[1];
    char *str = argv[2];
    int str_len = strlen(str);

    // File checks
    if (access(filename, F_OK) == -1) { // File existence check
        fprintf(stderr, ERR_MSGS[FILE_NOT_FOUND], filename);
        exit(EXIT_FAILURE);
    }
    if (access(filename, R_OK) == -1) { // File read access check
        fprintf(stderr, ERR_MSGS[FILE_NOT_PERMISSION], filename);
    }

    FILE *fp = fopen(filename, "r");

    size_t nchars = BUFFER_SIZE;
    char *line = malloc(BUFFER_SIZE);
    while (getline(&line, &nchars, fp) != -1) {
        char *strpos;
        if ((strpos = strstr(line, str)) == NULL)  continue;
        if (may) {
            do {
                for (int i=0; i<str_len; i++) {
                    strpos[i] = toupper(strpos[i]);
                }
            } while ((strpos = strstr(strpos, str)) != NULL);
        }

        printf(line);
    }

    free(line);
    fclose(fp);

    return EXIT_SUCCESS;
}
