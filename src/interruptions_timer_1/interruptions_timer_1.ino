#include <avr/io.h>
#include <avr/interrupt.h>

int cpt=0;
int valeurTr=1000;
int valeurLu=0;
void setup()
{
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(A0,INPUT);
  noInterrupts(); // désactiver toutes les interruptions

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 399;// = (16*10^6) / (5000*8) - 1 (must be <65536) 
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bits for 8 prescaler
  TCCR1B |= (1 << CS11); 
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  interrupts(); // activer toutes les interruptions
}

ISR(TIMER1_COMPA_vect) //timer1 interrupt 5KHz
{
  cpt=cpt+1;
  if(cpt%100==0) {
    if (cpt==5000) {
      valeurLu=analogRead(0);
      valeurTr = map(valeurLu,0,1023,5,10);
      Serial.println(valeurTr);
      digitalWrite(8, HIGH);
      cpt=0;
      Serial.println("tic"); 
    } else {
      valeurLu=analogRead(0);
      valeurTr = map(valeurLu,0,1023,5,10);
      Serial.println(valeurTr);
      digitalWrite(8, HIGH);     
    }   
  }
  else if(cpt==5000){
    cpt=0;
    Serial.println("tic");
  }
  else if(cpt%100==valeurTr){
    digitalWrite(8, LOW);
  }
}

void loop()
{
  // Votre application ici...
  
}
