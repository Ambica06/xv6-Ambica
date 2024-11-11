#include "types.h"
#include "user.h"
#include "fcntl.h"

#define BUFFER_SIZE 1024

// Convert integer to string
void itoa(int num, char *str) {
    int i = 0, temp_num = num, j;
    if (num == 0) {
        str[i++] = '0';
    } else {
        while (temp_num > 0) {
            str[i++] = (temp_num % 10) + '0';
            temp_num /= 10;
        }
        // Reverse the string
        for (j = 0; j < i / 2; j++) {
            char temp = str[j];
            str[j] = str[i - j - 1];
            str[i - j - 1] = temp;
        }
    }
    str[i] = '\0';
}

// Append a string to a buffer
void append_to_buffer(char *buffer, int *offset, const char *str) {
    while (*str && *offset < BUFFER_SIZE - 1) {
        buffer[(*offset)++] = *str++;
    }
}

// Function to check if a number is prime
int is_prime(int num) {
    int i;
    if (num < 2) return 0;
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

void generate_primes(int limit, char *buffer, int *offset, int nice_val) {
    int num = 2;
    char num_str[10];
    char pid_str[10];
    char nice_val_str[10];
    itoa(getpid(), pid_str);
    itoa(nice_val, nice_val_str);  // Convert nice value to string

    while (num <= limit && *offset < BUFFER_SIZE - 20) { // Reserve space for each line
        if (is_prime(num)) {
            append_to_buffer(buffer, offset, "PID ");
            append_to_buffer(buffer, offset, pid_str);
            append_to_buffer(buffer, offset, ": Prime ");
            itoa(num, num_str);
            append_to_buffer(buffer, offset, num_str);
            append_to_buffer(buffer, offset, " Nice ");
            append_to_buffer(buffer, offset, nice_val_str);  // Append nice value
            append_to_buffer(buffer, offset, "\n");
        }
        num++;
    }
    buffer[*offset] = '\0'; // Null-terminate the string
}

int main(int argc, char *argv[]) {
    int num_children = 5;
    int max_prime = 25;
    int fd[2];  // Pipe for communication
    int i;
    if (argc > 1) num_children = atoi(argv[1]);
    if (argc > 2) max_prime = atoi(argv[2]);

    pipe(fd);

    printf(1, "Parent process PID %d: Forking %d children.\n", getpid(), num_children);

    for (i = 0; i < num_children; i++) {
        int pid = fork();
        if (pid == 0) { // Child process
            close(fd[0]);  // Close read end in child

            int nice_value = ( i > 3 ) ? 3 : 4;
            nice(getpid(), nice_value);  // Set nice value

            char buffer[BUFFER_SIZE];
            int offset = 0;
            generate_primes(max_prime, buffer, &offset, nice_value);

            write(fd[1], buffer, offset);  // Write the buffer to the pipe
            close(fd[1]);  // Close write end after sending data
            exit();  // Exit the child process
        }
    }

    close(fd[1]);  // Close write end in parent

    // Parent reads from pipe and prints in order
    char buffer[BUFFER_SIZE];
    int n;
    while ((n = read(fd[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';  // Null-terminate the string
        printf(1, "%s", buffer);
    }

    close(fd[0]);  // Close read end

    for (i = 0; i < num_children; i++) {
        wait();  // Wait for all child processes to finish
    }

    printf(1, "All child processes finished.\n");
    exit();
}
