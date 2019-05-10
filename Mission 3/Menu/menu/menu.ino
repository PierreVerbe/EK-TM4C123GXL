int pinLM35 = 26;
int pinPhoto = 25;
float temperature;

void setup() {
Serial.begin(9600);

Serial1.begin(9600);
Serial1.write("AT+NAMEmichel");
Serial1.read();
}

long menu() {
  Serial1.println("Veuillez entrer le chiffre du service souhaité.");
  Serial1.println("1. Afficher la température.");
  Serial1.println("2. Affichaer la luminosité."); 
  Serial1.println("3. Action sur l'actionneur."); 
  Serial1.println("4. Afficher la distance."); 
  Serial1.println("0. Quitter.");
  long choix = -1;

  while(1){
    choix = Serial1.read(); 
    
    if(choix == 48) return 0;
    if(choix == 49) return 1;
    if(choix == 50) return 2;
    if(choix == 51) return 3;
    if(choix == 52) return 4;
    
  }

}

void getTemp() {
  temperature = analogRead(pinLM35) ;
  temperature = map(temperature, 0, 4095, 0, 3300);
  temperature = temperature/10;
  Serial.println(temperature);

  int inByte = Serial1.read();
  Serial1.write("Température : "); 
  Serial1.print(temperature); 
  Serial1.write(" °C\n");
  delay(250);
}

void loop() {

    if(menu() == 1){
      Serial1.println("AFFICHAGE DE LA TEMPERATURE EN COURS"); 
      getTemp();
    }
    else{
    Serial1.println("RIEN"); 
    }
    

//photoReading = analogRead(pinPhoto);
  //Serial.println(photoReading);
    
}
