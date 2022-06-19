
#include <DHT.h>
#include <SoftwareSerial.h>
#define den 4
#define bom 5
#define phun 6
SoftwareSerial lora(9, 10);
DHT dht(A3, DHT11);

#include "DS1307.h"

unsigned long tg;
unsigned long tg1;
unsigned long tg2;
unsigned long tg3;
unsigned long tg4;
unsigned long tg5;
unsigned long tg6;

String G = "1";
int GG[8];

int DAT_CHUAN = 0;
int KK_CHUAN = 0;
int TDL = 0;
int TDAD = 0;
int TDAK = 0;

void setup() {
  //setTime(20,38,30,3,13,4,2021);
  Wire.begin();
  Serial.begin(250000);
  lora.begin(9600);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(den, OUTPUT);
  pinMode(bom, OUTPUT);
  pinMode(phun, OUTPUT);
  digitalWrite(11, 0);
  digitalWrite(12, 0);

  dht.begin();
  tg1 = millis();
  tg2 = millis();
  tg3 = millis();
  tg4 = millis();
  tg5 = millis();
  tg6 = millis();
  lora.setTimeout(100);

}

void loop() {
  tg = millis();
   READDS1307();
  BOM();
  PHUN();
  DEN();
  TACH();

}

void TACH() {
  String N = "";
  if (lora.available()) {
    Serial.println("cos dl");
    N = lora.readStringUntil(',');
    N.trim();
   // Serial.println(N);
    if (N.substring(0, 1) == "1") {
      GUI();
      DAT_CHUAN = N.substring(1, 4).toInt();
      
      KK_CHUAN = N.substring(4, 7).toInt();
  ///  Serial.println(DAT_CHUAN);
   // Serial.println(KK_CHUAN);
    }
    if (N == "A" ){
      if(TDL==0){
        digitalWrite(den,1);
        tg1=millis();
        TDL=1; //Serial.println("Denbat");
        }
      else{
        digitalWrite(den,0);
        TDL=0; //Serial.println("Dentat");
        }
        lora.flush();
    }
    if (N == "B" ){
      if(TDAD==0){
        digitalWrite(bom,1);
        tg2=millis();
        TDAD=1;//// Serial.println("Bombat");
        }
      else{
        digitalWrite(bom,0);
        TDAD=0;// Serial.println("Bomtat");
        }
         lora.flush();
    }
    if (N == "C" ){
      if(TDAK==0){
        digitalWrite(phun,1);
        tg3=millis();
        TDAK=1;// Serial.println("Phunbat");
        }
      else{
        digitalWrite(phun,0);
        TDAK=0; //Serial.println("Phuntat");
        }
         lora.flush();
    }
      
  }
}


void GUI() {
  GG[1] = digitalRead(den);
  GG[2] = digitalRead(bom);
  GG[3] = digitalRead(phun);
  GG[4] = DAT();
  GG[5] = KK();
  G = "1";
  G += String(GG[1]);
  G += String(GG[2]);
  G += String(GG[3]);
  if (GG[4] < 100) {
    G += "0";
  }
  if (GG[4] < 10) {
    G += "0";
  }
  G += String(GG[4]);
  if (GG[5] < 100) {
    G += "0";
  }
  if (GG[5] < 10) {
    G += "0";
  }
  G += String(GG[5]);
  G+= ",";
  lora.println(G);
  //Serial.println(G);
}
void DEN() { 
   
  if (gio>6 && gio<18 && LIGHT() == 0 && TDL == 0) {
    digitalWrite(den, 1);
  }
  if (gio>6 && gio<18 && LIGHT() == 1 && TDL == 0) {
    digitalWrite(den, 0);
  }
  if (gio<6 && gio > 18 && LIGHT() == 0 && TDL == 0) {
    digitalWrite(den, 0);
  }
  
  if (tg - tg1 > 15000 && TDL == 1) {
    digitalWrite(den, 0);
    TDL = 0;
  }
}
void BOM() {
  if (DAT() < DAT_CHUAN && TDAD == 0) {
    digitalWrite(bom, 1);
  }
  if (DAT() > DAT_CHUAN && TDAD == 0) {
    digitalWrite(bom, 0);
  }
  if (tg - tg2 > 15000 && TDAD == 1) {
    digitalWrite(bom, 0);
    TDAD = 0;
  }
}
void PHUN() {
  if (KK() < KK_CHUAN && TDAK == 0) {
    digitalWrite(phun, 1);
  }
  if (KK() > KK_CHUAN && TDAK == 0) {
    digitalWrite(phun, 0);
  }
  if (tg - tg3 > 15000 && TDAK == 1) {
    digitalWrite(phun, 0);
    TDAK = 0;
  }
}

int DAT() {
  int a = (1023 - analogRead(A2)) / 10;
  if (a > 100) {
    a = 100;
  }
  return a;
}
int KK() {
  float a = dht.readHumidity();
  return a;
}
int LIGHT() {
  int b = analogRead(A6);
  if (b < 100) {
    return 0;
  }
  else {
    return 1;
  }
}
