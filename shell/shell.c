#include "../include/shell.h"
#include "../include/print.h"
#include "../include/string.h"
#include "../include/timer.h"
#include "../include/scheduler.h"
#include "../include/mm.h"

void shell_execute_command(char *cmd) {
    if (strlen(cmd) == 0) {
        return;
    }

    if (strcmp(cmd, "help") == 0) {
        print_str("Available commands:\n");
        print_str("  help   - Show commands\n");
        print_str("  clear  - Clear screen\n");
        print_str("  about  - OS information\n");
        print_str("  echo   - Print text (e.g. echo hello)\n");
        print_str("  mem    - Memory information\n");
        print_str("  tasks  - Task/scheduler information\n");
        print_str("  uptime - System uptime\n");
    } 
    else if (strcmp(cmd, "clear") == 0) {
        clear_screen();
    } 
    else if (strcmp(cmd, "about") == 0) {
        print_str("MinOS - A Lightweight Operating System\n");
        print_str("Developed for educational purposes.\n");
    } 
    else if (strncmp(cmd, "echo", 4) == 0) {
        if (cmd[4] == ' ') {
            print_str(cmd + 5);
        }
        print_str("\n");
    } 
    else if (strcmp(cmd, "mem") == 0) {
        uint32_t total, used, free;
        get_memory_stats(&total, &used, &free);
        print_str("Kernel Heap Statistics:\n");
        print_str("  Total: "); print_dec(total); print_str(" bytes\n");
        print_str("  Used:  "); print_dec(used); print_str(" bytes\n");
        print_str("  Free:  "); print_dec(free); print_str(" bytes\n");
    } 
    else if (strcmp(cmd, "crash") == 0) {
        print_str("Triggering divide-by-zero exception...\n");
        int a = 1;
        int b = 0;
        int c = a / b;
        (void)c; // Prevent unused variable warning
    } 
    else if (strcmp(cmd, "tasks") == 0) {
        int n = get_num_tasks();
        print_str("Tasks running: ");
        print_dec(n);
        print_str("\n");
        for (int i = 0; i < n; i++) {
            print_str("  Task ");
            print_dec(i);
            if (i == 0) print_str(" (Kernel/Shell)");
            if (is_task_active(i)) print_str(" - Active\n");
            else print_str(" - Suspended\n");
        }
    } 
    else if (strcmp(cmd, "uptime") == 0) {
        uint32_t uptime = get_uptime();
        print_str("Uptime: ");
        print_dec(uptime);
        print_str(" seconds\n");
    } 
    else {
        print_str("Unknown command: ");
        print_str(cmd);
        print_str("\nType 'help' for a list of commands.\n");
    }
}
