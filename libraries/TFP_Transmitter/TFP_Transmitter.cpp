#include "TFP_Transmitter.h"


TFP_Transmitter::TFP_Transmitter() {

    all_components[0] = Transmitter_Component(&ppm, 4, "Left Stick X", Stick);
    all_components[1] = Transmitter_Component(&ppm, 2, "Left Stick Y", Stick);
    all_components[2] = Transmitter_Component(&ppm, 1, "Right Stick X", Stick);
    all_components[3] = Transmitter_Component(&ppm, 3, "Right Stick Y", Knob);
    all_components[4] = Transmitter_Component(&ppm, 5, "Left Knob", Knob);
    all_components[5] = Transmitter_Component(&ppm, 6, "Right Knob", Knob);
    all_components[6] = Transmitter_Component(&ppm, 7, "Left Lever", Lever);
    all_components[7] = Transmitter_Component(&ppm, 8, "Right Lever", Lever);
};

bool TFP_Transmitter::begin(int ppm_pin) {
    Serial.println("Setting up transmitter PPM");
    ppm.begin(ppm_pin);

    while (ppm.available() < 0) {
        delay(10);
    }
    Serial.println("Transmitter PPM setup");

    Serial.println("Updating Transmitter");
    update();

    return true;
};


Transmitter_Component left_stick_x() { return all_components[0].get_value() };

Transmitter_Component left_stick_y() { return all_components[1].get_value() };

Transmitter_Component right_stick_x() { return all_components[2].get_value() };

Transmitter_Component right_stick_y() { return all_components[3].get_value() };

Transmitter_Component left_knob() { return all_components[4].get_value() };

Transmitter_Component right_knob() { return all_components[5].get_value() };

Transmitter_Component left_lever() { return all_components[6].get_value() };

Transmitter_Component right_lever() { return all_components[7].get_value() };

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