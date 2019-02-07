//Led PB_5 -> Rouge
//    PB_0 -> Vert
//    PB_1 -> Blue
      
short LedR = 2 ;
short LedB = 3 ;
short LedG = 4 ;

void setup() {
 pinMode(LedR, OUTPUT); 
 pinMode(LedG, OUTPUT); 
 pinMode(LedB, OUTPUT); 
}

void loop() {
  //rien
  digitalWrite(LedR, LOW);
  digitalWrite(LedG, LOW);
  digitalWrite(LedB, LOW);
  delay(1000);

  //Rouge
  digitalWrite(LedR, HIGH);
  digitalWrite(LedG, LOW);
  digitalWrite(LedB, LOW);
  delay(1000);

  //Vert
  digitalWrite(LedR, LOW);
  digitalWrite(LedG, HIGH);
  digitalWrite(LedB, LOW);
  delay(1000);

  //Bleu
  digitalWrite(LedR, LOW);
  digitalWrite(LedG, LOW);
  digitalWrite(LedB, HIGH);
  delay(1000);

  //Blanc
  digitalWrite(LedR, HIGH);
  digitalWrite(LedG, HIGH);
  digitalWrite(LedB, HIGH);
  delay(1000);

  //jaune
  digitalWrite(LedR, HIGH);
  digitalWrite(LedG, HIGH);
  digitalWrite(LedB, LOW);
  delay(1000);
}
