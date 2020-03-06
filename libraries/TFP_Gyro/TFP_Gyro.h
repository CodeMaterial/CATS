#pragma once

#include <Adafruit_FXAS21002C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class Gyro {
public:
    Gyro();

    bool begin();

    void update();

    void reset_heading();

    void calibrate();

public:
    float heading;
    float velocity;

private:
    Adafruit_FXAS21002C gyro;
    sensors_event_t event;
    float bias;
    long float time_since_update;
}
