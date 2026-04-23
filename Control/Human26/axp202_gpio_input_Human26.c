#include <Wire.h>
#include <axp20x.h>

AXP20X_Class axp;

const uint8_t i2c_sda = 21;
const uint8_t i2c_scl = 22;

void setup()
{
    Serial.begin(115200);
    Wire.begin(i2c_sda, i2c_scl);

    int ret = axp.begin(Wire);

    if (ret == AXP_FAIL) {
        Serial.println("AXP Power begin failed");
        while (1);
    }
    //! AXP202 GPIO has no internal pull-up or pull-down.
    //! For stability, external pull-up or pull-down resistors are required.
    ret = axp.setGPIOMode(AXP_GPIO_0, AXP_IO_INPUT_MODE);
    Serial.printf("AXP_GPIO_0 %d\n", ret);
    ret = axp.setGPIOMode(AXP_GPIO_1, AXP_IO_INPUT_MODE);
    Serial.printf("AXP_GPIO_1 %d\n", ret);
    ret = axp.setGPIOMode(AXP_GPIO_2, AXP_IO_INPUT_MODE);
    Serial.printf("AXP_GPIO_2 %d\n", ret);
    ret = axp.setGPIOMode(AXP_GPIO_3, AXP_IO_INPUT_MODE);
    Serial.printf("AXP_GPIO_3 %d\n", ret);

}

void loop()
{
    Serial.printf("GPIO: [0]:%d [1]:%d [2]:%d [3]:%d\n",
                  axp.gpioRead(AXP_GPIO_0),
                  axp.gpioRead(AXP_GPIO_1),
                  axp.gpioRead(AXP_GPIO_2),
                  axp.gpioRead(AXP_GPIO_3)
                 );
    delay(1000);
}