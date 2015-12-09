
void setup()
{
  pinMode(ledPin, OUTPUT);

  // initialiser le timer1
  noInterrupts(); // désactiver toutes les interruptions
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 31250; // 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS10); // 1 prescaler
  TIMSK1 |= (1 << OCIE1A); // Activer le mode de comparaison
  interrupts(); // activer toutes les interruptions
}

ISR(TIMER1_COMPA_vect) // fonction périodique
{
  digitalWrite(ledPin, digitalRead(ledPin) ^ 1); // Basculer la LED allumée/éteinte
}

void loop()
{
  // Votre application ici...
}
