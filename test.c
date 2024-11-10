#include "types.h"
#include "user.h"

// Function declaration for the main function in nice.c
int main(int argc, char *argv[]); // Declare the main function from nice.c

void test_invalid_pid() {
    char *args[] = {"nice", "99999", "3"}; // Invalid PID
    main(3, args); // Call the main function from nice.c with invalid PID
}

void test_out_of_bounds_nice_value() {
    char *args[] = {"nice", "0", "0"}; // Out-of-bounds value
    main(3, args); // Call the main function from nice.c with out-of-bounds value
}

void test_nice_value_change() {
    char *args_lower[] = {"nice", "2", "2"}; // Lower value
    char *args_higher[] = {"nice", "4", "4"}; // Higher value
    main(3, args_lower); // Call the main function from nice.c to change to lower value
    main(3, args_higher); // Call the main function from nice.c to change to higher value
}

int main(int argc, char *argv[]) {
    // Test invalid PID
    test_invalid_pid();

    // Test out-of-bounds nice value
    test_out_of_bounds_nice_value();

    // Test changing nice value
    test_nice_value_change();

    return 0; // Ensure main always returns an integer value
}