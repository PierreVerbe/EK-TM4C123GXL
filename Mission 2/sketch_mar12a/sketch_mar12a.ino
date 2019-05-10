int pinSignal = 5;
int valueSignal = 0;
float voltage = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  valueSignal = analogRead(pinSignal);
  voltage = valueSignal * (3.3/4096);
  Serial.println(voltage);
  delay(100);
}
