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
}


void loop() {
    transmitter.update();
    transmitter.print_state();
    drivetrain.wheel_steer(transmitter.left_stick_y.value - 500, transmitter.left_stick_x.value - 500);
    delay(10);
}
