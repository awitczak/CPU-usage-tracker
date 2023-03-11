#include "stdio.h"

// custom includes
#include "fileread.h"
#include "analyzer.h"

CPU_data CPU, CPU_prev;

int main() {

    get_data("/proc/stat", &CPU);

    init_demo_CPU_data(&CPU, &CPU_prev);

    printf("CPU usage: %f", calculate_CPU_usage_percentage(&CPU, &CPU_prev));

    return 0;
}
