#pragma once

#include <Servo.h>
#include "TFP_Gyro.h"

struct ESC_Calibration {
    int deadzone_max = 1500;
    int deadzone_cen = 1500;
    int deadzone_min = 1500;
};

class TFP_ESC {
public:
    TFP_ESC();

    bool begin(int pin, TFP_Gyro *gyro_in);

    void calibrate(TFP_Gyro *gyro);

    void save_calibration();

    void load_calibration();

    void reset_calibration();

    void set_speed(int speed);

    void stop();

    void print_state();

    int speed;

    float max_speed = 0.5;

private:
    Servo esc;
    int calibration_address;
    int pulse_size = 1500;
    ESC_Calibration calibration;
};