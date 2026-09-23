#include "../include/shell.h"
#include "../include/print.h"
#include "../include/string.h"

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
        // Stub for now. Full implementation in Day 8
        print_str("[Stub] Total Heap: 1 MiB, Used: 64 bytes, Free: 1048512 bytes\n");
    } 
    else if (strcmp(cmd, "tasks") == 0) {
        // Stub for now. Full implementation in Day 7
        print_str("[Stub] Task 1 (Running), Task 2 (Ready), Task 3 (Ready)\n");
    } 
    else if (strcmp(cmd, "uptime") == 0) {
        // Stub for now. Full implementation in Day 6
        print_str("[Stub] Uptime: 0 seconds\n");
    } 
    else {
        print_str("Unknown command: ");
        print_str(cmd);
        print_str("\nType 'help' for a list of commands.\n");
    }
}
