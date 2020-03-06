#pragma once

#include <Adafruit_FXAS21002C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class Gyro {
public:
    Gyro();

    bool begin();

    void update();

    void calibrate();

    bool is_rotating();

public:
    float heading = 0; // in radians
    float velocity = 0; // in radians per second

private:
    Adafruit_FXAS21002C gyro;
    sensors_event_t event;
    float bias = 0; // in radians per second
    unsigned long last_update = 0;
}
