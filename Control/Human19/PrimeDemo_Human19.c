
#define A_STAR_LV

const uint8_t chipSelect = 4;

#include <AStar32U4.h>
#include <SPI.h>
#include <SD.h>
#include <Keyboard.h>

AStar32U4LCD lcd;
AStar32U4Buzzer buzzer;
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;

char buttonMonitor();

class Menu
{
public:
  struct Item
  {
    const char * name;
    void (* action)();
  };

  Menu(Item * items, uint8_t itemCount)
  {
    this->items = items;
    this->itemCount = itemCount;
    lcdItemIndex = 0;
  }

  void lcdUpdate(uint8_t index)
  {
    lcd.clear();
    lcd.print(items[index].name);
    lcd.gotoXY(0, 1);
    lcd.print(F("\x7f" "A \xa5" "B C\x7e"));
  }

  void action(uint8_t index)
  {
    items[index].action();
  }

  // Prompts the user to choose one of the menu items, then
  // runs it, then returns.
  void select()
  {
    lcdUpdate(lcdItemIndex);

    while(1)
    {
      switch(buttonMonitor())
      {
      case 'A':
        // The A button was pressed so decrement the index.
        if (lcdItemIndex == 0)
        {
          lcdItemIndex = itemCount - 1;
        }
        else
        {
          lcdItemIndex--;
        }
        lcdUpdate(lcdItemIndex);
        break;

      case 'C':
        // The C button was pressed so increase the index.
        if (lcdItemIndex >= itemCount - 1)
        {
          lcdItemIndex = 0;
        }
        else
        {
          lcdItemIndex++;
        }
        lcdUpdate(lcdItemIndex);
        break;

      case 'B':
        // The B button was pressed so, run the item and
        // return.
        action(lcdItemIndex);
        return;
      }
    }
  }

private:
  Item * items;
  uint8_t itemCount;
  uint8_t lcdItemIndex;
};


// A couple of simple tunes, stored in program space.
const char beepBrownout[] PROGMEM = "<c32<e32#<g32";
const char beepWelcome[] PROGMEM = ">g32>>c32";
const char beepThankYou[] PROGMEM = ">>c32>g32";
const char beepButtonA[] PROGMEM = "!c32";
const char beepButtonB[] PROGMEM = "!e32";
const char beepButtonC[] PROGMEM = "!g32";
const char beepTimerTick[] PROGMEM = "!v8>>c32";

// Custom characters for the LCD:

// This character is a musical note.
const char note[] PROGMEM = {
  0b00100,
  0b00110,
  0b00101,
  0b00101,
  0b00100,
  0b11100,
  0b11100,
  0b00000,
};

// This character is a back arrow.
const char backArrow[] PROGMEM = {
  0b00000,
  0b00010,
  0b00001,
  0b00101,
  0b01001,
  0b11110,
  0b01000,
  0b00100,
};

void loadCustomCharacters()
{

  lcd.loadCustomCharacter(backArrow, 6);
  lcd.loadCustomCharacter(note, 7);
}

void displayBackArrow()
{
  lcd.clear();
  lcd.gotoXY(0,1);
  lcd.print(F("\6B"));
  lcd.gotoXY(0,0);
}

void keyboardDemo()
{
  displayBackArrow();
  lcd.print(F("Type A/C"));

  while(1)
  {
    if (buttonA.getSingleDebouncedPress())
    {
      // Button A was pressed.
      Keyboard.press('a');
      buzzer.playFromProgramSpace(beepButtonA);
    }
    if (!buttonA.isPressed())
    {
      Keyboard.release('a');
    }

    if (buttonC.getSingleDebouncedPress())
    {
      // Button C was pressed.
      Keyboard.press('c');
      buzzer.playFromProgramSpace(beepButtonC);
    }
    if (!buttonC.isPressed())
    {
      Keyboard.release('c');
    }

    if (buttonB.getSingleDebouncedPress())
    {
      // Button B was pressed, so quit.
      buzzer.playFromProgramSpace(beepButtonB);
      break;
    }
  }
}

