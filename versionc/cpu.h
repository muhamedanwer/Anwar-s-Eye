#ifndef CPU_H
#define CPU_H

// Structure to hold CPU statistics
typedef struct {
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
    unsigned long long guest;
    unsigned long long guest_nice;
} CPUStats;

// Function prototypes
void cpu_init();
float cpu_get_usage();
void cpu_update();

#endif /* CPU_H */