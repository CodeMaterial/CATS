#include "TFP_Transmitter.h"
#include <EEPROM.h>

Transmitter_Component::Transmitter_Component(PulsePositionInput *ppm_in, int channel_in, bool binary_mode_in)
        : ppm(ppm_in),
          channel(channel_in),
          name("Unknown Knob"),
          binary_mode(binary_mode_in) {
};

Transmitter_Component::Transmitter_Component(PulsePositionInput *ppm_in, int channel_in, const char *name_in,
                                     bool binary_mode_in)
        : ppm(ppm_in),
          channel(channel_in),
          name(name_in),
          binary_mode(binary_mode_in) {
};


void Transmitter_Component::calibrate() {

    update();

    if (binary_mode) {

        int previous_raw_value = raw_value;
        Serial.print("\n\n>> Please flip the ");
        Serial.println(name);

        for (int i = 0; i < (calibration.calibration_timeout / 10); i++) {
            delay(10);
            update();
            if (abs(previous_raw_value - raw_value) > 100) {
                calibration.raw_cen = (previous_raw_value + raw_value) / 2;
                calibration.calibrated = true;
                break;
            }
        }
    } else {

        Serial.print("\n\n>> Please move ");
        Serial.print(name);
        Serial.println(" for 3 seconds");

        int resting = value;

        for (int i = 0; i < (calibration.calibration_timeout / 10); i++) {
            delay(10);
            update();
            if (abs(value - resting) > 100) {
                break;
            }
        }
        Serial.println("Recording...");

        int motion_min = calibration.raw_cen;
        int motion_max = calibration.raw_cen;
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
            calibration.calibrated = true;
            calibration.raw_min = motion_min;
            calibration.raw_max = motion_max;
            calibration.raw_cen = (motion_max + motion_min) / 2;
        }

    }

    print_state();
    Serial.print(name);
    Serial.println(calibration.calibrated ? " Has been calibrated successfully" : " Has not been calibrated");
    save_calibration();

};

void Transmitter_Component::save_calibration() {
    EEPROM.put(channel * sizeof(calibration), calibration);
}

void Transmitter_Component::load_calibration() {
    EEPROM.get(channel * sizeof(calibration), calibration);
}


bool Transmitter_Component::is_calibrated() {
    return calibration.calibrated;
};

void Transmitter_Component::update() {
    raw_value = ppm->read(channel);
    value = map(raw_value, calibration.raw_min, calibration.raw_max, 0, 1000);
};


void Transmitter_Component::print_state() {
    update();
    Serial.print("\n---------------- State of ");
    Serial.print(name);
    Serial.print(" ----------------\nvalue: ");
    Serial.print(value);
    Serial.print(" | raw: ");
    Serial.print(raw_value);
    Serial.print(" | min: ");
    Serial.print(calibration.raw_min);
    Serial.print(" | center: ");
    Serial.print(calibration.raw_cen);
    Serial.print(" | max: ");
    Serial.print(calibration.raw_max);
    Serial.print(" | calibrated: ");
    Serial.println(calibration.calibrated);
};