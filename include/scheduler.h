#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#define MAX_TASKS 4
#define STACK_SIZE 1024

typedef struct {
    uint8_t stack[STACK_SIZE];
    uint32_t esp;
    int active;
} PCB;

void scheduler_init();
uint32_t schedule(uint32_t current_esp);
void create_task(void (*func)());
int get_num_tasks();
int get_current_task_id();
int is_task_active(int id);

#endif
