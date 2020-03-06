#include <EEPROM.h>
#include "TFP_Transmitter_Components.h"
// start reading from the first byte (address 0) of the EEPROM

Transmitter_components::Calibration calibration;


void setup() {
    Serial.begin(9600);

    while (!Serial) {
        delay(1);
    }

    calibration.raw_cen = 12;
    Serial.println(calibration.raw_cen);
    EEPROM.put(10, calibration);
}

void loop() {
    Serial.println();
//    Transmitter_components::Calibration calibration_retrieved; //Variable to store custom object read from EEPROM.
//    EEPROM.get(10, calibration_retrieved);
//    Serial.println(calibration.raw_cen);
    delay(500);
}