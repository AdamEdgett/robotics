#ifndef __LED_ARRAY
#define __LED_ARRAY

#define LED_SENSOR_COUNT 5
#define LED_SAMPLE_COUNT 10

// Factor multiplied by the sense value for testing against floor average
#define LED_TAPE_FACTOR 0.80

class LedArray {
    public:
        LedArray(int);
        LedArray(int, int, int, int, int);
        int sensor_pins[LED_SENSOR_COUNT];
        int *floor_average;
        void init();
        void sense(int*);
        char isTape();
};

#endif
