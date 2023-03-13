/** @file fileread.c
 * 
 * @brief Functions to access and read the contents of the /proc/stat file.
 *
 * @par       
 * 
 */

#include "fileread.h"

#define CHUNK_SIZE  64
#define N_LINES     16

char **get_data(char* filepath) {
    
    FILE* pFile = fopen(filepath, "r");
    
    if (pFile == NULL) {
        printf("Can't open the given file!\n");
        // return -1;
        exit(1);
    }
    else printf("File opened successfully!\n");

    char **lines = malloc(sizeof(char *) * N_LINES);

    size_t line_cnt = 0;
    size_t char_cnt = 0; // variable used to track the amount of characters in each line
    char c;

    while (!feof(pFile)) {
                
        c = fgetc(pFile);   // read a character from file

        if (ferror(pFile))
        {
            printf("Error reading from file.\n");
            // return -2;
            exit(1);
        }

        if (char_cnt == 0) lines[line_cnt] = malloc(CHUNK_SIZE);

        if (c == '\n') {    // line detected

            if (line_cnt % N_LINES == 0) {
                size_t new_size = line_cnt + N_LINES;
                lines = realloc(lines, sizeof(char *) * new_size);
            }

            // resize the current line according to the char_cnt
            lines[line_cnt] = realloc(lines[line_cnt], char_cnt + 1);

            // add a null terminator at the end
            lines[line_cnt][char_cnt] = '\0';

            // check if it is a line with the cpu information
            if (!strstr(lines[line_cnt], "cpu")) {
                break; // if a line does not contain the "cpu" substring anymore, exit the loop
            }

            char_cnt = 0;
            line_cnt++;
        }
        else {
            lines[line_cnt][char_cnt] = c;
            char_cnt++;
        }

        if (char_cnt % CHUNK_SIZE == 0 && char_cnt != 0) {
            // printf("Resizing the array.\n");

            size_t new_size = char_cnt + CHUNK_SIZE;
            lines[line_cnt] = realloc(lines[line_cnt], sizeof(char *) * new_size);
        }
    }

    /* resizing the line count */
    lines = realloc(lines, sizeof(char *) * line_cnt);

    /* freeing will be done after the analyzer thread finishes processing the data from the queue */
    // for (size_t i = 0; i < line_cnt; i++) {
    //     free(lines[i]);
    // } 
    // free(lines);

    /* close the file */
    fclose(pFile);

    return lines;
}