#include "TFP_Drivetrain.h"
#include "TFP_Transmitter.h"

Drivetrain drivetrain;
TFP_Transmitter transmitter;

int mode = 0;

void setup(void) {
    Serial.begin(9600);

    drivetrain.begin();
    drivetrain.load_calibration();
    transmitter.begin(10);
    transmitter.load_calibration();
}


void loop() {
    transmitter.update();

    int steer = transmitter.left_stick_x() * (transmitter.left_knob() / 1000.0f);

    drivetrain.wheel_steer(transmitter.left_stick_y(), steer);

    if (transmitter.left_lever() != mode) {
        mode = transmitter.left_lever();
        if (mode == 0) {
            drivetrain.reset_calibration();
            transmitter.reset_calibration();
        } else if (mode == 1) {
            drivetrain.load_calibration();
            transmitter.load_calibration();
        }
    }

    delay(10);
}
