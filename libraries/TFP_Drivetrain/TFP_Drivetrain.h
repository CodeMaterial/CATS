#include "TFP_Gyro.h"
#include "TFP_ESC.h"

struct Drivetrain_Calibration {
    int steer_adjust = 0;
};

class Drivetrain {
public:

    Drivetrain();

    bool begin();

    void calibrate(TFP_Gyro *gyro);

    void save_calibration();

    void load_calibration();

    void reset_calibration();

    void skid_steer(int left, int right);

    void wheel_steer(int power, int steer);

    void print_state();

private:
    TFP_ESC esc_l;
    TFP_ESC esc_r;
    Drivetrain_Calibration calibration;
};