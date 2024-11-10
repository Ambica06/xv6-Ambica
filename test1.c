// test1.c
#include "types.h"
#include "user.h"

int main() {
    int pid = getpid();  // Get the current process ID

    // Valid test: Change nice value for the current process
    printf(1, "Changing nice value for PID %d to 5\n", pid);
    int old_value = nice(pid, 5);  // Set nice value to 5
    printf(1, "Old nice value for PID %d: %d\n", pid, old_value);

    // Invalid test: Try setting an out-of-bounds nice value
    printf(1, "Trying to set an invalid nice value for PID %d\n", pid);
    old_value = nice(pid, 100);  // Invalid nice value (too high)
    if (old_value < 0) {
        printf(1, "Failed to set nice value: Out of bounds (%d)\n", 100);
    }

    old_value = nice(pid, -25);  // Invalid nice value (too low)
    if (old_value < 0) {
        printf(1, "Failed to set nice value: Out of bounds (%d)\n", -25);
    }

    // Test completed
    printf(1, "Test1 completed\n");
    exit();
}
