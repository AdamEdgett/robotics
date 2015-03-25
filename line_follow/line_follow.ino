#include <led_array.h>

// Motor pins
#define SPEED_RIGHT 5
#define SPEED_LEFT 6
#define DIR_RIGHT 8
#define DIR_LEFT 7

// IR LED pins
#define LED_SENSOR_COUNT 5
#define LED_START_PIN 14

#define FLOOR_VALUE 64
#define LINE_VALUE 54

// Speed constants
#define SPEED_FAST 255
#define SPEED_MED 170
#define SPEED_SLOW 84
#define SPEED_NONE 0

// Direction constants
#define DIR_FW LOW
#define DIR_BW HIGH

void setup()
{
  for(int i = 5; i <= 8; i++)
    pinMode(i, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  for(int i = LED_START_PIN; i <= LED_START_PIN + LED_SENSOR_COUNT; i++)
    Serial.println(String(i) + ': ' + String(analogRead(i)));
  delay(1000);
}

void stop()
{
  Serial.println("stop");
  analogWrite(SPEED_LEFT, SPEED_NONE);
  analogWrite(SPEED_RIGHT, SPEED_NONE);
}

void goForward()
{
  Serial.println("go forward");
  analogWrite(SPEED_LEFT, SPEED_FAST);
  analogWrite(SPEED_RIGHT, SPEED_FAST);
}

void goLeft()
{
  Serial.println("go left");
  analogWrite(SPEED_LEFT, SPEED_NONE);
  analogWrite(SPEED_RIGHT, SPEED_FAST);
}

void goRight()
{
  Serial.println("go right");
  analogWrite(SPEED_LEFT, SPEED_FAST);
  analogWrite(SPEED_RIGHT, SPEED_SLOW);
}

void correctLeft()
{
  Serial.println("correct left");
  analogWrite(SPEED_LEFT, SPEED_SLOW);
  analogWrite(SPEED_RIGHT, SPEED_MED);
}

void correctRight()
{
  Serial.println("correct right");
  analogWrite(SPEED_LEFT, SPEED_MED);
  analogWrite(SPEED_RIGHT, SPEED_SLOW);
}

void pivotLeft()
{
  Serial.println("pivot left");
  digitalWrite(DIR_RIGHT, DIR_BW);
  analogWrite(SPEED_LEFT, SPEED_FAST);
  analogWrite(SPEED_RIGHT, SPEED_SLOW);
}

void pivotRight()
{
  Serial.println("pivot right");
  digitalWrite(DIR_LEFT, DIR_BW);
  analogWrite(SPEED_LEFT, SPEED_FAST);
  analogWrite(SPEED_RIGHT, SPEED_SLOW);
}
