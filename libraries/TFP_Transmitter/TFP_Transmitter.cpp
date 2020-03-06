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

    while (ppm.available() < 0) {
        delay(10);
    }
    update();

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

void TFP_Transmitter::print_state(){
    Serial.println("\nCurrent transmitter state:");
    left_stick.print_state();
    right_stick.print_state();
    left_knob.print_state();
    right_knob.print_state();
    left_switch.print_state();
    right_switch.print_state();
}

void TFP_Transmitter::load_calibration() {
    left_stick.load_calibration();
    right_stick.load_calibration();
    left_knob.load_calibration();
    right_knob.load_calibration();
    left_switch.load_calibration();
    right_switch.load_calibration();
}