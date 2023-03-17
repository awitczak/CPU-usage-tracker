/** @file analyzer.h
 * 
 * @brief Functions to produce the desired output from the acquired data.
 *
 * @par       
 * 
 */ 

#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    uint32_t user;
    uint32_t nice;
    uint32_t system;
    uint32_t idle;
    uint32_t iowait;
    uint32_t irq;
    uint32_t softirq;
    uint32_t steal;
    uint32_t guest;
    uint32_t guest_nice;

    uint32_t non_idle;
    uint32_t total;

} core_data_t;

typedef struct {
    size_t size;
    core_data_t *core_data;
} CPU_data_t;

typedef struct {
    size_t size;
    float *core_usage;
} CPU_usage_t;

CPU_data_t *CPU_data_init(size_t size);
void process_CPU_data(CPU_data_t *CPU, char **data);
void print_CPU_data(CPU_data_t *CPU);
void store_CPU_data(CPU_data_t *CPU_prev, CPU_data_t *CPU_curr);
void CPU_data_clear(CPU_data_t *CPU);

CPU_usage_t *CPU_usage_init(size_t size);
void calculate_CPU_usage_percentage(CPU_data_t *CPU_prev, CPU_data_t *CPU_curr, CPU_usage_t *CPU_usage);
void print_CPU_usage(CPU_usage_t *CPU_usage);
void CPU_usage_clear(CPU_usage_t *CPU_usage);

#endif /* ANALYZER_H */

