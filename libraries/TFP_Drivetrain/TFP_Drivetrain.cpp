#include "TFP_Drivetrain.h"

Drivetrain::Drivetrain() {
    gyro.begin();
    esc_l.attach(5);
    esc_r.attach(6);
    esc_l.writeMicroseconds(calibration.l_deadzone_cen);
    esc_r.writeMicroseconds(calibration.r_deadzone_cen);
}

void Drivetrain::calibrate() {
    esc_l.calibrate();
    esc_r.calibrate();
};

void Drivetrain::save_calibration() {
    esc_l.save_calibration();
    esc_r.save_calibrate();
}

void Drivetrain::load_calibration() {
    esc_l.load_calibration();
    esc_r.load_calibration();
}

void SkidSteer(int left, int right) {
    esc_l.set_speed(left);
    esc_r.set_speed(right);
};

void WheelSteer(int power, int steer) {
    esc_l.set_speed(power - steer);
    esc_r.set_speed(power + steer);
};