#include "TFP_Drivetrain.h"

Drivetrain::Drivetrain() {
    Serial.println("Initialising Drivetrain");
    gyro.begin();
    esc_l.begin(5, &gyro);
    esc_r.begin(6, &gyro);
    esc_l.stop();
    esc_r.stop();
}

void Drivetrain::calibrate() {
    Serial.println("Calibrating drivetrain");
    esc_l.calibrate();
    esc_r.calibrate();
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

void Drivetrain::SkidSteer(int left, int right) {
    esc_l.set_speed(left);
    esc_r.set_speed(right);
};

void Drivetrain::WheelSteer(int power, int steer) {
    esc_l.set_speed(power - steer);
    esc_r.set_speed(power + steer);
};