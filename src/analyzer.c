#include "analyzer.h"

void init_demo_CPU_data(CPU_data_t*CPU, CPU_data_t*CPU_prev) {
    CPU_prev->user = 596365;
    CPU_prev->nice = 792;
    CPU_prev->system = 121328;
    CPU_prev->idle = 9103716;
    CPU_prev->iowait = 3445;
    CPU_prev->irq = 0;
    CPU_prev->softirq = 11101;
    CPU_prev->steal = 0;
    CPU_prev->guest = 0;
    CPU_prev->guest_nice = 0;

    CPU->user = 619826;
    CPU->nice = 793;
    CPU->system = 125326;
    CPU->idle = 9325694;
    CPU->iowait = 3512;
    CPU->irq = 0;
    CPU->softirq = 11390;
    CPU->steal = 0;
    CPU->guest = 0;
    CPU->guest_nice = 0;

    CPU_prev->non_idle = 0;
    CPU->non_idle = 0;

    CPU_prev->total = 0;
    CPU->total = 0;
}

float calculate_CPU_usage_percentage(CPU_data_t*CPU, CPU_data_t*CPU_prev) {

    CPU_prev->idle = CPU_prev->idle + CPU_prev->iowait;
    CPU->idle = CPU->idle + CPU->iowait;

    CPU_prev->non_idle = CPU_prev->user + CPU_prev->nice + CPU_prev->system + CPU_prev->irq + CPU_prev->softirq + CPU_prev->steal;
    CPU->non_idle = CPU->user + CPU->nice + CPU->system + CPU->irq + CPU->softirq + CPU->steal;

    CPU_prev->total = CPU_prev->idle + CPU_prev->non_idle;
    CPU->total = CPU->idle + CPU->non_idle;

    double totald = CPU->total - CPU_prev->total;
    double idled = CPU->idle - CPU_prev->idle;

    return (totald - idled) / totald;
}