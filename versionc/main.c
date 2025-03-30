#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "cpu.h"  // Include our CPU header

// Global flag for program execution
int running = 1;

// Signal handler for clean exit
void handle_signal(int sig) {
    printf("\nCaught signal %d, exiting...\n", sig);
    running = 0;
}

// Function prototypes for our monitoring modules
void initialize_monitor();
void cleanup_monitor();
void update_system_stats();
void display_stats();

int main() {
    // Register signal handler for Ctrl+C
    signal(SIGINT, handle_signal);
    
    // Initialize the monitor
    initialize_monitor();
    
    printf("System Monitor Started. Press Ctrl+C to exit.\n");
    
    // We need to initialize our stats before the first display
    update_system_stats();
    
    // Main loop
    while (running) {
        sleep(1);  // Wait for a second
        update_system_stats();
        display_stats();
    }
    
    // Cleanup before exit
    cleanup_monitor();
    
    return 0;
}

// Initialize any resources needed by the monitor
void initialize_monitor() {
    printf("Initializing system monitor...\n");
    cpu_init();  // Initialize CPU monitoring
}

// Release any resources used by the monitor
void cleanup_monitor() {
    printf("Cleaning up resources...\n");
    // No cleanup needed for CPU monitoring yet
}

// Update system statistics
void update_system_stats() {
    // Update CPU stats
    cpu_update();  
}

// Display the current system statistics
void display_stats() {
    // Get and display CPU usage
    float usage = cpu_get_usage();
    if (usage >= 0) {
        printf("CPU Usage: %.1f%%\r", usage);
        fflush(stdout);
    } else {
        printf("CPU: Error reading data\r");
        fflush(stdout);
    }
}