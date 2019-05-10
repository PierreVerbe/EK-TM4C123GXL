int pinLM35 = 26;
float temperature;

void setup() {
Serial.begin(9600);

Serial1.begin(9600);
Serial1.write("AT+NAMEmichel");
Serial1.read();
}

void loop() {
  temperature = analogRead(pinLM35) ;
  temperature = map(temperature, 0, 4095, 0, 3300);
  temperature = temperature/10;
  Serial.println(temperature);

  int inByte = Serial1.read();
  Serial1.write("Température : "); 
  Serial1.print(temperature); 
  Serial1.write(" °C"); 
  delay(100);
}
