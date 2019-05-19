int pinLM35 = 26;
int pinPhoto = 25;
short bargraph1 = 2;
short bargraph2 = 34;
const String COURANTE = "1";
const String SYNCHRO = "2";
const String RAPIDE = "3";
const String OBJ = "G02D";
const String REQ_ECR = "1";

void setup() {
  pinMode(bargraph1, OUTPUT); 
  pinMode(bargraph2, OUTPUT);
  
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial1.write("AT+NAMEmichel\n");
  Serial.println("***** DEMARRAGE DU SERVICE G02D *****");
}

void loop() {
  delay(5000);
  reqSynchro();
  delay(5000);
  Serial.println("**** ENVOI DE LA TEMPERATURE ****");
  reqTempCour();
  getAns();
  delay(5000);
  Serial.println("**** ENVOI DE LA LUMINOSITE ****");
  reqLumCour();
  getAns();
}

void reqTempCour(){
  String trame = COURANTE + OBJ + REQ_ECR + "3" + "01" + getTemp() + "0125";
  String check = getCheckSum(trame);
  String trame_finale = trame + check;
  Serial1.println(trame_finale);
  digitalWrite(bargraph1, HIGH);
  delay(100);
  digitalWrite(bargraph1, LOW);
  //getAns();
}

void reqLumCour(){
  String trame = COURANTE + OBJ + REQ_ECR + "3" + "01" + getLum() + "0125";
  String check = getCheckSum(trame);
  String trame_finale = trame + check;
  Serial1.println(trame_finale);
  digitalWrite(bargraph1, HIGH);
  delay(100);
  digitalWrite(bargraph1, LOW);
  //getAns();
}

void reqSynchro(){
  String trame = SYNCHRO + "101";
  Serial1.println(trame);
  digitalWrite(bargraph1, HIGH);
  delay(100);
  digitalWrite(bargraph1, LOW);
}

String getTemp() {
  float temperature = map(analogRead(pinLM35), 0, 4095, 0, 3300);
  temperature = temperature/10;
  int temp = (int)temperature;
  Serial.println("TEMPERATURE ACTUELLE : " + String(temp) + "°C");
  String temp2 = String(temp, HEX);
  temp2 = hexToFour(temp2);

  return temp2;
}

String getLum() {
  float luminosite = analogRead(pinPhoto);
  int lum = (int)map(luminosite, 0, 4095, 0, 100);
  Serial.println("LUMINOSITE ACTUELLE : " + String(lum) + " %");
  String lum2 = String(lum, HEX);
  lum2 = hexToFour(lum2);

  return lum2;
}

void getAns(){
  String ans = "";
  int delai = 100;
  do{
    ans = Serial1.read();
    Serial.println("ANSWER = " + ans);
    delay(100);
    delai = delai + 100;
      if(delai > 5000){
        Serial.println("ERREUR");
      }
  }
  while(ans == "-1");
}

String getCheckSum(String trame){
  int i = 0;
  int chk = 0;
  for (i = 0; i < trame.length(); i = i + 1){
    chk = chk + (int)trame.charAt(i);
  }
  return String(chk % 256, HEX);
}

String hexToFour(String a){
  while(a.length() < 4){
    a = "0" + a;
  }
  return a;
}
