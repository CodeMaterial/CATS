#include "TFP_Gyro.h"

TFP_Gyro::TFP_Gyro() {

};

bool TFP_Gyro::begin() {
    Serial.println("Initialising gyroscope");
    FXA.begin(GYRO_RANGE_1000DPS);
    last_update = millis();
    Serial.println("Gyroscope initialised");
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

    Serial.print("Calibrating gyroscope for ");
    Serial.print(calibration.calibration_duration);
    Serial.println(" Seconds");

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

    Serial.print("Calibration bias: ");
    Serial.print(calibration.bias, 4);
    Serial.println(" Radians per second.");
}

void TFP_Gyro::save_calibration() {
    Serial.println("Saving calibration");
    EEPROM.put(calibration_address, calibration);
}

void TFP_Gyro::load_calibration() {
    Serial.println("Loading calibration");
    EEPROM.get(calibration_address, calibration);
}

bool TFP_Gyro::is_rotating() {
    update();
    return abs(velocity) > 0.1;
}

void TFP_Gyro::wait_for_stationary(){
    Serial.println("Waiting for stationary motion");
    while(is_rotating()){
        delay(10);
    }
}