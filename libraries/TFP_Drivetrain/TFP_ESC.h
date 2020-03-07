#pragma once

#include "TFP_Gyro.h"

struct ESC_Calibration {
    int deadzone_max = 1500;
    int deadzone_cen = 1500;
    int deadzone_min = 1500;
};

class TFP_ESC {
public:
    TFP_ESC(TFP_Gyro *gyro);

    bool begin(int pin);

    void calibrate();

    void save_calibration();

    void load_calibration();

    void set_speed(int speed);

    void stop();

    int speed;

private:
    TFP_Gyro *gyro;
    Servo esc;
    int calibration_address;
    int pulse_size = 1500;
    ESC_Calibration calibration;
};