#include "TFP_Gyro.h"

#include <Adafruit_FXAS21002C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


Gyro::Gyro(): gyro(0x0021002C){

};

bool Gyro::begin(){
    gyro.begin(GYRO_RANGE_1000DPS)
};

void Gyro::update(){
    gyro.getEvent(&event);
    velocity = event.gyro.z - rotation_bias;
//    heading += (event.gyro.z)/20.0;
};

void Gyro::reset_heading(){

};

void Gyro::calibrate(){

};


//float heading;
//float velocity;
//float bias;
//long float time_since_update;