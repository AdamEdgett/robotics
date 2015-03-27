#include <LedArray.h>

// Motor pins
#define SPEED_RIGHT 5
#define SPEED_LEFT 6
#define DIR_RIGHT 8
#define DIR_LEFT 7

// IR LED pins
#define LED_SENSOR_COUNT 5
#define LED_START_PIN 14

#define LED_TAPE_FACTOR 0.95

// Speed constants
#define SPEED_FAST 170
#define SPEED_MED 110
#define SPEED_SLOW 50
#define SPEED_NONE 0

// Direction constants
#define DIR_FW LOW
#define DIR_BW HIGH

LedArray ledArray(LED_START_PIN, LED_TAPE_FACTOR);

void setup()
{
  for (int i = 5; i <= 8; i++)
    pinMode(i, OUTPUT);

  delay(500);
  Serial.begin(9600);

  ledArray.init();
}

void loop() {
  // Default to forward
  digitalWrite(DIR_RIGHT, DIR_FW);
  digitalWrite(DIR_LEFT, DIR_FW);

  int tapeValues = ledArray.isTape();
  Serial.print("binary values: ");
  Serial.println(tapeValues, BIN);
  switch (tapeValues) {
    case B00000:
    case B00100:
    case B01010:
    case B01110:
      goForward();
      break;

    case B01000:
    case B01100:
      correctLeft();
      break;

    case B10000:
    case B11000:
      goLeft();
      break;

    case B00010:
    case B00110:
      correctRight();
      break;

    case B00001:
    case B00011:
      goRight();
      break;

    // left corner
    case B10100:
    case B11100:
    case B10110:
    case B11010:
    case B11110:
      pivotLeft();
      break;

    // right corner
    case B00111:
    case B00101:
    case B01101:
    case B01011:
    case B01111:
      pivotRight();
      break;

    default:
        break;
  }
}

void stop() {
    Serial.println("stop");
    analogWrite(SPEED_LEFT, SPEED_NONE);
    analogWrite(SPEED_RIGHT, SPEED_NONE);
}

void goForward() {
    Serial.println("go forward");
    analogWrite(SPEED_LEFT, SPEED_FAST);
    analogWrite(SPEED_RIGHT, SPEED_FAST);
}

void goLeft() {
    Serial.println("go left");
    analogWrite(SPEED_LEFT, SPEED_NONE);
    analogWrite(SPEED_RIGHT, SPEED_FAST);
}

void goRight() {
    Serial.println("go right");
    analogWrite(SPEED_LEFT, SPEED_FAST);
    analogWrite(SPEED_RIGHT, SPEED_SLOW);
}

void correctLeft() {
    Serial.println("correct left");
    analogWrite(SPEED_LEFT, SPEED_SLOW);
    analogWrite(SPEED_RIGHT, SPEED_MED);
}

void correctRight() {
    Serial.println("correct right");
    analogWrite(SPEED_LEFT, SPEED_MED);
    analogWrite(SPEED_RIGHT, SPEED_SLOW);
}

void pivotLeft() {
    Serial.println("pivot left");
    analogWrite(SPEED_LEFT, SPEED_NONE);
    analogWrite(SPEED_RIGHT, SPEED_FAST);
}

void pivotRight() {
    Serial.println("pivot right");
    analogWrite(SPEED_LEFT, SPEED_FAST);
    analogWrite(SPEED_RIGHT, SPEED_NONE);
}
