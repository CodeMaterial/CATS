#pragma once

#include "Arduino.h"
#include <PulsePosition.h>

namespace Transmitter_components {

    class Transmitter_component {
    public:
        virtual void calibrate() = 0;

        virtual bool is_calibrated() = 0;

        virtual void update() = 0;

        virtual void print_state() = 0;
    };

    class Switch : public Transmitter_component {
    public:
        Switch(PulsePositionInput *ppm, int channel);

        Switch(PulsePositionInput *ppm, int channel, const char *name);

        void calibrate();

        bool is_calibrated();

        void update();

        void print_state();

        bool value;

    private:
        PulsePositionInput *ppm;
        int channel;
        const char *name;
        int raw_cen = 1500;
        int raw_value;
        bool calibrated = false;
        int calibration_timeout = 10000;
    };

    class Knob : public Transmitter_component {
    public:
        Knob(PulsePositionInput *ppm, int channel);

        Knob(PulsePositionInput *ppm, int channel, const char *name);

        void calibrate();

        bool is_calibrated();

        void update();

        void print_state();

        int value;

    private:
        PulsePositionInput *ppm;
        int channel;
        const char *name;
        int raw_max = 2000;
        int raw_min = 1000;
        int raw_cen = 1500;
        int raw_value;
        bool calibrated = false;
        int calibration_timeout = 10000;
    };


    class Stick : public Transmitter_component {
    public:
        Stick(PulsePositionInput *ppm, int x_channel, int y_channel);

        Stick(PulsePositionInput *ppm, int x_channel, int y_channel, const char *name);

        Knob x;
        Knob y;

        void calibrate();

        bool is_calibrated();

        void update();

        void print_state();

    private:
        const char *name;
    };
}