#include <PulsePosition.h>

#include <Servo.h>

#define PIN_ESC_L 0
#define PIN_ESC_R 0
#define PIN_PMM 0
#define PIN_LED 13


#define CHNL_RX 1
#define CHNL_RX_MAX 1915
#define CHNL_RX_CEN 1493
#define CHNL_RX_MIN 1075
#define CHNL_LY 2
#define CHNL_LY_MAX 1917
#define CHNL_LY_CEN 1491
#define CHNL_LY_MIN 1069
#define CHNL_RY 3
#define CHNL_RY_MIN 1068
#define CHNL_RY_MAX 1912
#define CHNL_LX 4
#define CHNL_LX_MIN 1082
#define CHNL_LX_CEN 1482
#define CHNL_LX_MAX 1915
#define CHNL_LN 5
#define CHNL_LN_MIN 1081
#define CHNL_LN_MAX 1917
#define CHNL_RN 6
#define CHNL_RN_MIN 1081
#define CHNL_RN_MAX 1917
#define CHNL_LLS 7
#define CHNL_LLS_CEN 1493
#define CHNL_RSS 8
#define CHNL_RSS_CEN 1493

#define TUNE_KP 0
#define TUNE_KI 0
#define TUNE_KD 0


double setpoint, input, output;
PID pid(&input, &output, &setpoint, TUNE_KP, TUNE_KI, TUNE_KD, DIRECT);


Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);

Servo esc_l;
Servo esc_r;

PulsePositionInput ppm;


float heading;


void reset_heading(){
  heading=0;
}

void setup() {
  esc_l.attach(PIN_ESC_L);
  esc_r.attach(PIN_ESC_R);
  ppm.begin(PIN_PMM);

  reset_heading();
}

void loop() {
  
  if (myIn.available() > 0) {
    int x_raw = myIn.read(CHNL_LX);
    int y_raw = myIn.read(CHNL_LY);
  }

}
