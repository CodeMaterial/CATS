#include "TFP_Transmitter.h"


TFP_Transmitter::TFP_Transmitter()
        : left_stick(&ppm, 4, 2, "Left Stick"),
          right_stick(&ppm, 1, 3, "Right Stick"),
          left_knob(&ppm, 5, "Left Knob"),
          right_knob(&ppm, 6, "Right Knob"),
          left_switch(&ppm, 7, "Left Switch"),
          right_switch(&ppm, 8, "Right Switch") {
};

bool TFP_Transmitter::begin(int ppm_channel){
    Serial.println("Setting up PPM");
    ppm.begin(ppm_channel);
    Serial.println("PPM setup");
    return true;
};

void TFP_Transmitter::update() {
    left_stick.update();
    right_stick.update();
    left_knob.update();
    right_knob.update();
    left_switch.update();
    right_switch.update();
};

void TFP_Transmitter::calibrate() {
    left_stick.calibrate();
    right_stick.calibrate();
    left_knob.calibrate();
    right_knob.calibrate();
    left_switch.calibrate();
    right_switch.calibrate();
};
