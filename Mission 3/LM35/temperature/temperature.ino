int pinLM35 = 24;
float temperature;

void setup() {
Serial.begin(9600);
}

void loop() {
  temperature = analogRead(pinLM35) ;
  temperature = map(val, 0, 4095, 0, 3300);
  temperature = temperature/10;
  Serial.println(temperature);
}
