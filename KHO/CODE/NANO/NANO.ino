#include <DHT.h>         // thư viện dht
#include "DS1307.h"
#include "NFC.h"
#include "SV.h"

DHT dht22(A2, DHT22);
#define MQ2 analogRead(A0)
#define PIR analogRead(A1)
#define L 5
#define F 3
#define BUZZ 4
//unsigned long ms;
int chay;
int trom;
int tchay = 50;      // nhiệt độ ngưỡng báo cháy
int kchay = 300;     // nồng độ khói ngưỡng báo cháy
float h;   // biến lưu độ ẩm kk
float t;   // biến lưu nhiệt độ
int TDD;
int TDCC;
int TDCS;
int TDQ;
unsigned long CARD0  = 212600393;                 // thẻ chủ
unsigned long  CARD1 = 712057896;
unsigned long  CARD2  = 2577389914;         //  các thẻ khách
unsigned long  CARD3 = 3656236634;
unsigned long  CARD4  = 2310478435;
unsigned long svcard;
/////thêm thẻ...
int tbd = 7;            // giờ bắt đầu
int tkt = 18;           // giờ kết thúc
int t_chay;
int t_bchay = 35;       // nhiệt độ báo cháy
unsigned long tg1;
unsigned long tg2;
String U = "";
void setup() {
  Serial.begin(250000);
  dht22.begin();
  SETUP_NFC();
  SETUP_SV();
  Wire.begin();
  // setTime(22,57,30,3,3,5,2022);  // set time ds1307
  pinMode(L, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(BUZZ, OUTPUT);
}
void loop() {
//  Serial.println(millis() - tg2);
  DOWN();
  CARD();
  CONTROL();
  BAO_CHAY();
  BAO_TROM();
  UPP();
}
void CONTROL() {
  digitalWrite(L, TDD);
  digitalWrite(F, TDQ);
  if (TDCC == 1) {
    Servo1(30, 5);
  }
  else {
    Servo1(140, 5);

  }
  if (TDCS == 1) {

    Servo2(10, 5);
    //   Serial.println("Mở cửa sổ");
  }
  else {
    Servo2(110, 5);

    //    Serial.println("Đóng cửa sổ");
  }
  delay(200);
}
void DOWN() {
  while (Serial.available()) {
    String N = Serial.readStringUntil('\r');
    N.trim();
    //   Serial.println(N);
    if (N == "1S") {
      tg2 = millis();
      TDCS = 1;
    }
    if (N == "0S") {
      tg2 = millis();
      TDCS = 0;
    }
    if (N == "1D") {
      TDD = 1;
    }
    if (N == "0D") {
      TDD = 0;
    }
    if (N == "1Q") {
      TDQ = 1;
    }
    if (N == "0Q") {
      TDQ = 0;
    }
    //    Serial.print(TDCS);
    //    Serial.print("  ");
    //    Serial.print(TDD);
    //    Serial.print("  ");
    //    Serial.print(TDQ);
    //    Serial.println("  ");
  }

}
void UPP() {
  h = dht22.readHumidity();
  t = dht22.readTemperature();
  U = "";
  if (h < 10) {
    U += "0";
  }
  U += String(h);
  if (t < 10) {
    U += "0";
  }
  U += String(t);
  U += String(TDCC);
  U += String(TDCS);
  U += String(TDD);
  U += String(TDQ);
  U += String(chay);
  U += String(trom);
  if (millis() - tg1 > 2500) {
    Serial.println(U);
    tg1 = millis();
  }

}
void CARD() {
  int m = 0;
  if (!mfrc522.PICC_IsNewCardPresent()) {}
  if (  mfrc522.PICC_ReadCardSerial()) {
    unsigned long ms;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uidDecTemp = mfrc522.uid.uidByte[i];
      MASO = MASO * 256 + uidDecTemp;
      ms  = MASO;
    }
    mfrc522.PICC_HaltA();
    //    Serial.println(ms);
    READDS1307();
    if (TDCC == 0) {
      if (ms == CARD0) {
        TDCC = 1;
        svcard = ms;
        m = 1;
        //       Serial.println("mở cửa");
      }
      if (ms == CARD1 || ms == CARD2 || ms == CARD3 || ms == CARD4) {
        if (gio > tbd && gio < tkt ) {         // trong giờ
          TDCC = 1;
          svcard = ms;
          m = 1;
          //        Serial.println("mở cửa");
        }
      }
      //      Serial.println(TDCC);
      //      Serial.println(svcard);
    }
    if (TDCC == 1 && m == 0 && ms == svcard) {
      TDCC = 0;
      //      Serial.println("đóng cửa");
    }

  }
}

void BAO_TROM() {
  if (TDCC == 0 && millis() - tg2 > 5000 && PIR > 550 ) {
    delay(20);
    if (TDCC == 0 && PIR > 550 ) {
      trom = 1;
    }
  }
  if (trom == 1) {
    BUZZ1();
    //   Serial.println("có trộm");
  }
}
void BAO_CHAY() {
  if (dht22.readTemperature() > tchay || MQ2 > kchay) {
    chay = 1;
  }
  if (chay == 1) {
    BUZZ1();
    //  Serial.println("cháy");
  }
}

void BUZZ1() {
  if (millis() % 100 < 50) {
    digitalWrite(BUZZ, 1);
  }
  else digitalWrite(BUZZ, 0);
}
