#pragma once

#include <EEPROM.h>
#include <PulsePosition.h>

namespace Transmitter_components {

    struct Calibration{
        int raw_max = 2000;
        int raw_min = 1000;
        int raw_cen = 1500;
        bool calibrated = false;
        int calibration_timeout = 10000;
    };


    class Switch {
    public:
        Switch(PulsePositionInput *ppm, int channel);

        Switch(PulsePositionInput *ppm, int channel, const char *name);

        void calibrate();

        void save_calibration();

        void load_calibration();

        bool is_calibrated();

        void update();

        void print_state();

        bool value;

    private:
        PulsePositionInput *ppm;
        int channel;
        const char *name;
        int raw_value;
        Calibration calibration;
    };

    class Knob {
    public:
        Knob(PulsePositionInput *ppm, int channel);

        Knob(PulsePositionInput *ppm, int channel, const char *name);

        void calibrate();

        void save_calibration();

        void load_calibration();

        bool is_calibrated();

        void update();

        void print_state();

        int value;

    private:
        PulsePositionInput *ppm;
        int channel;
        const char *name;
        int raw_value;
        Calibration calibration;
    };


    class Stick {
    public:
        Stick(PulsePositionInput *ppm, int x_channel, int y_channel);

        Stick(PulsePositionInput *ppm, int x_channel, int y_channel, const char *name);

        Knob x;
        Knob y;

        void calibrate();

        void save_calibration();

        void load_calibration();

        bool is_calibrated();

        void update();

        void print_state();

    private:
        const char *name;
    };
}