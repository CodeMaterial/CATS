#include "TFP_Drivetrain.h"

Drivetrain drivetrain;

void setup(void) {
    Serial.begin(9600);

    while (!Serial) {
        delay(1);
    }
    Serial.println("Serial connected");

    drivetrain.begin();
}


void loop() {
    for (int i = 0; i < 100; i++) {
//        Serial.println(i);
//        drivetrain.SkidSteer(i, i);
        delay(100);
    }
}
