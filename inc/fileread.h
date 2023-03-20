/** @file fileread.h
 * 
 * @brief Functions to access and read the contents of a text file.
 *
 */ 

#ifndef FILEREAD_H
#define FILEREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

_Static_assert(_SC_NPROCESSORS_CONF != -1, "Failed to retrieve number of processors");
#define NUM_CORES (size_t) sysconf(_SC_NPROCESSORS_CONF)

#define PROC_STAT_PATH "/proc/stat"
#define CHUNK_SIZE  64

void **get_CPU_data(const char* filepath);

#endif /* FILEREAD_H */

