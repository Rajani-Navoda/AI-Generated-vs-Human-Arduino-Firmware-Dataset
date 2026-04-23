// Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256 // Define a buffer size for incoming messages

// Function to simulate sending a message
void sendMessage(const char *message) {
    printf("Sending: %s\n", message);
}

// Function to simulate receiving a message
void receiveMessage(char *buffer, size_t size) {
    printf("Enter message: ");
    if (fgets(buffer, size, stdin) != NULL) {
        // Remove newline character from the input
        buffer[strcspn(buffer, "\n")] = 0;
    }
}

// Main function
int main() {
    char buffer[BUFFER_SIZE]; // Buffer to hold received messages

    while (1) {
        // Receive a message
        receiveMessage(buffer, sizeof(buffer));

        // Check for exit condition
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting program.\n");
            break; // Exit the loop if the user types "exit"
        }

        // Send back the received message
        sendMessage(buffer);
    }

    return 0; // Successful termination of the program
}
