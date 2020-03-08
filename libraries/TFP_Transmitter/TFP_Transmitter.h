#pragma once

#include "TFP_Transmitter_Components.h"

class TFP_Transmitter {
public:
    TFP_Transmitter();

    void update();

    void calibrate();

    void load_calibration();

    void reset_calibration();

    bool begin(int ppm_pin);

    void print_state();

public:
    Transmitter_Component left_stick_x;
    Transmitter_Component left_stick_y;
    Transmitter_Component right_stick_x;
    Transmitter_Component right_stick_y;
    Transmitter_Component left_knob;
    Transmitter_Component right_knob;
    Transmitter_Component left_switch;
    Transmitter_Component right_switch;
private:
    PulsePositionInput ppm;
    Transmitter_Component *all_components[8];
};
