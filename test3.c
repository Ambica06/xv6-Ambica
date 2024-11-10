// test3.c
#include "types.h"
#include "user.h"

int main() {
    int pid = getpid();  // Get the current process ID

    // Test setting nice value to the maximum valid value
    printf(1, "Setting nice value to maximum (5) for PID %d\n", pid);
    int old_value = nice(pid, 5);  // Maximum valid nice value
    if(old_value<0) {
        printf(1, "Failed to change nice value for PID: %d \n", pid);
    }
    else
    printf(1, "Old nice value for PID %d: %d\n", pid, old_value);

    // Test setting nice value to the minimum valid value
    printf(1, "Setting nice value to minimum (1) for PID %d\n", pid);
    old_value = nice(pid, 1);  // Minimum valid nice value
    if(old_value<0) {
        printf(1, "Failed to change nice value for PID: %d \n", pid);
    }
    else
    printf(1, "Old nice value for PID %d: %d\n", pid, old_value);

    // Test setting a valid nice value in the middle of the range
    printf(1, "Setting nice value to 4 for PID %d\n", pid);
    old_value = nice(pid, 4);  // A middle-ground nice value
    if(old_value<0) {
        printf(1, "Failed to change nice value for PID: %d \n", pid);
    }
    else
    printf(1, "Old nice value for PID %d: %d\n", pid, old_value);

    // Test completed
    printf(1, "Test3 completed\n");
    exit();
}
