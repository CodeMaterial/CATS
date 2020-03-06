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
    Transmitter_components::Channel_Component left_stick_x;
    Transmitter_components::Channel_Component left_stick_y;
    Transmitter_components::Channel_Component right_stick_x;
    Transmitter_components::Channel_Component right_stick_y;
    Transmitter_components::Channel_Component left_knob;
    Transmitter_components::Channel_Component right_knob;
    Transmitter_components::Channel_Component left_switch;
    Transmitter_components::Channel_Component right_switch;
private:
    PulsePositionInput ppm;
    Transmitter_components::Channel_Component *all_components[8];
};
