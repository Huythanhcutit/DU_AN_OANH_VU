#include<LiquidCrystal.h>
#include<EEPROM.h>
#include"DS1307.h"
LiquidCrystal lcd (8, 7, 3, 4, 5, 6); // rs,e,d0,d1,d2,d3

#define NUT1 digitalRead(12)
#define NUT2 digitalRead(11)
#define NUT3 digitalRead(10)
#define LDR1 analogRead(A0)
#define LDR2 analogRead(A1)
#define LDR3 analogRead(A2)
#define LDR4 analogRead(A3)
#define LDR5 analogRead(A6)
#define PIR  analogRead(A7)
#define DEN 9

int hbd = 6;
int hkt = 18;
unsigned long tg1;
unsigned long tg2;
unsigned long tgkhongnguoi =60000;
unsigned long tgthucong=60000;
int DK = 0;
int p = 0;
int go = 0;

int   SET = 400;

int e;
int pre_e;
float tichphan;
float viphan;
float out = 0;
float Kp = 0;
float Ki = 0.01;
float Kd = 0;

void setup() {
  Serial.begin(250000);
  Wire.begin();
  lcd.begin(16, 2);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(9, OUTPUT);

//  setTime(9, 47, 00, 4, 3, 11, 2021);

}
void loop() {
//  READDS1307();
  LCD();
  //  Serial.print(gio);
  //  Serial.print("   ");
  //  Serial.print(PIR1());
  //  Serial.print("   ");
  //  Serial.print(go);
  //  Serial.print("   ");
  ////  Serial.print(out);
  ////  Serial.print("   ");
  //
  //  Serial.print(MCH());
  //  Serial.print("   ");
//  SETUP();
//  DIEUKHIEN();
//  RUN();
}

void RUN() {
    if (gio > hbd && gio < hkt ) {
    if (PIR1() == 1) {
      tg2 = millis();
      Serial.println("co nguoi");
    }
    if (millis() - tg2 < tgkhongnguoi) {
      if (MCH() == 0) {
        PID(SET);
        Serial.println(LUX());
      }
      else {
        PID(180);
      }
    }
    else {
      digitalWrite(DEN, 0);
    }
  }
  else{
  if (DK == 1) {
    Serial.println("Bat thu cong");
    if (MCH() == 1) {
      PID(180);
    }
    else {
      PID(SET);
    }
  }
  if (DK == 0) {
      digitalWrite(DEN, 0);
  }
  }
}
void DIEUKHIEN() {
  if (NUT3 == 0) {
    delay(10);
    if (DK == 0) {
      DK = 1;
      tg1 = millis();
    }
    else {
      DK = 0;
    }
    while (NUT3 == 0) {}
  }
  if (millis() - tg1 > tgthucong) {
    DK = 0;
  }
}
void SETUP() {
  SET = CAITHONGSO(SET, 0, 600);
}
void PID(int st) {
  /*
    e = st - LUX();
    tichphan += e * 0.1;
    out = Kp * e + Ki * tichphan + Kd * viphan;
  */
  if (st > LUX()) {
    out += 0.2;
  }
  else {
    out -= 0.2;
  }
  if (out > 255) {
    out = 255;
  }
  if (out < 0) {
    out = 0;
  }
  int PWM = (int)out;
  
  analogWrite(DEN, PWM);
}
int CAITHONGSO(int bien, int duoi, int tren) {
  if (NUT2 == 0) {
    delay(10);
    if (NUT2 == 0) {
      bien += 50;
      if (bien > tren) {
        bien  = duoi;
      }
      delay(10);
      while (NUT2 == 0) {}
    }
  }
  if (NUT1 == 0) {
    delay(10);
    if (NUT1 == 0) {
      bien -= 50;
      if (bien < duoi) {
        bien = tren;
      }
      delay(10);
      while (NUT1 == 0) {}
    }
  }
  return bien;
}
void LCD() {
  lcd.setCursor(0, 0); lcd.print("Time: 06h - 18h");
  lcd.setCursor(3, 1); lcd.print("LUX");
  lcd.setCursor(0, 1);
  if (SET < 100) {
    lcd.print(" ");
  }
  if (SET < 10) {
    lcd.print(" ");
  }
  lcd.print(SET);
  lcd.setCursor(10, 1);
  if (DK == 1) {
    lcd.print("Manual");
  }
  else {
    lcd.print("Auto  ");
  }
}
int LUX() {
  float a = (LDR1 + LDR2 + LDR3 + LDR4) / 4;
  int b = (500000 * 9 * a) / (22506000 - 22000 * a) ;
  return b;
}
int MCH() {
  if (LDR5 > 800) {
    return 1;
  }
  else {
    return 0;
  }
}
int PIR1() {
  if (PIR < 400) {
    return 0;
  }
  else {
    return 1;
  }
}
