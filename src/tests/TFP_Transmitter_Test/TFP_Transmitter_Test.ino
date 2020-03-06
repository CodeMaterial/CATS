#include "TFP_Transmitter.h"

TFP_Transmitter transmitter;

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        delay(1);
    }
    Serial.println("Debug serial connected");
    delay(1000);
    transmitter.begin(10);
    Serial.println("Setup complete");
};

void loop() {
//    transmitter.left_stick.print_state();
    transmitter.update();
//    transmitter.calibrate();
    transmitter.load_calibration();
    while (true) {
        transmitter.update();
        transmitter.print_state();
        delay(1000);
    }
};