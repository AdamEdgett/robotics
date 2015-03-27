#include <Arduino.h>
#include "LedArray.h"

LedArray::LedArray(int start_pin, double tape_factor)
{
    this->tape_factor = tape_factor;

    for (int i = 0; i < LED_SENSOR_COUNT; i++)
    {
        this->sensor_pins[i] = start_pin+i;
    }
}

void LedArray::init()
{
    this->floor_average = new int[LED_SENSOR_COUNT]();

    for (int j = 0; j < LED_SAMPLE_COUNT; j++)
    {
        this->sense(this->floor_average);
        delay(100);
    }

    Serial.println("Calibration");
    for (int i = 0; i < LED_SENSOR_COUNT; i++)
    {
        this->floor_average[i] = this->floor_average[i] / LED_SAMPLE_COUNT;
        Serial.print(this->floor_average[i]);
        Serial.print("\t");
    }
    Serial.println("");
}

void LedArray::sense(int *values)
{
    for (int i = 0; i < LED_SENSOR_COUNT; i++)
    {
        values[i] += analogRead(this->sensor_pins[i]);
    }
}

char LedArray::isTape()
{
    int *values = new int[LED_SENSOR_COUNT]();

    for (int i = 0; i < LED_SENSOR_COUNT; i++)
    {
        this->sense(values);
    }

    for (int i = 0; i < LED_SENSOR_COUNT; i++)
    {
        values[i] = values[i] / LED_SENSOR_COUNT;
    }

    char ret = 0;

    Serial.println("Sensor values");
    for (int i = 0; i < LED_SENSOR_COUNT; i++)
    {
        if (values[i] < (this->floor_average[i] * tape_factor))
        {
            Serial.print(values[i]);
            Serial.print("\t");
            ret = (ret << 1) + 1;
        }
        else
        {
            Serial.print(values[i]);
            Serial.print("\t");
            ret = (ret << 1);
        }
    }
    Serial.println();

    delete[] values;

    return ret;
}
