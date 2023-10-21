#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define ALPHABET_N 26
#define ALPHABET_START 'A'
#define ALPHABET_END 'Z'
#define LC_OFFSET 'a' - 'A'

enum error {SUCCESS = 0, FILE_NOT_FOUND = 1, FILE_READ_ERROR = 2};

typedef struct char_stat {
    char chr;
    int count;
    int lineStarts;
} CharStat;

CharStat *countChars(char *filename, int *error);
int attempt_add_count(CharStat *char_stats, char c, int mode);
CharStat *init_char_stats();


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
CharStat *countChars(char *filename, int *error) {
    *error = SUCCESS;
    if (access(filename, F_OK) == -1) {
        *error = FILE_NOT_FOUND;
        return NULL;
    }
    if (access(filename, R_OK) == -1) {
        *error = FILE_READ_ERROR;
        return NULL;
    }

    CharStat *char_stats = init_char_stats();
    FILE *fp = fopen(filename, "r");
    char *line = NULL;

    while (getline(&line, NULL, fp) != -1) {
        attempt_add_count(char_stats, line[0], 1);
        for (int i=1; line[i] != '\0'; i++) {
            attempt_add_count(char_stats, line[i], 0);
        }
    }

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
        char_stats[i].count = 0;
        char_stats[i].lineStarts = 0;
    }
    return char_stats;
}


/** @brief Attempt to increase the count for the given char in the given char_stat array.
 * 
 * Given a char_stat array and a character, this function attempts to increase the
 * count for that character in the array. If the character is not an alphabet character,
 * the function does nothing. If the character is an alphabet character, the function
 * increases the count for that character in the array. If the character is lowercase,
 * the function increases the count for the uppercase version of the character. If mode
 * is 1, the function also increases the lineStarts count for the character in the array.
 * 
 * @param char_stats The char_stat array to update
 * @param c The character to update the count for
 * @param mode Whether to update the lineStarts count as well
 * 
 * @return 1 if the character count was successfully increased, 0 if nothing happened
*/
int attempt_add_count(CharStat *char_stats, char c, int mode) {
    c = toupper(c);
    if (c < ALPHABET_START && c > ALPHABET_END) {
        return 0;
    }
    char_stats[c-ALPHABET_START].count++;
    if (mode == 1) char_stats[c-ALPHABET_START].lineStarts++;
    
    return 1;
}


int main(int argc, char **argv) {
    // if (argc < 2) {
    //     printf("%s expects at least one argument.\n Try: %s <filename>\n", argv[0], argv[0]);
    //     return 1;
    // }


    return 0;
}

