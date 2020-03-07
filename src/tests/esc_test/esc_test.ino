#include "TFP_ESC.h"
#include "TFP_Gyro.h"

TFP_Gyro gyro;
TFP_ESC esc;

void setup(void) {
    Serial.begin(9600);

    gyro.begin();

    esc.begin(5, &gyro);

    while (!Serial) {
        delay(1);
    }
}


void loop() {
    delay(100);
}
