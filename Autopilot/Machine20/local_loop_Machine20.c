/* .+

.context    : aTalk, real time data communication
.title      : random data send/receive closed on local loop
.kind       : c source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Revello - Italy
.creation   : 4-Nov-2019
.copyright  : (c) 2019 Fabrizio Pollastri
.license    : GNU Lesser General Public License version 3

.description

This program sends blocks of random data with random size, the blocks are
transmitted to a local loop and received from the same loop. The received
data is checked against the transmitted data for errors.

.- */

// Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DATA_SIZE 1024 // Maximum size for data blocks
#define LOOP_BUFFER_SIZE (MAX_DATA_SIZE + sizeof(int)) // Buffer to hold data and its size

// Function to simulate sending data over a local loop
void sendData(char* data, int size) {
    // Simulating sending data by just printing it to the console
    // In a real scenario, replace this with actual sending logic
    printf("Sending data: ");
    for (int i = 0; i < size; i++) {
        printf("%02X ", (unsigned char)data[i]);
    }
    printf("\n");
}

// Function to simulate receiving data over a local loop
void receiveData(char* buffer, int* size) {
    // Simulating receiving data by generating random data
    *size = rand() % MAX_DATA_SIZE + 1; // Random size between 1 and MAX_DATA_SIZE
    for (int i = 0; i < *size; i++) {
        buffer[i] = rand() % 256; // Fill with random bytes
    }
}

// Function to check received data against sent data
int checkData(char* sentData, char* receivedData, int size) {
    return memcmp(sentData, receivedData, size) == 0; // Compare memory blocks
}

// Main function
int main() {
    char sentData[MAX_DATA_SIZE];
    char receivedData[MAX_DATA_SIZE];
    int dataSize;

    srand(time(NULL)); // Seed the random number generator

    while (1) {
        // Generate random data to send
        dataSize = rand() % MAX_DATA_SIZE + 1; // Random size
        for (int i = 0; i < dataSize; i++) {
            sentData[i] = rand() % 256; // Fill with random bytes
        }

        // Send data
        sendData(sentData, dataSize);

        // Simulate receiving the data (in reality, this would happen over a loop)
        memcpy(receivedData, sentData, dataSize); // Simulate perfect transmission
        // Uncomment the line below to simulate data corruption
        // receivedData[rand() % dataSize] ^= 0xFF; // Introduce a random bit error

        // Check the received data
        if (checkData(sentData, receivedData, dataSize)) {
            printf("Data received correctly!\n");
        } else {
            printf("Data error detected!\n");
        }

        printf("Press Ctrl+C to exit.\n");
        sleep(1); // Delay for a second before sending the next block
    }

    return 0; // Successful termination of the program (unreachable in this infinite loop)
}
