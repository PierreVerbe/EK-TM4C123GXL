int pinLM35 = 26;
float temperature;

void setup() {
Serial.begin(9600);
}

void loop() {
  temperature = analogRead(pinLM35) ;
  temperature = map(temperature, 0, 4095, 0, 3300);
  temperature = temperature/10;
  Serial.println(temperature);
}
