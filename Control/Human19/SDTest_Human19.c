

#include <AStar32U4.h>
#include <SPI.h>
#include <SD.h>

AStar32U4LCD lcd;
AStar32U4Buzzer buzzer;
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;

const uint8_t chipSelect = 4;

void setup()
{
  char lastButton = ' ';

  // Initialize the SD card.
  lcd.clear();
  lcd.print("Init...");
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect))
  {
    Serial.println("Card failed, or not present");
    buzzer.playNote(NOTE_C(2), 100, 15);
    lcd.clear();
    lcd.print("Card err");
    while(1){}  // done
  }

  // Open the file.
  lcd.clear();
  lcd.print("Open...");
  Serial.println("Opening file...");
  File file = SD.open("test.txt");
  if (!file)
  {
    Serial.println("error opening test.txt");
    buzzer.playNote(NOTE_C(2), 100, 15);
    lcd.clear();
    lcd.print("File err");
    while(1){}  // done
  }

  // Start a loop where we will read data from the file,
  // keeping track of what line number we are on.
  uint32_t lineNumber = 1;
  while (true)
  {
    // Read 8 bytes from the file and store it in "line".
    char line[8];
    for(uint8_t i = 0; i < sizeof(line); i++)
    {
      if (!file.available()) { goto eof; }
      char x = file.read();
      if (x == '\n') { lineNumber++; }
      line[i] = x;
    }

    // Replace unprintable characters with spaces.  Some
    // characters will still get printed incorrectly on the
    // LCD, but should look correct in the serial monitor.
    for(uint8_t i = 0; i < sizeof(line); i++)
    {
      if (!isprint(line[i]))
      {
        line[i] = ' ';
      }
    }

    // Display the line number, position, and eight
    // characters from the file on the LCD.
    lcd.clear();
    lcd.print(lineNumber);
    lcd.print(' ');
    lcd.print(file.position());
    lcd.gotoXY(0, 1);
    lcd.write(line, 8);

    // Also print info to the serial monitor.
    Serial.print(lastButton);
    Serial.print(' ' );
    Serial.print(lineNumber);
    Serial.print(' ');
    Serial.print(file.position());
    Serial.print(' ');
    Serial.write(line, 8);
    Serial.println();

    // Wait for a button press while blinking all the LEDs.
    while(1)
    {
      ledRed(millis() >> 10 & 1);
      ledYellow(millis() >> 9 & 1);
      ledGreen(millis() >> 8 & 1);

      // Whenever a button is pressed, we play a distinctive
      // note for that button, record the button press, and
      // break out of this loop.

      if (buttonA.getSingleDebouncedPress())
      {
        buzzer.playNote(NOTE_G(3), 100, 15);
        lastButton = 'A';
        break;
      }

      if (buttonB.getSingleDebouncedPress())
      {
        buzzer.playNote(NOTE_G(4), 100, 15);
        lastButton = 'B';
        break;
      }

      if (buttonC.getSingleDebouncedPress())
      {
        buzzer.playNote(NOTE_G(5), 100, 15);
        lastButton = 'C';
        break;
      }
    }

    // Read 512 bytes from the file to clear out any caches
    // in the Arduino SD library.
    for (uint16_t i = 0; i < 512; i++)
    {
      if (!file.available()) { goto eof; }
      char x = file.read();
      if (x == '\n') { lineNumber++; }
    }
  }

  eof:  // We reached the end of the file.

  file.close();

  buzzer.playNote(NOTE_G(2), 100, 15);
  lcd.clear();
  lcd.print("EOF");
  Serial.println("EOF");
}

void loop()
{
}