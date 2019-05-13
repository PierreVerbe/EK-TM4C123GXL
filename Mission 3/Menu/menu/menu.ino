int pinLM35 = 26;
int pinPhoto = 25;
float temperature;
float luminosite;
const String COURANTE = "1";
const String SYNCHRO = "2";
const String RAPIDE = "3";
const String OBJ = "G02D";
const String REQ_ECR = "1";
//const String CAP_TEMP = "3";

void setup() {
Serial.begin(9600);

Serial1.begin(9600);
Serial1.write("AT+NAMEmichel\n");
Serial1.write("****** DEMARRAGE DU SERVICE ******\n");
Serial1.read();
}

void loop() {
  req_Cour();
  Serial1.println("Veuillez entrer le chiffre du service souhaité.");
  Serial1.println("1. Afficher la température.");
  Serial1.println("2. Affichaer la luminosité."); 
  Serial1.println("3. Action sur l'actionneur."); 
  Serial1.println("4. Afficher la distance."); 
  Serial1.println("0. Quitter.");
  
  if(menu() == 1){
    Serial1.println("AFFICHAGE DE LA TEMPERATURE EN COURS"); 
    getTemp();
    req_Cour();
  }
  else if(menu() == 2){
    Serial1.println("AFFICHAGE DE LA LUMINOSITE EN COURS");
    getLum();
  }
  else{
    Serial1.println("RIEN"); 
  }

    

//photoReading = analogRead(pinPhoto);
  //Serial.println(photoReading);
    
}

long menu() {
  long choix = -1;

  while(choix == -1){
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

void getLum(){
  luminosite = analogRead(pinPhoto);
  luminosite = map(luminosite, 0, 4095, 0, 100);
  Serial1.write("Luminosité : ");
  Serial1.print(luminosite);
  Serial1.write(" %\n");
  delay(250);
}

void req_Cour(){
  String trame = COURANTE + OBJ + REQ_ECR + "3" + "01" + req_Temp() + "0125";
  String check = getCheckSum(trame);
  String trame_finale = trame + check;
  Serial1.println(trame_finale);
}

String getCheckSum(String trame){
  int i = 0;
  int chk = 0;
  for (i = 0; i < trame.length(); i = i + 1){
    chk = chk + (int)trame.charAt(i);
  }
  return String(chk % 256, HEX);
}

String req_Temp() {
  temperature = analogRead(pinLM35) ;
  temperature = map(temperature, 0, 4095, 0, 3300);
  temperature = temperature/10;
  int temp = (int)temperature;
  Serial.println(temp);
  return String(temp, HEX);
  //Serial.println(temperature);

  //int inByte = Serial1.read();
  //Serial1.write("Température : "); 
  //Serial1.print(temperature); 
  //Serial1.write(" °C\n");
  //delay(250);
}
