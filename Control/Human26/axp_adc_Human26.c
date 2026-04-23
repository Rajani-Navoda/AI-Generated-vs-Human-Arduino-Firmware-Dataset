#include "axp20x.h"

AXP20X_Class axp;
const uint8_t i2c_sda = 21;
const uint8_t i2c_scl = 22;
const uint8_t slave_address = AXP192_SLAVE_ADDRESS;             //use axp192
// const uint8_t slave_address = AXP202_SLAVE_ADDRESS;          //use axp202

void printPowerChannel();

void setup(void)
{
    Serial.begin(115200);

    Wire.begin(i2c_sda, i2c_scl);

    Serial.println("AXP192/AXP202 ADC Test");

    /* Initialise the pmu */
    int ret = axp.begin(Wire, slave_address);
    if (ret) {
        /* There was a problem detecting the AXP202/192 ... check your connections */
        Serial.println("Ooops, AXP202/AXP192 power chip detected ... Check your wiring!");
        while (1);
    }

    /*Enable AXP ADC function*/
    axp.adc1Enable(AXP202_VBUS_VOL_ADC1 |
                   AXP202_VBUS_CUR_ADC1 |
                   AXP202_BATT_CUR_ADC1 |
                   AXP202_BATT_VOL_ADC1,
                   true);

    Serial.println("");

    printPowerChannel();
}

void loop(void)
{
    Serial.println("=========================");
    Serial.print("VBUS STATUS: ");
    // You can use isVBUSPlug to check whether the USB connection is normal
    if (axp.isVBUSPlug()) {

        Serial.println("CONNECT");

        // Get USB voltage
        Serial.print("VBUS Volate:");
        Serial.print(axp.getVbusVoltage());
        Serial.println(" mV");

        // Get USB current
        Serial.print("VBUS Current: ");
        Serial.print(axp.getVbusCurrent());
        Serial.println(" mA");

    } else {
        Serial.println("DISCONNECT");
    }

    Serial.println("=========================");

    Serial.print("BATTERY STATUS: ");

    // You can use isBatteryConnect() to check whether the battery is connected properly
    if (axp.isBatteryConnect()) {

        Serial.println("CONNECT");

        // Get battery voltage
        Serial.print("BAT Volate:");
        Serial.print(axp.getBattVoltage());
        Serial.println(" mV");

        // To display the charging status, you must first discharge the battery,
        // and it is impossible to read the full charge when it is fully charged
        if (axp.isChargeing()) {
            Serial.print("Charge:");
            Serial.print(axp.getBattChargeCurrent());
            Serial.println(" mA");
        } else {
            // Show current consumption
            Serial.print("Discharge:");
            Serial.print(axp.getBattDischargeCurrent());
            Serial.println(" mA");

            /*getBattPercentage just only support axp202 */
            if (slave_address == AXP202_SLAVE_ADDRESS) {
                Serial.print("Per: ");
                Serial.print(axp.getBattPercentage());
                Serial.println(" %");
            }
        }
    } else {
        Serial.println("DISCONNECT");
    }
    Serial.println();
    Serial.println();
    delay(3000);
}


void printPowerChannel()
{
    Serial.print("DC2:");
    Serial.print(axp.isDCDC2Enable() ? String(axp.getDCDC2Voltage()) + " mv" : "DISABLE");
    Serial.print("  ");

    Serial.print("DC3:");
    Serial.print(axp.isDCDC3Enable() ? String(axp.getDCDC3Voltage()) + " mv" : "DISABLE");
    Serial.print("  ");

    Serial.print("LDO2:");
    Serial.print(axp.isLDO2Enable() ? String(axp.getLDO2Voltage()) + " mv" : "DISABLE");
    Serial.print("  ");

    Serial.print("LDO3:");
    Serial.print(axp.isLDO3Enable() ? String(axp.getLDO3Voltage()) + " mv" : "DISABLE");
    Serial.print("  ");

    Serial.print("LDO4:");
    Serial.print(axp.isLDO4Enable() ? "ENABLE" : "DISABLE");
    Serial.print("  ");

    Serial.print("Exten:");
    Serial.print(axp.isExtenEnable() ? "ENABLE" : "DISABLE");
    Serial.print("\r\n");
}