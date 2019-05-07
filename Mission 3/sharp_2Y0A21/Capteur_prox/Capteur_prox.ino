short capteur_prox = 25; 

int valueProx = 0;
int distanceCm = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {  
   valueProx = analogRead(capteur_prox);
   valueProx = map(valueProx, 0, 4095, 30, 4);
   Serial.println(valueProx - 2); 
}
