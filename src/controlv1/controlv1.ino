#include <Servo.h>

// objets servo pour envoi d'une valeure
Servo escMoteur1, escMoteur2, escMoteur3, escMoteur4;

//Acquisition des commandes
int throttle; // poussée générale
int rollOffset; // inclinaison gauche/droite
int pitchOffset; // inclinaison avant/arriere
int yawOffset; // rotation sur lui même

//contrôle des moteurs
// modifier ces valeurs change inclinaison avance recule
int puissanceMoteur1, puissanceMoteur3;
// modifier ces valeurs change inclinaison gauche droite
int puissanceMoteur2, puissanceMoteur4;

void setup() {
  // put your setup code here, to run once:
  escMoteur1.attach($*PIN*);
  escMoteur2.attach($*PIN*);
  escMoteur3.attach($*PIN*);
  escMoteur4.attach($*PIN*);
}

void loop() {
  // put your main code here, to run repeatedly:
  calculPuissanceMoteurs();
}

void calculPuissanceMoteurs() {
  puissanceMoteur1 = throttle + pitchOffset + yawOffset;
  puissanceMoteur2 = throttle + rollOffset - yawOffset;
  puissanceMoteur3 = throttle - pitchOffset + yawOffset;
  puissanceMoteur4 = throttle - rollOffset - yawOffset;
}

void 


