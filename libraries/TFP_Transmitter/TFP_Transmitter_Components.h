#pragma once

#include <EEPROM.h>
#include <PulsePosition.h>

enum Component_Mode {
    Switch,
    Knob,
    Stick
};

struct Transmitter_Calibration {
    int raw_max = 2000;
    int raw_min = 1000;
    int raw_cen = 1500;
    int deadzone_max = 1500 + 20;
    int deadzone_min = 1500 - 20;
    bool calibrated = false;
    int calibration_timeout = 10000;
};

class Transmitter_Component {
public:
    Transmitter_Component(PulsePositionInput *ppm, int channel, Component_Mode mode);

    Transmitter_Component(PulsePositionInput *ppm, int channel, const char *name, Component_Mode mode);

    void calibrate();

    void save_calibration();

    void load_calibration();

    void reset_calibration();

    bool is_calibrated();

    void update();

    void print_state();

    int value;

private:
    PulsePositionInput *ppm;
    int channel;
    const char *name;
    Component_Mode mode;
    int raw_value;
    Transmitter_Calibration calibration;
};
