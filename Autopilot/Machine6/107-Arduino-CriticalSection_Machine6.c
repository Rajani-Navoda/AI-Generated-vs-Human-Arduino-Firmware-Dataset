#include <107-Arduino-CriticalSection.h>  // Include the CriticalSection library

// Create a global shared resource (a simple counter)
volatile int counter = 0;

// Create a critical section object
arduino::CriticalSection criticalSection;

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Notify that the program has started
  Serial.println("Starting critical section example");
}

void loop() {
  // Enter the critical section to modify the shared resource (counter)
  {
    // Use a scoped critical section to ensure that access to the counter is protected
    arduino::CriticalSection::Lock lock(criticalSection);

    // Safely increment the counter
    counter++;
    Serial.print("Counter incremented to: ");
    Serial.println(counter);
  }  // The lock is automatically released here (end of scope)

  // Simulate some other work
  delay(1000);
}
