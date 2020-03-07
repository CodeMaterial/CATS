#include <Servo.h>
#include "TFP_Gyro.h"
#include "TFP_ESC.h"

struct Drivetrain_Calibration {
    int steer_adjust = 0;
};

class Drivetrain {
public:

    Drivetrain();

    void calibrate();

    void save_calibration();

    void load_calibration();

    void SkidSteer(int left, int right);

    void WheelSteer(int power, int steer);

private:
    TFP_ESC esc_l;
    TFP_ESC esc_r;
    TFP_Gyro gyro;
    Drivetrain_Calibration calibration;
}