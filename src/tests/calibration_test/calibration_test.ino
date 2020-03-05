#include <Adafruit_FXAS21002C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define NUMBER_SAMPLES 500

Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);


float min_x, max_x, mid_x;
float min_y, max_y, mid_y;
float min_z, max_z, mid_z;

void setup(void) {
    Serial.begin(115200);
    while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens


    /* Initialise the sensor */
    if (!gyro.begin(GYRO_RANGE_1000DPS)) {
        Serial.println("Ooops, no FXAS21002C detected ... Check your wiring!");
        while (1)
            ;
    }



    Serial.println(F("Sensor Lab - Gyroscope Calibration!"));

    Serial.println("Looking for a gyro");

    gyro.printSensorDetails();
    delay(100);

    sensors_event_t event;
    gyro.getEvent(&event);

    min_x = max_x = event.gyro.x;
    min_y = max_y = event.gyro.y;
    min_z = max_z = event.gyro.z;
    delay(10);

    Serial.println(F("Place gyro on flat, stable surface!"));

    Serial.print(F("Fetching samples in 3..."));
    delay(1000);
    Serial.print("2...");
    delay(1000);
    Serial.print("1...");
    delay(1000);
    Serial.println("NOW!");

    float x, y, z;
    for (uint16_t sample = 0; sample < NUMBER_SAMPLES; sample++) {
        sensors_event_t event;
        gyro.getEvent(&event);
        x = event.gyro.x;
        y = event.gyro.y;
        z = event.gyro.z;
        Serial.print(F("Gyro: ("));
        Serial.print(x); Serial.print(", ");
        Serial.print(y); Serial.print(", ");
        Serial.print(z); Serial.print(")");

        min_x = min(min_x, x);
        min_y = min(min_y, y);
        min_z = min(min_z, z);

        max_x = max(max_x, x);
        max_y = max(max_y, y);
        max_z = max(max_z, z);

        mid_x = (max_x + min_x) / 2;
        mid_y = (max_y + min_y) / 2;
        mid_z = (max_z + min_z) / 2;

        Serial.print(F(" Zero rate offset: ("));
        Serial.print(mid_x, 4); Serial.print(", ");
        Serial.print(mid_y, 4); Serial.print(", ");
        Serial.print(mid_z, 4); Serial.print(")");

        Serial.print(F(" rad/s noise: ("));
        Serial.print(max_x - min_x, 3); Serial.print(", ");
        Serial.print(max_y - min_y, 3); Serial.print(", ");
        Serial.print(max_z - min_z, 3); Serial.println(")");
        delay(10);
    }
    Serial.println(F("\n\nFinal zero rate offset in radians/s: "));
    Serial.print(mid_x, 4); Serial.print(", ");
    Serial.print(mid_y, 4); Serial.print(", ");
    Serial.println(mid_z, 4);
}



void loop() {
    delay(10);
}