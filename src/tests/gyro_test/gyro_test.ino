#include <Adafruit_FXAS21002C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);


float heading = 0;
float rotation_drift = 0;
float noise = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    delay(1);
  }

  if (!gyro.begin(GYRO_RANGE_1000DPS)) {
    Serial.println("Ooops, no FXAS21002C detected ... Check your wiring!");
    while (1)
      ;
  }

  float noise_min = 100000;
  float noise_max = -1000;

  for(int i=0; i<50; i++){
      gyro.getEvent(&event);
      rotation_drift += event.gyro.z;

      if(event.gyro.z > noise_max){
          noise_max = event.gyro.z;
      }
      if(event.gyro.z < noise_min){
          noise_min = event.gyro.z;
      }

      delay(50);
  }
  rotation_drift /= 50;
  noise = noise_max - noise_min;
  Serial.print("drift: "); Serial.println(rotation_drift, 4);
  Serial.print("noise: "); Serial.println(noise, 4);
}


void loop(void) {
  /* Get a new sensor event */
  sensors_event_t event;
  gyro.getEvent(&event);

  /* Display the results (speed is measured in rad/s) */
//  Serial.print(event.gyro.x);
//  Serial.print("  ");
//  Serial.print(event.gyro.y);
//  Serial.print("  ");
//  Serial.println(event.gyro.z);

    event.gyro.z -= rotation_drift;

    heading += (event.gyro.z)/20.0;


//    Zero rate offset: (0.0082, 0.0085, 0.0153) rad/s noise: (0.019, 0.029, 0.031)


    Serial.print(heading*57.2958);
    Serial.print(" ");
    Serial.println((event.gyro.z/20)*57.2958);
    delay(50);
}
