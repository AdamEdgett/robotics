#include <Arduino.h>
#include "led_array.h"

LedArray::LedArray(int pin)
{
    for (int i = 0; i < LED_SENSOR_COUNT; i++)
    {
        this->sensor_pins[i] = pin+i;
    }
}

LedArray::LedArray(int pin1, int pin2, int pin3, int pin4, int pin5)
{
    this->sensor_pins[0] = pin1;
    this->sensor_pins[1] = pin2;
    this->sensor_pins[2] = pin3;
    this->sensor_pins[3] = pin4;
    this->sensor_pins[4] = pin5;
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
        if (values[i] < (this->floor_average[i] * LED_TAPE_FACTOR))
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
