//int pinH_sens = 3; //PB_0
//int pinH_inverse = 4; //PB_1

int pinH_sens = 15; //26
int pinH_inverse = 7; //22

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("START moteur 50% bon sens");
  analogWrite(pinH_inverse, 0);
  analogWrite(pinH_sens, 255);
  delay(5000); 

  Serial.println("START moteur 50% autre sens");
  analogWrite(pinH_sens, 0);
  analogWrite(pinH_inverse, 255);
  delay(5000); 
}

//18
