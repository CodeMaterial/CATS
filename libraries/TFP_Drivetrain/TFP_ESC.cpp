#include "TFP_ESC.h"


TFP_ESC::TFP_ESC(){

};

bool TFP_ESC::begin(int pin, TFP_Gyro *gyro_in) {
    Serial.println("Initialising ESC");
    esc.attach(pin);
    gyro = gyro_in;
    calibration_address = 1500 + pin * sizeof(calibration);
    return true;
};

void TFP_ESC::calibrate() {

    Serial.println("Clearing previous calibration");

    calibration = ESC_Calibration();
    stop();

    Serial.println("Calibrating ESC's deadzone max");


    gyro->wait_for_stationary();

    while (!gyro->is_rotating()) {
        calibration.deadzone_max += 1;
        esc.writeMicroseconds(calibration.deadzone_max);
        delay(100);
    }
    stop();

    Serial.println("Calibrating ESC's deadzone min");

    gyro->wait_for_stationary();

    while (!gyro->is_rotating()) {
        calibration.deadzone_min -= 1;
        esc.writeMicroseconds(calibration.deadzone_min);
        delay(100);
    }
    stop();

    save_calibration();

};

void TFP_ESC::save_calibration() {
    Serial.println("Saving calibration");
    EEPROM.put(calibration_address, calibration);
}

void TFP_ESC::load_calibration() {
    Serial.println("Loading calibration");
    EEPROM.get(calibration_address, calibration);
}

void TFP_ESC::set_speed(int speed) {

    speed *= max_speed;


    int pwm_duration = calibration.deadzone_cen;

    if (speed > 0) {
        pwm_duration = map(speed, 0, 500, calibration.deadzone_max, 2000);
    } else if (speed < 0) {
        pwm_duration = map(speed, 0, -500, calibration.deadzone_min, 1000);
    }

    esc.writeMicroseconds(constrain(pwm_duration, 1000, 2000));

};

void TFP_ESC::stop() {
    esc.writeMicroseconds(calibration.deadzone_cen);
};