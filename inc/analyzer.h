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

} CPU_data;

void init_demo_CPU_data(CPU_data *CPU, CPU_data *CPU_prev);
float calculate_CPU_usage_percentage(CPU_data *CPU, CPU_data *CPU_prev);

#endif /* ANALYZER_H */

