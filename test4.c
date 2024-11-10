// test4.c
#include "types.h"
#include "user.h"

int main() {
    int pid = getpid();  // Get the current process ID

    // Changing nice value multiple times
    printf(1, "Changing nice value for PID %d\n", pid);
    nice(pid, 1);
    nice(pid, 2);
    nice(pid, 3);
    nice(pid, 4);
    nice(pid, 5);

    // Verify the changes
    printf(1, "Final nice value for PID %d (should be 5): %d\n", pid, nice(pid, 5));

    // Test completed
    printf(1, "Test4 completed\n");
    exit();
}
