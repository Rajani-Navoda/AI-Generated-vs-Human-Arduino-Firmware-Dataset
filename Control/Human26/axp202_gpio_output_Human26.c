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
    
    axp.setGPIOMode(AXP_GPIO_0, AXP_IO_OUTPUT_HIGH_MODE);
    axp.setGPIOMode(AXP_GPIO_1, AXP_IO_OUTPUT_HIGH_MODE);

    //! GPIO2, GPIO3 is only allowed to be configured to output low
    axp.gpioWrite(AXP_GPIO_2, LOW);
    axp.gpioWrite(AXP_GPIO_3, LOW);

}

void loop()
{
    //! GPIO0, GPIO1 allows output high and low
    axp.gpioWrite(AXP_GPIO_0, HIGH);
    axp.gpioWrite(AXP_GPIO_1, HIGH);
    delay(1000);
    axp.gpioWrite(AXP_GPIO_0, LOW);
    axp.gpioWrite(AXP_GPIO_1, LOW);
    delay(1000);
}
