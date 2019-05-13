int pinTransistor = 2; //PB_5

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("START moteur 50%");
  analogWrite(pinTransistor, 510);
  delay(1000);
  
  Serial.println("STOP moteur");
  analogWrite(pinTransistor, 0);
  delay(1000); 
}
