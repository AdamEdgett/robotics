#ifndef __LED_ARRAY
#define __LED_ARRAY

#define LED_SENSOR_COUNT 5
#define LED_SAMPLE_COUNT 10

// Factor multiplied by the sense value for testing against floor average
#define LED_TAPE_FACTOR 0.8

class LedArray {
    public:
        LedArray(int start_pin, double tape_factor = LED_TAPE_FACTOR);
        int sensor_pins[LED_SENSOR_COUNT];
        int *floor_average;
        double tape_factor;
        void init();
        void sense(int*);
        char isTape();
};

#endif
