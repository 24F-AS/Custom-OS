#include "./include/print.h"
#include <stdint.h>
#include "./include/mm.h"
#include "./include/keyboard.h"
#include "./include/idt.h"
#include "./include/timer.h"
#include "./include/scheduler.h"

extern uint8_t _kernel_end;
#define KHEAP_SIZE (1024 * 1024)

// Simple delay
void delay() {
    volatile unsigned long i;
    for (i = 0; i < 50000000UL; i++);
}

void task1() {
    while(1) {
        // print_str("T1 ");
        delay();
    }
}

void task2() {
    while(1) {
        // print_str("T2 ");
        delay();
    }
}

void kernel_main() {
    terminal_init();
    print_str("=====================================\n");
    print_str("       MinOS - Lightweight OS        \n");
    print_str("=====================================\n");
    print_str("Members: Ansh, Saurav, Vedant\n\n");

    /* Initialize kernel heap */
    kheap_init(&_kernel_end, KHEAP_SIZE);
    print_str("kheap initialized (1 MiB)\n");

    /* Initialize Scheduler */
    scheduler_init();
    create_task(task1);
    create_task(task2);
    print_str("Scheduler initialized with 3 tasks (Kernel + T1 + T2)\n");

    /* Initialize Timer to 100 Hz */
    timer_init(100);

    /* Initialize IDT and PIC */
    idt_install();

    /* Initialize keyboard state */
    keyboard_init();

    /* Print the shell prompt */
    print_str("\nminos> ");

    /* 
     * Infinite loop. This is technically "Task 0".
     * CPU wakes up on keyboard and timer interrupts.
     * The timer interrupt will context switch to T1 and T2 automatically!
     */
    while (1) {
        __asm__ volatile("hlt");
    }
}

