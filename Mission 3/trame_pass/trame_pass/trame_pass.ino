// Ce programme permet de communiquer entre l'objet et la passerelle en Bluetooth grâce à des trames.
// Il est nécessaire de connecter la carte APP avec le logiciel passerelleWindows.jar.
// Les schémas des trames se trouvent sur Moodle.

int pinLM35 = 26; // pins actionneur
int pinPhoto = 25;
short bargraph1 = 2; // pins bargraph
short bargraph2 = 34;
const String COURANTE = "1"; // codes de trames
const String SYNCHRO = "2";
const String RAPIDE = "3";
const String OBJ = "G02D"; // objet du nom de l'équipe
const String REQ_ECR = "1";
const String REQ_LEC = "1";

void setup() {
  pinMode(bargraph1, OUTPUT); // Mise en output des leds du bargraph
  pinMode(bargraph2, OUTPUT);

  Serial.begin(9600); // Démarrage moniteur série
  Serial1.begin(9600); // Démarrage Bluetooth
  Serial1.write("AT+NAMEG02D\n");
  Serial.println("***** DEMARRAGE DU SERVICE G02D *****");
}

void loop() {
  delay(5000);
  Serial.println("**** ENVOI DE LA TEMPERATURE ****");
  reqTempCour(); // Requête en écriture de la température vers la passerelle
  getAns(); // Attente de réponse de la passerelle
  delay(5000);
  Serial.println("**** ENVOI DE LA LUMINOSITE ****");
  reqLumCour(); // Requête en écriture de la luminosité vers la passerelle
  getAns();
}

String reqActionneur(){
  // En travaux
  String trame = COURANTE + OBJ + REQ_LEC + "a" + "01" + "ACTI" + "0125";
  String check = getCheckSum(trame);
  String trame_finale = trame + check;
  Serial.println(trame_finale);
  Serial1.println(trame_finale);
}

void reqTempCour(){
  // Envoi de trame température de la carte vers la passerelle.
  // | TRA | OBJ  | REQ | TYP | NUM | VAL       | TIM  | CHK         |
  // | 1   | G02D | 1   | 3   | 01  | getTemp() | 0125 | getCheckSum |
  String trame = COURANTE + OBJ + REQ_ECR + "3" + "01" + getTemp() + "0125";
  String check = getCheckSum(trame); // obtention du ckecksum
  String trame_finale = trame + check; // ajout du checksum dans la trame
  Serial1.println(trame_finale); // Envoi en Bluetooth
  light();
}

void reqLumCour(){
  // Envoi de trame luminosité de la carte vers la passerelle.
  // | TRA | OBJ  | REQ | TYP | NUM | VAL       | TIM  | CHK         |
  // | 1   | G02D | 1   | 5   | 01  | getLum()  | 0125 | getCheckSum |
  String trame = COURANTE + OBJ + REQ_ECR + "5" + "01" + getLum() + "0125";
  String check = getCheckSum(trame);
  String trame_finale = trame + check;
  Serial1.println(trame_finale);
  light();
}

void reqSynchro(){
  // En travaux
  String trame = SYNCHRO + "1";
  Serial1.println(trame);
  digitalWrite(bargraph1, HIGH);
  delay(100);
  digitalWrite(bargraph1, LOW);
}

String getTemp() {
  // Récupération de la température
  float temperature = map(analogRead(pinLM35), 0, 4095, 0, 3300); // on lit sur le pin analogique
  temperature = temperature/10; // valeur récupérée entre 0 et 4095 (12 bits), on la mappe entre 0 et 3300
  int temp = (int)temperature;
  Serial.println("TEMPERATURE ACTUELLE : " + String(temp) + "°C"); // Affichage sur moniteur série
  String temp2 = String(temp, HEX); // Conversion de in a String en hexa
  temp2 = hexToFour(temp2); // sur 4 caractères

  return temp2;
}

String getLum() {
  // Récupération de la luminosité
  float luminosite = analogRead(pinPhoto); // lecture sur le pin analogique
  int lum = (int)map(luminosite, 0, 4095, 0, 100); // mappage des valeurs
  Serial.println("LUMINOSITE ACTUELLE : " + String(lum) + " %"); // Affichage sur moniteur série
  String lum2 = String(lum, HEX); // int to String hexa
  lum2 = hexToFour(lum2); // sur 4 caractères

  return lum2;
}

void getAns(){
  // Lecture moniteur Bluetooth en attente d'une réponse
  String ans = "";
  int delai = 100;
  do{
    // Si la réponse lue vaut -1, délai incrémenté
    // Au bout de 5secs affichage erreur, connexion perdue avec passerelle
    ans = Serial1.readString();
    Serial.println("ANSWER = " + ans);
    delay(100);
    delai = delai + 100;
    Serial.println(delai);
      if(delai > 5000){
        Serial.println("ERREUR VEUILLEZ RECONNECTER LA CARTE");
      }
  }
  while(ans == "-1" or ans == "");
}

void getAnsActionneur(){
  // Lecture moniteur Bluetooth en attente d'une réponse pour activation actionneur
  String trame = Serial1.readString();
  Serial.println(trame);
  if(trame.substring(6,7).equals("a")){
    actionneur();
  }
}

String getCheckSum(String trame){
  // Fonction permettant d'obtenir le getCheckSum
  // On effectue la somme de tout les caractères en les convertissant en integer
  int i = 0;
  int chk = 0;
  for (i = 0; i < trame.length(); i = i + 1){
    chk = chk + (int)trame.charAt(i);
  }
  return String(chk % 256, HEX);
}

String hexToFour(String a){
  // Ajout de caractère "0" au début si champ inférieur à 4 caractères
  while(a.length() < 4){
    a = "0" + a;
  }
  return a;
}

void light(){
  // Lumière bargraph à chaque envoi de trame
  digitalWrite(bargraph1, HIGH);
  delay(100);
  digitalWrite(bargraph1, LOW);
}
