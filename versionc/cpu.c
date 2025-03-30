#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Global variables to store current and previous CPU stats
static CPUStats prev_stats;
static CPUStats current_stats;

// Forward declaration of static function
static int read_cpu_stats(CPUStats *stats);

// Initialize CPU monitoring
void cpu_init() {
    memset(&prev_stats, 0, sizeof(CPUStats));
    memset(&current_stats, 0, sizeof(CPUStats));
    
    // Initialize first reading
    if (read_cpu_stats(&prev_stats) < 0) {
        fprintf(stderr, "Failed to initialize CPU monitoring\n");
    }
}

// Read CPU statistics from /proc/stat
static int read_cpu_stats(CPUStats *stats) {
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Error opening /proc/stat");
        return -1;
    }
    
    // Read the first line which contains overall CPU stats
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        perror("Error reading /proc/stat");
        fclose(fp);
        return -1;
    }
    
    // Parse the line to extract CPU stats
    // Format: "cpu user nice system idle iowait irq softirq steal guest guest_nice"
    if (sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
              &stats->user, &stats->nice, &stats->system, &stats->idle,
              &stats->iowait, &stats->irq, &stats->softirq, &stats->steal,
              &stats->guest, &stats->guest_nice) < 4) {
        fprintf(stderr, "Error parsing CPU stats\n");
        fclose(fp);
        return -1;
    }
    
    fclose(fp);
    return 0;
}

// Update CPU stats
void cpu_update() {
    // Move current stats to previous stats
    memcpy(&prev_stats, &current_stats, sizeof(CPUStats));
    
    // Read new current stats
    if (read_cpu_stats(&current_stats) < 0) {
        fprintf(stderr, "Error updating CPU stats\n");
    }
}

// Get CPU usage percentage
float cpu_get_usage() {
    // Calculate deltas
    unsigned long long prev_idle = prev_stats.idle + prev_stats.iowait;
    unsigned long long current_idle = current_stats.idle + current_stats.iowait;
    
    unsigned long long prev_non_idle = prev_stats.user + prev_stats.nice + 
                                      prev_stats.system + prev_stats.irq + 
                                      prev_stats.softirq + prev_stats.steal;
    
    unsigned long long current_non_idle = current_stats.user + current_stats.nice + 
                                         current_stats.system + current_stats.irq + 
                                         current_stats.softirq + current_stats.steal;
    
    unsigned long long prev_total = prev_idle + prev_non_idle;
    unsigned long long current_total = current_idle + current_non_idle;
    
    // Calculate difference
    unsigned long long total_delta = current_total - prev_total;
    unsigned long long idle_delta = current_idle - prev_idle;
    
    float cpu_usage = 0.0;
    if (total_delta != 0) {
        cpu_usage = 100.0 * (total_delta - idle_delta) / total_delta;
    }
    
    return cpu_usage;
}