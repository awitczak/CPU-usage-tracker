/** @file fileread.h
 * 
 * @brief Functions to access and read the contents of a text file.
 *
 * @par       
 * 
 */ 

#ifndef FILEREAD_H
#define FILEREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROC_STAT_PATH "/proc/stat"
#define CHUNK_SIZE  64

void **get_CPU_data(const char* filepath);

#endif /* FILEREAD_H */

