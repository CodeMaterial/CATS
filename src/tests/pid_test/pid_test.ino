#include <PIDController.h>
#include "TFP_Drivetrain.h"
#include "TFP_Gyro.h"

Drivetrain drivetrain;
PIDController pid; // Create an instance of the PID controller class, called "pid"
TFP_Gyro gyro;

void setup() {
    Serial.begin(9600);   // Some methods require the Serial.begin() method to be called first

    pid.begin();          // initialize the PID instance
    pid.setpoint(0);    // The "goal" the PID controller tries to "reach"
    pid.tune(700, 0, 0);    // Tune the PID, arguments: kP, kI, kD
    pid.limit(-500, 500);    // Limit the PID output between 0 and 255, this is important to get rid of integral windup!

    drivetrain.begin();
    drivetrain.load_calibration();
    gyro.begin();
    gyro.calibrate();
}

void loop() {
    gyro.update();
    int steer = pid.compute(gyro.heading);    // Let the PID compute the value, returns the optimal output
    drivetrain.wheel_steer(0, steer);
    Serial.print(gyro.heading);
    Serial.print(" ");
    Serial.println(steer);
    delay(10);                                // Delay for 30 ms
}
