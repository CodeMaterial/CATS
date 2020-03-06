#include "TFP_Gyro.h"

TFP_Gyro gyro;

void setup(void) {
  Serial.begin(9600);

  while (!Serial) {
    delay(1);
  }
  gyro.begin();
  gyro.calibrate();
}


void loop() {
    gyro.update();
    Serial.println(gyro.is_rotating());
    delay(100);
}
