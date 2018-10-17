#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "casa-automatica-86bff.firebaseio.com"
#define FIREBASE_AUTH "nULru985ChWogscC8nnBfl8QLMO3Yw9nWNS8oCyZ"
#define WIFI_SSID "AndroidAP"
#define WIFI_PASSWORD "bmzv6725"

float temp= 0;
int analog=0;
int sala = D4;
int cozinha = D6;
int banheiro = D2;
int gas = D5;

void ligarLed(int led) {
  digitalWrite(led , HIGH);
}

void desligarLed(int led){
  digitalWrite(led, LOW);
}

void setup() {

  Serial.begin(9600);

  pinMode(banheiro, OUTPUT);
  pinMode(sala, OUTPUT);
  pinMode(cozinha, OUTPUT);
  pinMode(gas, INPUT);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

  //temperatura

  analog=analogRead(17);
  float temp= 0.322*analog;
  Firebase.setFloat("Temperatura", temp);
  Serial.print("Temeperature:");
  Serial.println(temp);
  
  //Gas
  
   int valDigital = digitalRead(gas);
   if(valDigital == 0) {
    Serial.println("Gas detectado");
    Firebase.setString("gas", "Gás detectado");
   }
   else {
    Serial.println("Sem gas");
    Firebase.setString("gas", "Sem gás");
   }
  
  //Sala 
  
  String salaLed = Firebase.getString("salaLed");
  if(salaLed == "ligada") {
    Serial.println("ligar luz da sala: " + salaLed);
    ligarLed(sala);
  }
  else {
    Serial.println("desligar luz da sala " + salaLed);
    desligarLed(sala);
  }

  //Cozinha
  
  String cozinhaLed = Firebase.getString("cozinhaLed");
  if(cozinhaLed == "ligada") {
    Serial.println("ligar luz da cozinha " + cozinhaLed);
    ligarLed(cozinha);
  }
  else {
    Serial.println("desligar luz da cozinha " + cozinhaLed);
    desligarLed(cozinha);
  }

  //Banheiro
  String banheiroLed = Firebase.getString("banheiroLed");
  if(banheiroLed == "ligada") {
    Serial.println("ligar luz do banheiro " + banheiroLed);
    ligarLed(banheiro);
  }
  else {
    Serial.println("desligar luz do banheiro " + banheiroLed);
    desligarLed(banheiro);
  }
}
