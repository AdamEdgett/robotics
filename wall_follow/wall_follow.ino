#include <NewPing.h>

// Motor pins
#define SPEED_RIGHT 5
#define SPEED_LEFT 6
#define DIR_RIGHT 8
#define DIR_LEFT 7

// Sonar pins
#define PING_TRIGGER_LEFT 9
#define PING_ECHO_LEFT 10
#define PING_TRIGGER_CENTER 2
#define PING_ECHO_CENTER 3
#define PING_TRIGGER_RIGHT 4
#define PING_ECHO_RIGHT 5
#define MAX_DISTANCE 200

// Speed constants
#define SPEED_FAST 255
#define SPEED_MED 170
#define SPEED_SLOW 84
#define SPEED_NONE 0

// Direction constants
#define DIR_FW LOW
#define DIR_BW HIGH

NewPing leftSonar(PING_TRIGGER_LEFT, PING_ECHO_LEFT, MAX_DISTANCE);
NewPing centerSonar(PING_TRIGGER_CENTER, PING_ECHO_CENTER, MAX_DISTANCE);

void setup()
{
  for(int i = 5; i <= 8; i++)
    pinMode(i, OUTPUT);

  leftSonar.ping();
  centerSonar.ping();
  delay(250);
  Serial.begin(9600);
}

void loop()
{
  int cmLeft = (leftSonar.ping() / US_ROUNDTRIP_CM);
  int cmCenter = (centerSonar.ping() / US_ROUNDTRIP_CM);

  // Correcting max distant timeout values
  if (cmLeft == 0)
    cmLeft = 1000;
  if (cmCenter == 0)
    cmCenter = 1000;

  Serial.println("Ping left: " + String(cmLeft) + "cm");
  Serial.println("Ping center: " + String(cmCenter) + "cm");

  // Default to forward
  digitalWrite(DIR_RIGHT, DIR_FW);
  digitalWrite(DIR_LEFT, DIR_FW);

  if (cmCenter < 6) {
    stop();
  } else if (cmLeft < 20 && cmCenter < 15) {
    pivotRight();
    delay(1000);
    goForward();
    delay(200);
  } else if (cmLeft < 9) {
    correctRight();
  } else if (cmLeft > 13 && cmLeft <= 16) {
    correctLeft();
  } else if (cmLeft > 16 && cmLeft <= 35) {
    correctLeft();
    delay(1000);
    goForward();
    delay(600);
    correctRight();
    delay(750);
  } else if (cmLeft > 35 && cmLeft <= 50) {
    correctLeft();
    delay(1000);
    goForward();
    delay(1000);
    correctRight();
    delay(750);
  } else if (cmLeft > 50) {
    goLeft();
    delay(500);
    goForward();
    delay(200);
  } else {
    goForward();
  }
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
