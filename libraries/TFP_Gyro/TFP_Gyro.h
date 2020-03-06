#pragma once

#include <Adafruit_FXAS21002C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class TFP_Gyro {
public:
    TFP_Gyro();

    bool begin();

    void update();

    void calibrate();

    bool is_rotating();

public:
    float heading = 0; // in radians
    float velocity = 0; // in radians per second

private:
    Adafruit_FXAS21002C FXA = Adafruit_FXAS21002C(0x0021002C);
    sensors_event_t event;
    float bias = 0; // in radians per second
    unsigned long last_update = 0;
};