// Ce programme permet d'utiliser chaque composant de la carte APP depuis un menu.
// Il faut une application sur smartphone tel que Serial Bluetooth Terminal

int pinH_sens = 15; // pins actionneur
int pinH_inverse = 7;
int pinLM35 = 26; // pin capteur température
int pinPhoto = 25; // pin photorésistance

void setup() {
Serial.begin(9600); // Démarrage moniteur serie

Serial1.begin(9600); // Démarrage Bluetooth
Serial1.write("AT+NAMEG02D\n"); // Assignation nom objet
Serial1.write("****** DEMARRAGE DU SERVICE ******\n");
Serial1.read();
}

void loop() {
  // Menu utilisateur avec plusieurs choix
  Serial1.println("Veuillez entrer le chiffre du service souhaité.");
  Serial1.println("1. Afficher la température.");
  Serial1.println("2. Affichaer la luminosité."); 
  Serial1.println("3. Action sur l'actionneur."); 
  Serial1.println("4. Afficher la distance."); 
  Serial1.println("0. Quitter.");

  // Si l'utilisateur entre 1, affichage température
  if(menu() == 1){
    Serial1.println("AFFICHAGE DE LA TEMPERATURE EN COURS"); 
    getTemp();
  }
  // 2 affichage luminosité
  else if(menu() == 2){
    Serial1.println("AFFICHAGE DE LA LUMINOSITE EN COURS");
    getLum();
  }
  // 3 démarrage actionneur
  else if (menu() == 3){
    Serial1.println("DEMARRAGE DE L'ACTIONNEUR");
    actionneur();
  }
  // sinon ne rien faire
  else{
    Serial1.println("RIEN"); 
  }   
}

long menu() {
  long choix = -1;

  while(choix == -1){
    // tant que l'objet ne recoit rien on lit le choix de l'utilisateur
    choix = Serial1.read(); 
    // ASCII 0x49 --> 1 (température) + retour chariot
    // ASCII 0x50 --> 2 (température) + retour chariot
    // ...
    if(choix == 48) return 0;
    else if(choix == 49) return 1;
    else if(choix == 50) return 2;
    else if(choix == 51) return 3;
    else if(choix == 52) return 4;  
  }
}

void getTemp() {
  // Récupération de la température depuis le capteur LM35
  float temperature = analogRead(pinLM35); // on lit sur le pin analogique
  temperature = map(temperature, 0, 4095, 0, 3300); // valeur récupérée entre 0 et 4095 (12 bits), on la mappe entre 0 et 3300
  temperature = temperature/10;
  Serial.println(temperature);

  int inByte = Serial1.read();
  Serial1.write("Température : "); // Affichage sur le serial Bluetooth 
  Serial1.print(temperature); 
  Serial1.write(" °C\n");
  delay(250);
}

void getLum(){
  // Récupération de la luminosité depuis la photorésistance
  float luminosite = analogRead(pinPhoto);
  luminosite = map(luminosite, 0, 4095, 0, 100);
  Serial1.write("Luminosité : ");
  Serial1.print(luminosite);
  Serial1.write(" %\n");
  delay(250);
}

void actionneur(){
  // Démarrage de l'actionneur grâce au pont en H
  Serial1.println("START moteur 100% bon sens");
  // On envoit 5V dans un sens du pont
  analogWrite(pinH_inverse, 0);
  analogWrite(pinH_sens, 255);
  delay(5000); 

  Serial1.println("START moteur 100% autre sens");
  // On envoit 5V dans l'autre sens du pont
  analogWrite(pinH_sens, 0);
  analogWrite(pinH_inverse, 255);
  delay(5000);

  // On arrête tout
  analogWrite(pinH_sens, 0);
  analogWrite(pinH_inverse, 0);
}
