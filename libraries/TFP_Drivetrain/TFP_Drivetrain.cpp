#include "TFP_Drivetrain.h"

Drivetrain::Drivetrain() {
}

bool Drivetrain::begin() {
    Serial.println("Initialising Drivetrain");
    esc_l.begin(5);
    esc_r.begin(6);
    esc_l.stop();
    esc_r.stop();
    return true;
}

void Drivetrain::calibrate(TFP_Gyro *gyro) {
    Serial.println("Calibrating drivetrain");
    esc_l.calibrate(gyro);
    esc_r.calibrate(gyro);
};

void Drivetrain::save_calibration() {
    Serial.println("Saving drivetrain");
    esc_l.save_calibration();
    esc_r.save_calibration();
}

void Drivetrain::load_calibration() {
    Serial.println("Loading calibration");
    esc_l.load_calibration();
    esc_r.load_calibration();
}

void Drivetrain::reset_calibration() {
    Serial.println("Resetting drivetrain calibration");
    esc_l.reset_calibration();
    esc_r.reset_calibration();
}

void Drivetrain::skid_steer(int left, int right) {
    esc_l.set_speed(left);
    esc_r.set_speed(right);
};

void Drivetrain::wheel_steer(int power, int steer) {
    esc_l.set_speed(power - steer);
    esc_r.set_speed(power + steer);
};

void Drivetrain::print_state() {
    Serial.println("Drivetrain state:");
    esc_l.print_state();
    esc_r.print_state();
}