short pinPot = 28;
short bargraph1 = 2;
short bargraph2 = 34;
short bargraph3 = 35;
short bargraph4 = 36;
short bargraph5 = 37;

int valuePot = 0;

void setup() {  
 pinMode(bargraph1, OUTPUT); 
 pinMode(bargraph2, OUTPUT); 
 pinMode(bargraph3, OUTPUT); 
 pinMode(bargraph4, OUTPUT); 
 pinMode(bargraph5, OUTPUT); 
 Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  valuePot = analogRead(pinPot);
  //Serial.println(valuePot); 
  
  //bargraph
  valuePot = map(valuePot, 5, 4095, 1, 5);
  Serial.println(valuePot); 
  switch(valuePot){
    case 1:
      digitalWrite(bargraph1, HIGH);
      digitalWrite(bargraph2, LOW);
      digitalWrite(bargraph3, LOW);
      digitalWrite(bargraph4, LOW);
      digitalWrite(bargraph5, LOW);
      break;

   case 2:
      digitalWrite(bargraph1, LOW);
      digitalWrite(bargraph2, HIGH);
      digitalWrite(bargraph3, LOW);
      digitalWrite(bargraph4, LOW);
      digitalWrite(bargraph5, LOW);
      break;


   case 3:
      digitalWrite(bargraph1, LOW);
      digitalWrite(bargraph2, LOW);
      digitalWrite(bargraph3, HIGH);
      digitalWrite(bargraph4, LOW);
      digitalWrite(bargraph5, LOW);
      break;


   case 4:
      digitalWrite(bargraph1, LOW);
      digitalWrite(bargraph2, LOW);
      digitalWrite(bargraph3, LOW);
      digitalWrite(bargraph4, HIGH);
      digitalWrite(bargraph5, LOW);
      break;


   case 5:
      digitalWrite(bargraph1, LOW);
      digitalWrite(bargraph2, LOW);
      digitalWrite(bargraph3, LOW);
      digitalWrite(bargraph4, LOW);
      digitalWrite(bargraph5, HIGH);
      break;
  } 
  delay(1);           
}
