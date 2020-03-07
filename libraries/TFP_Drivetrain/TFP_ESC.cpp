#include "TFP_ESC.h"


TFP_ESC::TFP_ESC(TFP_Gyro *gyro_in) : gyro(gyro_in) {

};

bool TFP_ESC::begin(int pin){
    esc.attach(pin);
    calibration_address = 1500 + pin*sizeof(calibration);
};

void TFP_ESC::calibrate() {

    stop();

    gyro->wait_for_stationary();

    while (!gyro->is_rotating()) {
        calibration.deadzone_max += 1;
        esc.writeMicroseconds(calibration.l_deadzone_max);
        delay(100);
    }
    stop();

    save_calibration();

};

void TFP_ESC::save_calibration() {
    EEPROM.put(calibration_address, calibration);
}

void TFP_ESC::load_calibration() {
    EEPROM.get(calibration_address, calibration);
}

void TFP_ESC::set_speed(int speed);

void stop(){
    esc.writeMicroseconds(calibration.deadzone_cen)
};