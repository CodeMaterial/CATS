#include "TFP_Transmitter.h"

Transmitter_components::Switch::Switch(PulsePositionInput *ppm_in, int channel_in)
        : ppm(ppm_in),
          channel(channel_in) {
};

Transmitter_components::Switch::Switch(PulsePositionInput *ppm_in, int channel_in, const char *name_in)
        : ppm(ppm_in),
          channel(channel_in),
          name(name_in) {
};

void Transmitter_components::Switch::calibrate() {

    update();
    int previous_raw_value = raw_value;
    Serial.print("\n\n>> Please flip the ");
    Serial.println(name);

    for (int i = 0; i < (calibration_timeout / 10); i++) {
        delay(10);
        update();
        if (abs(previous_raw_value - raw_value) > 100) {
            raw_cen = (previous_raw_value + raw_value) / 2;
            calibrated = true;
            break;
        }
    }
    print_state();
    Serial.print(name);
    Serial.println(calibrated ? " Has been calibrated successfully" : " Has not been calibrated");
};

bool Transmitter_components::Switch::is_calibrated() {
    return calibrated;
};

void Transmitter_components::Switch::update() {
    raw_value = ppm->read(channel);
    value = raw_value > raw_cen;
};

Transmitter_components::Knob::Knob(PulsePositionInput *ppm_in, int channel_in)
        : ppm(ppm_in),
          channel(channel_in),
          name("Unknown Knob") {
};

Transmitter_components::Knob::Knob(PulsePositionInput *ppm_in, int channel_in, const char *name_in)
        : ppm(ppm_in),
          channel(channel_in),
          name(name_in) {
};


void Transmitter_components::Knob::calibrate() {
    Serial.print("\n\n>> Please move ");
    Serial.print(name);
    Serial.println(" for 3 seconds");

    update();

    int resting = value;

    for (int i = 0; i < (calibration_timeout / 10); i++) {
        delay(10);
        update();
        if(abs(value - resting) > 100){
            break;
        }
    }
    Serial.println("Recording...");

    int motion_min = raw_cen;
    int motion_max = raw_cen;
    for (int i = 0; i < 300; i++) {
        delay(10);
        update();
        if (raw_value > motion_max) {
            motion_max = raw_value;
        }
        if (raw_value < motion_min) {
            motion_min = raw_value;
        }
    }
    if ((motion_max - motion_min) > 500) {
        calibrated = true;
        raw_min = motion_min;
        raw_max = motion_max;
        raw_cen = (motion_max + motion_min) / 2;
    }

    print_state();
    Serial.print(name);
    Serial.println(calibrated ? " Has been calibrated successfully" : " Has not been calibrated");
};

bool Transmitter_components::Knob::is_calibrated() {
    return calibrated;
};

void Transmitter_components::Knob::update() {
    raw_value = ppm->read(channel);
    value = map(raw_value, raw_min, raw_max, 0, 1000);
};

Transmitter_components::Stick::Stick(PulsePositionInput *ppm, int x_channel, int y_channel)
        : x(ppm, x_channel, "x"),
          y(ppm, y_channel, "y"),
          name("Unknown Stick") {
};

Transmitter_components::Stick::Stick(PulsePositionInput *ppm, int x_channel, int y_channel, const char *name)
        : x(ppm, x_channel, "x"),
          y(ppm, y_channel, "y"),
          name(name) {
};


void Transmitter_components::Stick::calibrate() {
    Serial.print("\n\nCalibrating ");
    Serial.println(name);
    x.calibrate();
    y.calibrate();
};

bool Transmitter_components::Stick::is_calibrated() {
    return x.is_calibrated() && y.is_calibrated();
};

void Transmitter_components::Stick::update() {
    x.update();
    y.update();
}

void Transmitter_components::Switch::print_state() {
    update();
    Serial.print("\n---------------- State of ");
    Serial.print(name);
    Serial.print(" ----------------\nvalue: ");
    Serial.print(value);
    Serial.print(" | raw: ");
    Serial.print(raw_value);
    Serial.print(" | center: ");
    Serial.print(raw_cen);
    Serial.print(" | calibrated: ");
    Serial.println(is_calibrated());
};

void Transmitter_components::Knob::print_state() {
    update();
    Serial.print("\n---------------- State of ");
    Serial.print(name);
    Serial.print(" ----------------\nvalue: ");
    Serial.print(value);
    Serial.print(" | raw: ");
    Serial.print(raw_value);
    Serial.print(" | min: ");
    Serial.print(raw_min);
    Serial.print(" | center: ");
    Serial.print(raw_cen);
    Serial.print(" | max: ");
    Serial.print(raw_max);
    Serial.print(" | calibrated: ");
    Serial.println(is_calibrated());
};

void Transmitter_components::Stick::print_state() {
    Serial.print("\n---------------- State of ");
    Serial.print(name);
    Serial.println(" ----------------");
    x.print_state();
    y.print_state();
};