/** @file fileread.c
 * 
 * @brief Functions to access and read the contents of the /proc/stat file.
 *
 * @par       
 * 
 */

#include "fileread.h"

void **get_CPU_data(const char* filepath) {

    /* important to add 1, as the first line is the general cpu usage data */
    size_t N_lines = (size_t) NUM_CORES + 1;

    FILE* pFile = fopen(filepath, "r");

    if (pFile == NULL) {
        perror("Error opening /proc/stat");
        exit(EXIT_FAILURE);
    }
    
    char **lines = malloc(sizeof(char *) * N_lines);

    size_t line_cnt = 0;
    size_t char_cnt = 0;
    char c;

    while (line_cnt < N_lines) {
        c = (char) fgetc(pFile);

        if (ferror(pFile)) {
            perror("Problem during /proc/stat reading");
            exit(EXIT_FAILURE);
        }

        if (char_cnt % CHUNK_SIZE == 0 && char_cnt != 0) {
            size_t new_size = char_cnt + CHUNK_SIZE;
            lines[line_cnt] = realloc(lines[line_cnt], sizeof(char *) * new_size);
        }

        if (char_cnt == 0) lines[line_cnt] = malloc(CHUNK_SIZE);

        if (c == '\n') {
            /* resize the current line according to the char_cnt */
            lines[line_cnt] = realloc(lines[line_cnt], char_cnt + 1);
            lines[line_cnt][char_cnt] = '\0';

            char_cnt = 0;
            line_cnt++;
        }
        else {
            lines[line_cnt][char_cnt] = c;
            char_cnt++;
        }
    }
 
    fclose(pFile);

    return (void **) lines;
}
