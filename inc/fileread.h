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

#include "analyzer.h"

int get_data(char* filepath, CPU_data *CPU);
int get_CPU_data(char* filepath, CPU_data *CPU);

#endif /* FILEREAD_H */

