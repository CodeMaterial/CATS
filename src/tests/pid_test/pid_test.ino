#include <PIDController.h>
#include "TFP_Drivetrain.h"
#include "TFP_Transmitter.h"
#include "TFP_Gyro.h"

Drivetrain drivetrain;
TFP_Transmitter transmitter;
PIDController pid; // Create an instance of the PID controller class, called "pid"
TFP_Gyro gyro;

double Kp, Ki, Kd;

double target = 0;

void setup() {
    Serial.begin(9600);

    pid.begin();

    pid.limit(-500, 500);

    drivetrain.begin();
    drivetrain.load_calibration();
    transmitter.begin(10);
    transmitter.load_calibration();
    gyro.begin();
    gyro.calibrate();
}

void loop() {

    transmitter.update();

    if(transmitter.left_lever.value){
        drivetrain.begin();
        drivetrain.load_calibration();
        transmitter.begin(10);
        transmitter.load_calibration();
        gyro.begin();
        gyro.calibrate();
        while(transmitter.left_lever.value){
            transmitter.update();
            delay(10);
        }
    }

    Kp = transmitter.right_stick_y.value;
    Ki = transmitter.right_knob.value/100.0f;
    Kd = transmitter.left_knob.value*100;

    pid.tune(Kp, Ki, Kd);

    target = (transmitter.left_stick_x.value / 500.0f) * 1.5708f;

    pid.setpoint(target);

    gyro.update();
    double pid_output = pid.compute(gyro.heading);

    drivetrain.wheel_steer(0, (int) pid_output);

    Serial.print("target:");
    Serial.print(target);
    Serial.print(", heading:");
    Serial.print(gyro.heading);
    Serial.print(", pid_output:");
    Serial.print(pid_output);
    Serial.print(", P:");
    Serial.print(Kp);
    Serial.print(", I:");
    Serial.print(Ki);
    Serial.print(", D:");
    Serial.println(Kd);

    delay(10);
}
