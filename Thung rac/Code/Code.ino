#include<Servo.h>
#include <SoftwareSerial.h> // thư viện kết nối sim và bộ âm thanh
#include "Arduino.h"        // thư viện arduino 
#include "DFRobotDFPlayerMini.h"  // thư viện bộ lưu giọng nói
SoftwareSerial mySoftwareSerial(A1, A0); // RX, TX   // Khai báo chân bộ lưu giọng nói
DFRobotDFPlayerMini myDFPlayer;                     // khai báo tên bộ lưu giọng nói
void printDetail(uint8_t type, int value);
Servo SV1;
Servo SV2;
Servo SV3;
Servo SV4;
int S1 = 120;
int S2 = 90;
int S4 = 50;
#define CBL 1 - digitalRead(7)
#define CBR 1 - digitalRead(8)
#define CBV 1 - digitalRead(9)
#define DC 10
#define VAN 11
#define BOM 12

int conguoi = 0;
int quytrinh = 0;
int dayrac = 0;
unsigned long tg;
unsigned long tg0;
unsigned long tg1;
unsigned long tg2;
unsigned long tg3;
unsigned long tg4;

void setup() {
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);   // cấu hình bộ giọng nói
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(25);  //Set volume value .

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  SV1.attach(2);
  SV2.attach(3);
  SV3.attach(4);
  SV4.attach(5);
  SV1.write(120);
  SV2.write(17);
  SV3.write(50);
  SV4.write(50);

}
void loop() {
  RUN();
  VOUCHER();

}
void RUN() {
  if (CBL == 1 || CBR == 1) {
    if (millis() - tg0 > 1000) {
    if (CBL == 1 || CBR == 1) {
      conguoi = 1;
      tg1 = millis();
    }
  }
  }
  if (CBL == 0 && CBR == 0) {
    conguoi = 0;
    tg0 = millis();
  }
  if (conguoi == 1 && quytrinh == 0) {
    tg = millis();
    myDFPlayer.play(1);  
    digitalWrite(DC, 0);
    NAP(128, 5);
    quytrinh = 1;
  }
  if (millis() - tg > 7000) {
    if (conguoi == 0 && quytrinh == 1) {
      myDFPlayer.play(2);  
      NAP(50, 20);
      tg1 = millis();
      quytrinh = 0;
      digitalWrite(DC, 1);
    }
  }
  if (millis() - tg1 > 5000) {
    digitalWrite(DC, 0);
  }
}
void VOUCHER() {
  if (CBV == 1) {
    tg3 = millis();
  }
  if (CBV == 0) {
    tg4 = millis();
  }
  if (millis() - tg4 > 1000 && dayrac == 0) {
    myDFPlayer.play(3);
    HUT();
    dayrac = 1;
  }
  if (millis() - tg3 > 10000 && dayrac == 1) {
    dayrac = 0;
  }
}
