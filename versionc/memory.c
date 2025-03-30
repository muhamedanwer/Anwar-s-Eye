#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static memory prev_stats;
static memory current_stats;

static int read_memory(memory *stats){
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL){
        perror("Error opening /proc/meminfo");
        return -1;
    }
    char buffer[256];
   if (fgets(buffer, sizeof(buffer), fp) == NULL){
        perror("Error reading /proc/stat");
        fclose(fp);
        return -1;
    }
}

void memory_update(){

    memcpy(&prev_stats, &current_stats, sizeof(memory));

    if
}