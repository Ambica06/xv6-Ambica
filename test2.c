// test2.c
#include "types.h"
#include "user.h"

int main() {
    int invalid_pid = 99999;  // A non-existent PID

    // Try to change nice value of a non-existent process
    printf(1, "Trying to change nice value for invalid PID %d\n", invalid_pid);
    int old_value = nice(invalid_pid, 5);  // Try setting nice for an invalid PID
    if (old_value < 0) {
        printf(1, "Failed to change nice value: Invalid PID\n");
    }

    // Test completed
    printf(1, "Test2 completed\n");
    exit();
}
