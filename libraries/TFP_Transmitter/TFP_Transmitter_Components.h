#pragma once

#include <EEPROM.h>
#include <PulsePosition.h>


struct Calibration {
    int raw_max = 2000;
    int raw_min = 1000;
    int raw_cen = 1500;
    bool calibrated = false;
    int calibration_timeout = 10000;
};

class Channel_Component {
public:
    Channel_Component(PulsePositionInput *ppm, int channel, bool binary_mode = false);

    Channel_Component(PulsePositionInput *ppm, int channel, const char *name, bool binary_mode = false);

    void calibrate();

    void save_calibration();

    void load_calibration();

    bool is_calibrated();

    void update();

    void print_state();

    int value;

private:
    PulsePositionInput *ppm;
    int channel;
    const char *name;
    bool binary_mode;
    int raw_value;
    Calibration calibration;
};
