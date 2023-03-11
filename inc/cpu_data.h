/** @file cpu_data.h
 * 
 * @brief Functions to produce the desired output from the acquired data.
 *
 * @par       
 * zzzz
 */ 

#ifndef CPU_DATA_H
#define CPU_DATA_H

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
} CPU_data;

#endif /* CPU_DATA_H */

