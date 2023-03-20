#include "analyzer.h"

CPU_data_t *CPU_data_init(size_t size) {
    CPU_data_t *CPU = malloc(sizeof(CPU_data_t));

    CPU->size = size + 1;
    CPU->core_data = malloc(sizeof(core_data_t) * CPU->size);
    
    for (size_t i = 0; i < CPU->size; i++) {
        CPU->core_data[i].user       = 0;
        CPU->core_data[i].nice       = 0;
        CPU->core_data[i].system     = 0;
        CPU->core_data[i].idle       = 0;
        CPU->core_data[i].iowait     = 0;
        CPU->core_data[i].irq        = 0;
        CPU->core_data[i].softirq    = 0;
        CPU->core_data[i].steal      = 0;
        CPU->core_data[i].guest      = 0;
        CPU->core_data[i].guest_nice = 0;

        CPU->core_data[i].non_idle   = 0;
        CPU->core_data[i].total      = 0;
    }
    return CPU;
}

void process_CPU_data(CPU_data_t *CPU, char **data) {
    for (size_t i = 0; i < CPU->size; i++) {
        sscanf(data[i], "%*s %u %u %u %u %u %u %u %u %u %u", 
        &CPU->core_data[i].user, 
        &CPU->core_data[i].nice, 
        &CPU->core_data[i].system, 
        &CPU->core_data[i].idle, 
        &CPU->core_data[i].iowait, 
        &CPU->core_data[i].irq, 
        &CPU->core_data[i].softirq, 
        &CPU->core_data[i].steal, 
        &CPU->core_data[i].guest, 
        &CPU->core_data[i].guest_nice);
    }
}

void print_CPU_data(CPU_data_t *CPU) {
    printf("|----------------------------------|\n");
    for (size_t i = 0; i < CPU->size; i++) {
        printf("cpu[%zu]: %d %d %d %d %d %d %d %d %d %d\n", i, 
        CPU->core_data[i].user, 
        CPU->core_data[i].nice, 
        CPU->core_data[i].system, 
        CPU->core_data[i].idle, 
        CPU->core_data[i].iowait, 
        CPU->core_data[i].irq, 
        CPU->core_data[i].softirq, 
        CPU->core_data[i].steal, 
        CPU->core_data[i].guest, 
        CPU->core_data[i].guest_nice);
    }
}

void store_CPU_data(CPU_data_t *CPU_prev, CPU_data_t *CPU_curr) {
    for (size_t i = 0; i < CPU_prev->size; i++) {
        CPU_prev->core_data[i].user       = CPU_curr->core_data[i].user;
        CPU_prev->core_data[i].nice       = CPU_curr->core_data[i].nice;
        CPU_prev->core_data[i].system     = CPU_curr->core_data[i].system;
        CPU_prev->core_data[i].idle       = CPU_curr->core_data[i].idle;
        CPU_prev->core_data[i].iowait     = CPU_curr->core_data[i].iowait;
        CPU_prev->core_data[i].irq        = CPU_curr->core_data[i].irq;
        CPU_prev->core_data[i].softirq    = CPU_curr->core_data[i].softirq;
        CPU_prev->core_data[i].steal      = CPU_curr->core_data[i].steal;
        CPU_prev->core_data[i].guest      = CPU_curr->core_data[i].guest;
        CPU_prev->core_data[i].guest_nice = CPU_curr->core_data[i].guest_nice;

        CPU_prev->core_data[i].non_idle   = CPU_curr->core_data[i].non_idle;
        CPU_prev->core_data[i].total      = CPU_curr->core_data[i].total;
    }
}

void CPU_data_clear(CPU_data_t *CPU) {
    free(CPU->core_data);
    free(CPU);
}

CPU_usage_t *CPU_usage_init(size_t size) {
    CPU_usage_t *CPU_usage = malloc(sizeof(CPU_usage_t));
    CPU_usage->size = size + 1;
    
    CPU_usage->core_usage = malloc(sizeof(float) * CPU_usage->size);

    for (size_t i = 0; i < CPU_usage->size; i++) {
        CPU_usage->core_usage[i] = 0;
    }

    return CPU_usage;
}

void calculate_CPU_usage_percentage(CPU_data_t *CPU_prev, CPU_data_t *CPU_curr, CPU_usage_t *CPU_usage) {
    double prev_idle = 0, idle = 0, prev_non_idle = 0, non_idle = 0, prev_total = 0, total = 0, total_d = 0, idle_d = 0;
    
    for (size_t i = 0; i < CPU_usage->size; i++) {
        prev_idle = CPU_prev->core_data[i].idle + CPU_prev->core_data[i].iowait;
        idle = CPU_curr->core_data[i].idle + CPU_curr->core_data[i].iowait;

        prev_non_idle = CPU_prev->core_data[i].user + CPU_prev->core_data[i].nice + CPU_prev->core_data[i].system + CPU_prev->core_data[i].irq + CPU_prev->core_data[i].softirq + CPU_prev->core_data[i].steal;
        non_idle = CPU_curr->core_data[i].user + CPU_curr->core_data[i].nice + CPU_curr->core_data[i].system + CPU_curr->core_data[i].irq + CPU_curr->core_data[i].softirq + CPU_curr->core_data[i].steal;

        prev_total = prev_non_idle + prev_idle;
        total = non_idle + idle;

        total_d = total - prev_total;
        idle_d = idle - prev_idle;

        CPU_usage->core_usage[i] = (float) ((total_d - idle_d) / total_d) * 100;
    }
}

void print_CPU_usage(CPU_usage_t *CPU_usage) {
    printf("|--------------------|\n");
    for (size_t i = 0; i < CPU_usage->size; i++) {
        printf("  cpu[%zu]: %.3f%%\n", i, CPU_usage->core_usage[i]);
    }
}

void CPU_usage_clear(CPU_usage_t *CPU_usage) {
    free(CPU_usage->core_usage);
    free(CPU_usage);
}
