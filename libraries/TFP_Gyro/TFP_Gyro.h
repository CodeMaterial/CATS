#pragma once

#include <Adafruit_FXAS21002C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <EEPROM.h>

struct Gyro_Calibration {
    int bias = 0;
    bool calibrated = false;
    int calibration_duration = 1000;
    int calibration_samples = 100;
};

class TFP_Gyro {
public:
    TFP_Gyro();

    bool begin();

    void update();

    void calibrate();

    void save_calibration();

    void load_calibration();

    bool is_rotating();

    void wait_for_stationary();

public:
    float heading = 0; // in radians
    float velocity = 0; // in radians per second

private:
    Adafruit_FXAS21002C FXA = Adafruit_FXAS21002C(0x0021002C);
    sensors_event_t event;
    Gyro_Calibration calibration;
    unsigned long last_update = 0;
    const int calibration_address = 1000;
};