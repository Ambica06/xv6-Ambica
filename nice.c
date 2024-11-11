// nice.c (Main program to change nice values from the command line)
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(2, "Usage: nice <pid> <new_nice_value>\n");
        return 1;
    }

    int pid = getpid();
    int new_nice_value;

    if (argc == 3) {
        pid = atoi(argv[1]);  // PID provided
        new_nice_value = atoi(argv[2]);  // New nice value
    } else {
        new_nice_value = atoi(argv[1]);  // Only nice value, apply to current process
    }

    // Change the nice value for the specified PID
    int old_value = nice(pid, new_nice_value);
    if (old_value < 0) {
        printf(2, "Failed to change nice value for PID %d\n", pid);
    } else {
        printf(1, "%d %d\n", pid, old_value);
    }

    exit();
}
