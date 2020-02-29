#include "TFP_Transmitter.h"

Transmitter_components::Switch::Switch(PulsePositionInput *ppm_in, int channel_in)
        : ppm(ppm_in),
          channel(channel_in),
          raw_cen(1500) {
};

Transmitter_components::Switch::Switch(PulsePositionInput *ppm_in, int channel_in, const char *name_in)
        : ppm(ppm_in),
          channel(channel_in),
          name(name_in),
          raw_cen(1500) {
};

void Transmitter_components::Switch::calibrate() {
    Serial.print("Calibrating ");
    Serial.println(name);
    calibrated = true;
};

bool Transmitter_components::Switch::is_calibrated() {
    return calibrated;
};

void Transmitter_components::Switch::update() {
    value = ppm->read(channel) > raw_cen;
};

Transmitter_components::Knob::Knob(PulsePositionInput *ppm_in, int channel_in)
        : ppm(ppm_in),
          channel(channel_in),
          name("Unknown Knob"),
          raw_max(2000),
          raw_min(1000),
          raw_cen(1500) {
};

Transmitter_components::Knob::Knob(PulsePositionInput *ppm_in, int channel_in, const char *name_in)
        : ppm(ppm_in),
          channel(channel_in),
          name(name_in),
          raw_max(2000),
          raw_min(1000),
          raw_cen(1500) {
};


void Transmitter_components::Knob::calibrate() {
    Serial.print("Calibrating ");
    Serial.println(name);
    calibrated = true;
};

bool Transmitter_components::Knob::is_calibrated() {
    return calibrated; //TODO
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
    Serial.print("Calibrating ");
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