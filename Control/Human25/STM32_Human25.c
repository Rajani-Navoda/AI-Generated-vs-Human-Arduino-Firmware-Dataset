#include <Joystick.h>
#include <AxisJoystick.h>

#define SW_PIN PA5
#define VRX_PIN PA6
#define VRY_PIN PA7
#define STM32_ADC_MIN 0
#define STM32_ADC_MAX 4095
#define AXES_DEVIATION 100

Joystick* joystic;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  joystic = new AxisJoystick(SW_PIN, VRX_PIN, VRY_PIN);
  joystic->calibrate(STM32_ADC_MIN, STM32_ADC_MAX, AXES_DEVIATION);
  /*
    or
    joystic->calibrate(
      STM32_ADC_MIN + AXES_DEVIATION,
      STM32_ADC_MAX - AXES_DEVIATION
    );
  */
}

// the loop function runs over and over again forever
void loop() {
  Serial.print("SingleRead: " + moveTitle(joystic->singleRead()));
  Serial.println(" | MultipleRead: " + moveTitle(joystic->multipleRead()));

  delay(500); // optionally, only to delay the output of information in the example
}

/**
  Return title of the input joystick move.
*/
String moveTitle(const Joystick::Move move) {
  switch (move) {
    case Joystick::Move::NOT:
      return "NOT";
    case Joystick::Move::PRESS:
      return "PRESS";
    case Joystick::Move::UP:
      return "UP";
    case Joystick::Move::DOWN:
      return "DOWN";
    case Joystick::Move::RIGHT:
      return "RIGHT";
    case Joystick::Move::LEFT:
      return "LEFT";
    default:
      return "???";
  }
}