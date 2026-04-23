// Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define BUFFER_SIZE 256

// Function to simulate sending a message
void sendMessage(const char *message) {
    printf("Sending: %s\n", message);
}

// Function to simulate receiving a message
void receiveMessage(char *buffer, size_t size) {
    printf("Enter message: ");
    fgets(buffer, size, stdin);
    // Remove newline character from the input
    buffer[strcspn(buffer, "\n")] = 0;
}

// Main function
int main() {
    char buffer[BUFFER_SIZE];

    while (1) {
        // Receive a message
        receiveMessage(buffer, sizeof(buffer));

        // If the message is "exit", break the loop
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Send back the received message
        sendMessage(buffer);
    }

    return 0;
}