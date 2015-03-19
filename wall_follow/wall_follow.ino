#include <NewPing.h>

// Motor pins
#define SPEED_RIGHT 6
#define SPEED_LEFT 5
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
NewPing rightSonar(PING_TRIGGER_RIGHT, PING_ECHO_RIGHT, MAX_DISTANCE);

void setup()
{
  for(int i = 5; i <= 8; i++)
    pinMode(i, OUTPUT);

  pinMode(PING_TRIGGER_LEFT, OUTPUT);
  pinMode(PING_TRIGGER_CENTER, OUTPUT);
  pinMode(PING_TRIGGER_RIGHT, OUTPUT);
  pinMode(PING_ECHO_LEFT, INPUT);
  pinMode(PING_ECHO_CENTER, INPUT);
  pinMode(PING_ECHO_RIGHT, INPUT);

  Serial.begin(9600);
}

void loop()
{
  int cmLeft = (leftSonar.ping() / US_ROUNDTRIP_CM);
  int cmCenter = (centerSonar.ping() / US_ROUNDTRIP_CM);
  int cmRight = (rightSonar.ping() / US_ROUNDTRIP_CM);
  Serial.println("Ping left: " + String(cmLeft) + "cm");
  Serial.println("Ping center: " + String(cmCenter) + "cm");
  Serial.println("Ping right: " + String(cmRight) + "cm");

  digitalWrite(DIR_RIGHT, DIR_FW);
  digitalWrite(DIR_LEFT, DIR_FW);

  if (cmCenter < 3) {
    analogWrite(SPEED_LEFT, SPEED_NONE);
    analogWrite(SPEED_RIGHT, SPEED_NONE);
  } else if (cmCenter < 10) {
    analogWrite(SPEED_LEFT, SPEED_FAST);
    digitalWrite(DIR_LEFT, DIR_BW);
    analogWrite(SPEED_RIGHT, SPEED_FAST);
  } else if (cmLeft > 6 && cmLeft < 60) {
    analogWrite(SPEED_LEFT, SPEED_FAST);
    analogWrite(SPEED_RIGHT, SPEED_NONE);
  } else if (cmRight > 6 && cmRight < 60) {
    analogWrite(SPEED_LEFT, SPEED_NONE);
    analogWrite(SPEED_RIGHT, SPEED_FAST);
  } else {
    analogWrite(SPEED_LEFT, SPEED_FAST);
    analogWrite(SPEED_RIGHT, SPEED_FAST);
  }
  delay(40);
}