// Blinks all three LEDs in sequence.
void ledDemo()
{
  displayBackArrow();

  uint8_t state = 3;
  static uint16_t lastUpdateTime = millis() - 2000;
  while(buttonMonitor() != 'B')
  {
    if ((uint16_t)(millis() - lastUpdateTime) >= 500)
    {
      lastUpdateTime = millis();
      state = state + 1;
      if (state >= 4) { state = 0; }

      switch(state)
      {
      case 0:
        buzzer.play("c32");
        lcd.gotoXY(0, 0);
        lcd.print("Red   ");
        ledRed(1);
        ledGreen(0);
        ledYellow(0);
        break;

      case 1:
        buzzer.play("e32");
        lcd.gotoXY(0, 0);
        lcd.print("Green");
        ledRed(0);
        ledGreen(1);
        ledYellow(0);
        break;

      case 2:
        buzzer.play("g32");
        lcd.gotoXY(0, 0);
        lcd.print("Yellow");
        ledRed(0);
        ledGreen(0);
        ledYellow(1);
        break;
      }
    }
  }

  ledRed(0);
  ledYellow(0);
  ledGreen(0);
}

const char fugue[] PROGMEM =
  "! T120O5L16agafaea dac+adaea fa<aa<bac#a dac#adaea f"
  "O6dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
  "L8MS<b-d<b-d MLe-<ge-<g MSc<ac<a MLd<fd<f O5MSb-gb-g"
  "ML>c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
  "O6L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
  "O5e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
  "e>d>c#>db>d>c#b >c#agaegfe fO6dc#dfdc#<b c#4";

const char fugueTitle[] PROGMEM =
  "       \7 Fugue in D Minor - by J.S. Bach \7       ";

// Play a song on the buzzer and display its title.
void musicDemo()
{
  displayBackArrow();

  uint8_t fugueTitlePos = 0;
  uint16_t lastShiftTime = millis() - 2000;

  while(buttonMonitor() != 'B')
  {
    // Shift the song title to the left every 250 ms.
    if((uint16_t)(millis() - lastShiftTime) > 250)
    {
      lastShiftTime = millis();

      lcd.gotoXY(0, 0);
      for(uint8_t i = 0; i < 8; i++)
      {
        char c = pgm_read_byte(fugueTitle + fugueTitlePos + i);
        lcd.write(c);
      }
      fugueTitlePos++;

      if(fugueTitlePos + 8 >= sizeof(fugueTitle))
      {
        fugueTitlePos = 0;
      }
    }

    if(!buzzer.isPlaying())
    {
      buzzer.playFromProgramSpace(fugue);
    }
  }
}

// Display the the battery (VIN) voltage and indicate
// whether USB power is detected.
void powerDemo()
{
  uint16_t lastDisplayTime = millis() - 2000;
  while(buttonMonitor() != 'B')
  {
    if ((uint16_t)(millis() - lastDisplayTime) > 250)
    {
      bool usbPower = usbPowerPresent();

#if defined(A_STAR_LV)
      uint16_t batteryLevel = readBatteryMillivoltsLV4();
#elif defined(A_STAR_LV_AC03B)
      uint16_t batteryLevel = readBatteryMillivoltsLV3();
#elif defined(A_STAR_SV)
      uint16_t batteryLevel = readBatteryMillivoltsSV();
#else
#error "Unknown board"
#endif

      lastDisplayTime = millis();
      lcd.clear();
      lcd.print(batteryLevel);
      lcd.print(F(" mV"));
      lcd.gotoXY(0, 1);
      lcd.print(F("\6B USB="));
      lcd.print(usbPower ? 'Y' : 'N');
    }
  }
}

Sd2Card card;
SdVolume volume;


void sdDemo()
{
  lcd.clear();

  lcd.clear();
  lcd.print(F("SD..."));

  if (!(card.init(SPI_HALF_SPEED, chipSelect)))
  {
    lcd.clear();
    lcd.print(F("No SD   "));
  }
  else
  {
    lcd.print('.');

    if (!volume.init(card))
    {
      lcd.clear();
      lcd.print(F("No volum"));
    }
    else
    {
      
      uint32_t size = (uint32_t)volume.clusterCount() *
        volume.blocksPerCluster() / 2048;
      lcd.clear();
      lcd.print(size);
      lcd.print(F(" MB"));
    }
  }

 
  lcd.gotoXY(0, 1);
  lcd.print(F("\6B"));
  while(buttonMonitor() != 'B');
}

