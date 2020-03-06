#pragma once

#include "Arduino.h"
#include "TFP_Transmitter_Components.h"

class TFP_Transmitter {
public:
    TFP_Transmitter();

    void update();

    void calibrate();

    void load_calibration();

    bool begin(int ppm_channel);

    void print_state();

public:
    Transmitter_components::Stick left_stick;
    Transmitter_components::Stick right_stick;
    Transmitter_components::Knob left_knob;
    Transmitter_components::Knob right_knob;
    Transmitter_components::Switch left_switch;
    Transmitter_components::Switch right_switch;
private:
    PulsePositionInput ppm;
};
