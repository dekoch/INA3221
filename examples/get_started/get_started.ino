#include <Wire.h>
#include <INA3221.h>

#define SERIAL_SPEED     115200  // serial baud rate

// Set I2C address to 0x41 (A0 pin -> VCC)
INA3221 ina_0(INA3221_ADDR40_GND);

void current_measure_init() {
    ina_0.begin(&Wire);
    ina_0.reset();
    // Set shunt resistors to 100 mOhm for all channels
    ina_0.setShuntRes(100, 100, 100);
}

void setup() {
    Serial.begin(SERIAL_SPEED);
    current_measure_init();

    while (!Serial) {
        delay(1);
    }
}

void loop() {
    Serial.print(ina_0.getCurrent(INA3221_CH1) * 1000);
    Serial.print("mA ");
    Serial.print(ina_0.getVoltage(INA3221_CH1));
    Serial.println("V");

    delay(1000);
}