.
void serialMonitorDemo()
{
  lcd.clear();
  lcd.print(F("Type"));
  lcd.gotoXY(0, 1);
  lcd.print(F("into"));
  delay(1000);

  lcd.clear();
  lcd.print(F("serial"));
  lcd.gotoXY(0, 1);
  lcd.print(F("monitor."));
  delay(1000);

  lcd.cursorBlinking();
  displayBackArrow();

  Serial.flush();

  uint8_t column = 0;
  bool quit = 0;

  while(!quit)
  {
    if (Serial.available())
    {
      // We received a character from the serial port.
      char c = Serial.read();

      // Show the character on the LCD.
      if (column >= 8)
      {
     
        displayBackArrow();
        column = 0;
      }
      column++;
      lcd.write(c);

d.
      Serial.print("Received character 0x");
      Serial.println((uint8_t)c, HEX);
    }


    switch(buttonMonitor())
    {
    case 'A':
      Serial.println(F("Button A was pressed."));
      break;

    case 'C':
      Serial.println(F("Button C was pressed."));
      break;

    case 'B':
      quit = true;
      break;
    }
  }

  lcd.hideCursor();
}

Menu::Item mainMenuItems[] = {
  { "Keyboard", keyboardDemo },
  { "LEDs", ledDemo },
  { "Music", musicDemo },
  { "Power", powerDemo },
  { "SD card", sdDemo },
  { "Serial", serialMonitorDemo },
};
Menu mainMenu(mainMenuItems, 6);


char buttonMonitor()
{
  if (buttonA.getSingleDebouncedPress())
  {
    buzzer.playFromProgramSpace(beepButtonA);
    return 'A';
  }

  if (buttonB.getSingleDebouncedPress())
  {
    buzzer.playFromProgramSpace(beepButtonB);
    return 'B';
  }

  if (buttonC.getSingleDebouncedPress())
  {
    buzzer.playFromProgramSpace(beepButtonC);
    return 'C';
  }

  return 0;
}

void setup()
{
  loadCustomCharacters();


  bool brownout = MCUSR >> BORF & 1;
  MCUSR = 0;

  if (brownout)
  {

    buzzer.playFromProgramSpace(beepBrownout);
    lcd.clear();
    lcd.print(F("Brownout"));
    lcd.gotoXY(0, 1);
    lcd.print(F(" reset! "));
    delay(1000);
  }
  else
  {
    buzzer.playFromProgramSpace(beepWelcome);
  }

  lcd.clear();
  lcd.print(F(" A-Star"));
  lcd.gotoXY(0, 1);
#if defined(A_STAR_LV) || defined(A_STAR_LV_AC03B)
  lcd.print(F("Prime LV"));
#elif defined(A_STAR_SV)
  lcd.print(F("Prime SV"));
#else
#error "Unknown board"
#endif

  delay(1000);

  lcd.clear();
  lcd.print(F("Demo"));
  lcd.gotoXY(0, 1);
  lcd.print(F("Program"));
  delay(1000);

  lcd.clear();
  lcd.print(F("Use B to"));
  lcd.gotoXY(0, 1);
  lcd.print(F("select."));
  delay(1000);

  lcd.clear();
  lcd.print(F("Press B"));
  lcd.gotoXY(0, 1);
  lcd.print(F("-try it!"));

  while(buttonMonitor() != 'B'){}

  buzzer.playFromProgramSpace(beepThankYou);
  lcd.clear();
  lcd.print(F(" Thank"));
  lcd.gotoXY(0, 1);
  lcd.print(F("  you!"));
  delay(1000);
}


void mainMenuSelect()
{
  lcd.clear();
  lcd.print(F("  Main"));
  lcd.gotoXY(0, 1);
  lcd.print(F("  Menu"));
  delay(1000);
  mainMenu.select();
}

void loop()
{
  mainMenuSelect();
}