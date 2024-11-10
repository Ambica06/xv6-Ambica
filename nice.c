#include "types.h"
#include "user.h"

// Function to change the nice value
void change_nice_value(int pid, int new_nice_value) {
    int old_nice_value = nice(pid, new_nice_value);
    if (old_nice_value < 0) {
        printf(2, "Failed to change nice value for PID %d\n", pid);
    } else {
        printf(1, "%d %d\n", pid, old_nice_value);
    }
}

// Function to run tests
void run_tests() {

    // Test 1: Invalid PID
    int invalid_pid = 99999; // Assuming this PID does not exist
    printf(1, "Testing with invalid PID: %d\n", invalid_pid);
    change_nice_value(invalid_pid, 3); // Test changing nice value for an invalid PID

    // Test 2: Out-of-bounds nice value
    int valid_pid = getpid(); // Get the current process ID for testing
    printf(1, "Testing with out-of-bounds nice value for PID: %d\n", valid_pid);
    change_nice_value(valid_pid, 0); // Test changing to an out-of-bounds value (0)

    // Test 3: Valid nice value change
    printf(1, "Testing valid nice value change for PID: %d\n", valid_pid);
    change_nice_value(valid_pid, 2); // Change to a valid nice value
    change_nice_value(valid_pid, 4); // Change to another valid nice value

    // Test 4: Another invalid PID
    printf(1, "Testing with another invalid PID: %d\n", invalid_pid);
    change_nice_value(invalid_pid, 5); // Test changing nice value for another invalid PID

    printf(1, "Testing by passing only the nice value %d\n", 3);
    change_nice_value(getpid(), 3);
    printf(1, "Tests completed.\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(2, "Usage: nice <pid> <new_nice_value>\n");
        run_tests(); // Run tests if no arguments are provided
        return 1;
    }

    int pid = getpid();
    int new_nice_value;

    if(argv[1]) {
        pid = atoi(argv[1]);
        new_nice_value = atoi(argv[2]);
    } else {
        new_nice_value = atoi(argv[2]);
    }

    // Call the function to change the nice value
    nice(pid, new_nice_value);

    return 0;
}
