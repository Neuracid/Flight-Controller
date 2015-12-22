#include <Servo.h>
//pins
//inputs
int pinCh1 = 12;
int pinCh2 = 13;
int pinCh3 = 7;
int pinCh4 = 8;
//outputs
int pinMoteur1 = 3;
int pinMoteur2 = 5;
int pinMoteur3 = 6;
int pinMoteur4 = 9;

// Canaux radio
unsigned long ch1,ch2,ch3,ch4;
// ch1 = gauche/droite
// ch2 = haut/bas
// ch3 = throttle
// ch4 = rotation sur lui même

// objets servo pour envoi d'une valeure
Servo escMoteur1, escMoteur2, escMoteur3, escMoteur4;

//Acquisition des commandes
int throttle = 10; // poussée générale
int rollOffset = 0; // inclinaison gauche/droite
int pitchOffset = 0; // inclinaison avant/arriere
int yawOffset = 0; // rotation sur lui même

//contrôle des moteurs
// modifier ces valeurs change inclinaison avance recule
int puissanceMoteur1, puissanceMoteur3;
// modifier ces valeurs change inclinaison gauche droite
int puissanceMoteur2, puissanceMoteur4;

void setup() {
  // put your setup code here, to run once:
  //initialisation des pins
  escMoteur1.attach(pinMoteur1);
  escMoteur2.attach(pinMoteur2);
  escMoteur3.attach(pinMoteur3);
  escMoteur4.attach(pinMoteur4);
  pinMode(pinCh1,INPUT);
  pinMode(pinCh2,INPUT);
  pinMode(pinCh3,INPUT);
  pinMode(pinCh4,INPUT);

  //interruption à 50Hz pour commande moteurs
  noInterrupts(); // désactiver toutes les interruptions
  //set timer2 interrupt at 50Hz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR2A = 4999;// = (16*10^6) / (50*64) - 1 (must be <65536) 
  // turn on CTC mode
  TCCR2B |= (1 << WGM12);
  // Set CS2 bits for 64 prescaler
  TCCR2B |= (1 << CS22); 
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE1A);
  interrupts(); // activer toutes les interruptions
  // ini à zéro
  escMoteur1.writeMicroseconds(throttle);
  escMoteur2.writeMicroseconds(throttle);
  escMoteur3.writeMicroseconds(throttle);
  escMoteur4.writeMicroseconds(throttle);
}

//timer2 interrupt 50Hz 
ISR(TIMER2_COMPA_vect) {
  escMoteur1.writeMicroseconds(puissanceMoteur1);
  escMoteur2.writeMicroseconds(puissanceMoteur2);
  escMoteur3.writeMicroseconds(puissanceMoteur3);
  escMoteur4.writeMicroseconds(puissanceMoteur4);
}

void calculPuissanceMoteurs() {
  puissanceMoteur1 = throttle + pitchOffset + yawOffset;
  puissanceMoteur2 = throttle + rollOffset - yawOffset;
  puissanceMoteur3 = throttle - pitchOffset + yawOffset;
  puissanceMoteur4 = throttle - rollOffset - yawOffset;
}

void lectureRadio() {
  throttle = pulseIn(pinCh3, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  lectureRadio();
  calculPuissanceMoteurs();
  
}
