int pinPhoto = 25;
int photoReading;

void setup() {
 Serial.begin(9600);
}

void loop() {
  photoReading = analogRead(pinPhoto);
  Serial.println(photoReading);
}
