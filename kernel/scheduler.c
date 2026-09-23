#include "../include/scheduler.h"
#include "../include/print.h"
#include "../include/timer.h"
#include "../include/pic.h"

static PCB tasks[MAX_TASKS];
static int current_task = -1;
static int num_tasks = 0;

// The kernel's state when interrupted will be saved in tasks[0]
// We will treat the initial execution context as Task 0

void scheduler_init() {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].active = 0;
    }
    
    // Task 0 is the main kernel thread (shell/idle)
    tasks[0].active = 1;
    num_tasks = 1;
    current_task = 0;
}

void create_task(void (*func)()) {
    if (num_tasks >= MAX_TASKS) return;
    
    int id = num_tasks++;
    
    // Initialize stack for the new task
    // Stack grows downwards, so start at the top
    uint32_t *stack = (uint32_t *)&tasks[id].stack[STACK_SIZE - 4];
    
    // Simulate an interrupt frame (what iret expects)
    *stack = 0x202; // EFLAGS (Interrupts enabled: bit 9 is 1)
    stack--;
    *stack = 0x08;  // CS (Code Segment)
    stack--;
    *stack = (uint32_t)func; // EIP (Instruction Pointer)
    stack--;
    
    // Simulate pusha (8 registers)
    *stack = 0; // EAX
    stack--;
    *stack = 0; // ECX
    stack--;
    *stack = 0; // EDX
    stack--;
    *stack = 0; // EBX
    stack--;
    *stack = 0; // ESP (ignored by popa)
    stack--;
    *stack = 0; // EBP
    stack--;
    *stack = 0; // ESI
    stack--;
    *stack = 0; // EDI
    
    tasks[id].esp = (uint32_t)stack;
    tasks[id].active = 1;
}

// Called directly from assembly IRQ0
uint32_t schedule(uint32_t current_esp) {
    // Acknowledge the timer interrupt
    timer_handler();
    pic_send_eoi(0);

    if (num_tasks <= 1) {
        return current_esp; // Nothing to switch to
    }

    // Save the stack pointer of the task that was just interrupted
    tasks[current_task].esp = current_esp;

    // Round-robin to the next active task
    do {
        current_task = (current_task + 1) % num_tasks;
    } while (!tasks[current_task].active);

    // Return the stack pointer of the new task
    // The assembly stub will mov esp, eax and then popa/iret
    return tasks[current_task].esp;
}

int get_num_tasks() {
    return num_tasks;
}

int get_current_task_id() {
    return current_task;
}

int is_task_active(int id) {
    if (id < 0 || id >= MAX_TASKS) return 0;
    return tasks[id].active;
}
