//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "casa-automatica-86bff.firebaseio.com"
#define FIREBASE_AUTH "nULru985ChWogscC8nnBfl8QLMO3Yw9nWNS8oCyZ"
#define WIFI_SSID "Casa 1301"
#define WIFI_PASSWORD "28050213020"


int quarto = D7;
int sala = D6;
int banheiro = D5;
int cozinha = D4;

void ligarLed(int led) {
  digitalWrite(led , HIGH);
}

void desligarLed(int led){
  digitalWrite(led, LOW);
}

void setup() {

  Serial.begin(9600);

  pinMode(quarto,OUTPUT);
  pinMode(sala, OUTPUT);
  pinMode(cozinha, OUTPUT);
  pinMode(banheiro, OUTPUT);
  
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

  //Quarto
  String quartoLed = Firebase.getString("quartoLed");
  if(quartoLed == "ligada") {
    Serial.println("ligar luz do quarto " + quartoLed);
    ligarLed(quarto);
  }
  else {
    Serial.println("desligar luz do quarto " + quartoLed);
    desligarLed(quarto);
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
  delay(500);
}
