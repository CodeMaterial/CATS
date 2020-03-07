#include "TFP_ESC.h"
#include "TFP_Gyro.h"

TFP_Gyro gyro;
TFP_ESC esc;

void setup(void) {
    Serial.begin(9600);


    while (!Serial) {
        delay(1);
    }
    Serial.println("Serial connected");

    gyro.begin();
    esc.begin(5, &gyro);
}


void loop() {
//    for(int i=0; i<100; i++){
//        Serial.println(i);
//        esc.set_speed(i);
        delay(100);
//    }
}
