#include "TFP_Drivetrain.h"
#include "TFP_Transmitter.h"

Drivetrain drivetrain;
TFP_Transmitter transmitter;

void setup(void) {
    Serial.begin(9600);

    while (!Serial) {
        delay(1);
    }
    Serial.println("Serial connected");

    drivetrain.begin();
    transmitter.begin(10);

    transmitter.calibrate();
    drivetrain.calibrate();
}


void loop() {
    transmitter.update();
    transmitter.print_state();
    delay(10);
}
