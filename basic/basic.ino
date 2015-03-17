int SR = 6;
int SL = 5;
int DR = 8;
int DL = 7;

void setup()
{
  int i;
  for(i=5;i<=8;i++)
  pinMode(i, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int leftspeed = 255; //255 is maximum speed
  int rightspeed = 255;
  analogWrite (SR,255);
  digitalWrite(DR,HIGH);
  analogWrite (SL,255);
  digitalWrite(DL,HIGH);
  delay(100);
}
