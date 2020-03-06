#include "TFP_Gyro.h"


TFP_Gyro::TFP_Gyro(){

};

bool TFP_Gyro::begin() {
    FXA.begin(GYRO_RANGE_1000DPS);
    last_update = millis();
    return true;
};

void TFP_Gyro::update() {

    unsigned long now = millis();

    FXA.getEvent(&event);
    velocity = event.gyro.z - bias;
    heading += velocity * ((now - last_update) / 1000.0f);
    last_update = now;
};

void TFP_Gyro::calibrate() {

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

    Serial.print("Bias: ");
    Serial.println(bias, 4);
}

bool TFP_Gyro::is_rotating() {
    update();
    return abs(velocity) > 0.1;
}