#include <Servo.h>
int valeurLue;
int valeurTransmise;

Servo esc;
void setup()
{
  esc.attach(9);
  esc.writeMicroseconds(10000);
}

void loop()
{
  valeurLue=analogRead(0);
  valeurTransmise = map(valeurLue,0,1023,1000,1500);
  esc.writeMicroseconds(valeurTransmise);
}
