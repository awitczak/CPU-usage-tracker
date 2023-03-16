#include "analyzer.h"

void CPU_data_init(CPU_data_t *CPU, size_t size) {
    CPU->size = size + 1;
    CPU->CPU_data = malloc(sizeof(core_data_t) * CPU->size);

    for (size_t i = 0; i < CPU->size; i++) {
        CPU[i].CPU_data = malloc(sizeof(core_data_t));

        CPU[i].CPU_data->user       = 0;
        CPU[i].CPU_data->nice       = 0;
        CPU[i].CPU_data->system     = 0;
        CPU[i].CPU_data->idle       = 0;
        CPU[i].CPU_data->iowait     = 0;
        CPU[i].CPU_data->irq        = 0;
        CPU[i].CPU_data->softirq    = 0;
        CPU[i].CPU_data->steal      = 0;
        CPU[i].CPU_data->guest      = 0;
        CPU[i].CPU_data->guest_nice = 0;

        CPU[i].CPU_data->non_idle   = 0;
        CPU[i].CPU_data->total      = 0;
    }
}

void process_CPU_data(CPU_data_t *CPU, char **data) {
    for (size_t i = 0; i < CPU->size; i++) {
        sscanf(data[i], "%*s %u %u %u %u %u %u %u %u %u %u", &CPU[i].CPU_data->user, &CPU[i].CPU_data->nice, &CPU[i].CPU_data->system, &CPU[i].CPU_data->idle, &CPU[i].CPU_data->iowait, &CPU[i].CPU_data->irq, &CPU[i].CPU_data->softirq, &CPU[i].CPU_data->steal, &CPU[i].CPU_data->guest, &CPU[i].CPU_data->guest_nice);
    }
}

void print_CPU_data(CPU_data_t *CPU) {
    for (size_t i = 0; i < CPU->size; i++) {
        printf("cpu[%ld]: %d %d %d %d %d %d %d %d %d %d\n", i, CPU[i].CPU_data->user, CPU[i].CPU_data->nice, CPU[i].CPU_data->system, CPU[i].CPU_data->idle, CPU[i].CPU_data->iowait, CPU[i].CPU_data->irq, CPU[i].CPU_data->softirq, CPU[i].CPU_data->steal, CPU[i].CPU_data->guest, CPU[i].CPU_data->guest_nice);
    }
}

// float calculate_CPU_usage_percentage(CPU_data_t *CPU, CPU_data_t *CPU_prev) {

    // CPU_prev->idle = CPU_prev->idle + CPU_prev->iowait;
    // CPU->idle = CPU->idle + CPU->iowait;

    // CPU_prev->non_idle = CPU_prev->user + CPU_prev->nice + CPU_prev->system + CPU_prev->irq + CPU_prev->softirq + CPU_prev->steal;
    // CPU->non_idle = CPU->user + CPU->nice + CPU->system + CPU->irq + CPU->softirq + CPU->steal;

    // CPU_prev->total = CPU_prev->idle + CPU_prev->non_idle;
    // CPU->total = CPU->idle + CPU->non_idle;

    // double totald = CPU->total - CPU_prev->total;
    // double idled = CPU->idle - CPU_prev->idle;

    // return (totald - idled) / totald;
// }