#include "TFP_Gyro.h"

TFP_Gyro::TFP_Gyro() {

};

bool TFP_Gyro::begin() {
    FXA.begin(GYRO_RANGE_1000DPS);
    last_update = millis();
    return true;
};

void TFP_Gyro::update() {

    unsigned long now = millis();

    FXA.getEvent(&event);
    velocity = event.gyro.z - calibration.bias;
    heading += velocity * ((now - last_update) / 1000.0f);
    last_update = now;
};

void TFP_Gyro::calibrate() {

    calibration.bias = 0;
    heading = 0;

    unsigned long start_time = millis();
    for (int i = 0; i < calibration.calibration_samples; i++) {
        update();
        delay(calibration.calibration_duration/calibration.calibration_samples);
    }
    unsigned long calibration_duration_in_millis = millis() - start_time;
    calibration.bias = (1000 * heading) / calibration_duration_in_millis;

    heading = 0;

    Serial.print("Bias: ");
    Serial.println(calibration.bias, 4);
}

void TFP_Gyro::save_calibration() {
    EEPROM.put(calibration_address, calibration);
}

void TFP_Gyro::load_calibration() {
    EEPROM.get(calibration_address, calibration);
}

bool TFP_Gyro::is_rotating() {
    update();
    return abs(velocity) > 0.1;
}

void TFP_Gyro::wait_for_stationary(){
    while(is_rotating()){
        delay(10);
    }
}