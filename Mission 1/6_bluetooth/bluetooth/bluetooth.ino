//TXD -> PB_0
//RXD -> PB_1

short pinPot = 28;
unsigned int valuePot = 0;
float voltage = 0;

void setup() {
  Serial1.begin(9600);
  Serial1.write("AT+NAMEmichel");
  Serial1.read();
  //Serial1.write("Je m'appelle HC06"); 
}

void loop() {
    valuePot = analogRead(pinPot);
    voltage = valuePot * (3.3/4096);

    int inByte = Serial1.read();
    Serial1.write("Val pot :"); 
    Serial1.print(valuePot); 
    Serial1.write("\n"); 
    Serial1.write("Voltage :"); 
    Serial1.print(voltage); 
    delay(100);
}
