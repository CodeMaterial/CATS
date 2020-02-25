#include <PulsePosition.h>

#include <Servo.h>

#define PIN_ESC_L 0 // TODO
#define PIN_ESC_R 0 // TODO
#define PIN_PMM 0   // TODO
#define PIN_LED 13

#define PWM_ESC_MAX 0 //in Microseconds // TODO
#define PWM_ESC_CEN (PWM_ESC_MAX+PWM_ESC_MIN)/2
#define PWM_ESC_MIN 0 //in Microseconds // TODO

#define CHNL_RX 1
#define CHNL_RX_MAX 1915
#define CHNL_RX_CEN 1493 // Error = 0
#define CHNL_RX_MIN 1075
#define CHNL_LY 2
#define CHNL_LY_MAX 1917
#define CHNL_LY_CEN 1491 // Error = +2
#define CHNL_LY_MIN 1069
#define CHNL_RY 3
#define CHNL_RY_MIN 1068
#define CHNL_RY_MAX 1912
#define CHNL_LX 4
#define CHNL_LX_MIN 1082
#define CHNL_LX_CEN 1482 // Error = -17
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

#define DIR_UP 1
#define DIR_DWN -1

#define RESOLUTION 500

#define DEBUG false;


int remap(int raw_value, int min, int center, int max, float sensitivity){
  if (raw_value > center){
    return map(raw_value, center, max, 0, sensitivity*RESOLUTION)
  }else{
    return map(raw_value, min, center, -sensitivity*RESOLUTION, 0)
  }
}

void move(int l_control, int r_control){

  int esc_l_ms = map(l_control, -RESOLUTION, RESOLUTION, PWM_ESC_MIN, PWM_ESC_MAX);
  int esc_r_ms = map(r_control, -RESOLUTION, RESOLUTION, PWM_ESC_MIN, PWM_ESC_MAX);

  esc_l.writeMicroseconds(esc_l_ms);
  esc_r.writeMicroseconds(esc_r_ms);
  
  if (DEBUG){
    Serial.print("L: ");
    Serial.print(l_control);
    Serial.print(" (");
    Serial.print(esc_l_ms);
    Serial.print(") R: ");
    Serial.print(r_control);
    Serial.print(" (");
    Serial.print(esc_r_ms);
    Serial.println(")");
  }
}


Servo esc_l;
Servo esc_r;
PulsePositionInput ppm;

float x_sensitivity = 1.0;
float y_sensitivity = 1.0;

int orientation = DIR_UP;


void setup() {
  Serial.begin(9600);
  if(DEBUG){
    while (!Serial) {
      delay(1);
    }
    Serial.println("Debug serial connected")
  }
  
  Serial.println("Initialising radio connection")
  ppm.begin(PIN_PMM);

  Serial.println("Initialising ESCs")
  esc_l.attach(PIN_ESC_L);
  esc_l.writeMicroseconds(PWM_ESC_CEN)
  esc_r.attach(PIN_ESC_R);
  esc_r.writeMicroseconds(PWM_ESC_CEN)

  Serial.println("Setup complete")
}

void loop() {
  
  if (ppm.available() > 0) {
    float x_raw = ppm.read(CHNL_LX);
    int x_input = remap(x_raw, CHNL_LX_MIN, CHNL_LX_CEN, CHNL_LX_MAX, x_sensitivity);

    float y_raw = ppm.read(CHNL_LY);
    int y_input = remap(y_raw, CHNL_LY_MIN, CHNL_LY_CEN, CHNL_LY_MAX, y_sensitivity);

    orientation = ppm.read(CHNL_LLS) > CHNL_LLS_CEN ? DIR_UP : DIR_DWN;

    int l_control = y_input + x_input*orientation;
    int r_control = y_input - x_input*orientation;

    move(l_control, r_control);
  }

}
