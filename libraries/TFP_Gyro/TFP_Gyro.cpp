#include "TFP_Gyro.h"


Gyro::Gyro() : gyro(0x0021002C) {

};

bool Gyro::begin() {
    gyro.begin(GYRO_RANGE_1000DPS);
    last_update = millis();
};

void Gyro::update() {

    long float now = millis();

    gyro.getEvent(&event);
    velocity = event.gyro.z - bias;
    heading += velocity * ((now - last_update) / 1000);
    last_update = now;
};

void Gyro::calibrate() {

    bias = 0;
    heading = 0;

    unsigned long start_time = millis();
    for (int i = 0; i < 100; i++) {
        update();
        delay(20);
    }
    unsigned long calibration_duration_in_millis = millis() - start_time;
    bias = (1000 * heading) / calibration_duration_in_millis;

    heading = 0;
}

bool Gyro::is_rotating() {
    update();
    return abs(velocity) > 0.1;
}