#include "TFP_Transmitter.h"


TFP_Transmitter::TFP_Transmitter()
        : left_stick_x(&ppm, 4, "Left Stick X", Stick),
          left_stick_y(&ppm, 2, "Left Stick Y", Stick),
          right_stick_x(&ppm, 1, "Right Stick X", Stick),
          right_stick_y(&ppm, 3, "Right Stick Y", Knob),
          left_knob(&ppm, 5, "Left Knob", Knob),
          right_knob(&ppm, 6, "Right Knob", Knob),
          left_switch(&ppm, 7, "Left Switch", Switch),
          right_switch(&ppm, 8, "Right Switch", Switch) {
};

bool TFP_Transmitter::begin(int ppm_pin) {
    Serial.println("Setting up transmitter PPM");
    ppm.begin(ppm_pin);

    while (ppm.available() < 0) {
        delay(10);
    }
    Serial.println("Transmitter PPM setup");

    all_components[0] = &left_stick_x;
    all_components[1] = &left_stick_y;
    all_components[2] = &right_stick_x;
    all_components[3] = &right_stick_y;
    all_components[4] = &left_knob;
    all_components[5] = &right_knob;
    all_components[6] = &left_switch;
    all_components[7] = &right_switch;

    Serial.println("Updating Transmitter");
    update();

    return true;
};

void TFP_Transmitter::update() {
    for (auto component:all_components) {
        component->update();
    }
};

void TFP_Transmitter::calibrate() {
    Serial.println("Calibrating transmitter components");
    for (auto component:all_components) {
        component->calibrate();
    }
};

void TFP_Transmitter::print_state() {
    Serial.println("Current transmitter state:");
    for (auto component:all_components) {
        component->print_state();
    }
}

void TFP_Transmitter::load_calibration() {
    Serial.println("Loading transmitter components");
    for (auto component:all_components) {
        component->load_calibration();
    }
}

void TFP_Transmitter::reset_calibration() {
    Serial.println("Resetting transmitter components");
    for (auto component:all_components) {
        component->reset_calibration();
    }
}