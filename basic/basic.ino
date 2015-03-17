int SR = 6;
int SL = 5;
int DR = 8;
int DL = 7;
int SPEED_FAST = 255;
int SPEED_MED = 170;
int SPEED_SLOW = 84;
int SPEED_NONE = 0;
int DIR_FW = LOW;
int DIR_BW = HIGH;

void setup()
{
  int i;
  for(i=5;i<=8;i++)
  pinMode(i, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  analogWrite (SR, SPEED_FAST);
  digitalWrite(DR, DIR_FW);

  analogWrite (SL, SPEED_FAST);
  digitalWrite(DL, DIR_FW);
}
