#ifndef MEMORY_H
#define MEMORY_H

typedef struct 
{
    unsigned long used;
    unsigned long avilable;
    unsigned long total;
    unsigned long total_swap;
    unsigned long free_swap;
    
    
} memory;

void memory_init();
float memory_get_info();
void memory_update();

#endif   /* MEMORY_H */
