#include <TimerOne.h>
#include <OneWire.h>
#include <DS18B20.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);
#define ONE_WIRE_BUS A0
#define nut_den digitalRead(2)
#define nut_bom digitalRead(3)
#define bom A3
#define den A2
int G[5];
String U = "";
unsigned long tg1;
int DOAM_CHUAN;
int TDB = 0;
int TDD = 0;
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);
void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(bom, OUTPUT);
  pinMode(den, OUTPUT);
  tg1 = millis();
  sensor.begin();
  Timer1.initialize(100000);
  Timer1.attachInterrupt(NUT);
}
void loop() {
  LCD();
  NHAN_DL();
  BOM();
}
void NHAN_DL() {
  if (Serial.available()) {
    String N = "";
    N = Serial.readStringUntil('\r');
    N.trim();
    if (N.substring(0, 1) == "0") {
      UP_DL();
      DOAM_CHUAN = N.substring(1, 4).toInt();
      Serial.flush();
    }
    if (N == "B") {
      if (TDB == 0) {
        digitalWrite(bom, 1);
        tg1 = millis();
        TDB = 1;
      }
      else {
        digitalWrite(bom, 0);
        TDB = 0;
      }
      Serial.flush();
    }
    if (N == "D") {
      if (TDD == 0) {
        digitalWrite(den, 1);
        TDD = 1;
      }
      else {
        digitalWrite(den, 0);
        TDD = 0;
      }
      Serial.flush();
    }
  }
}
void UP_DL() {
  G[0] = digitalRead(bom);
  G[1] = digitalRead(den);
  G[2] = NHIETDO();
  G[3] = DOAM();

  U = "";
  U += String(G[0]);
  U += String(G[1]);
  if (G[2] < 100) {
    U += "0";
  }
  if (G[2] < 10) {
    U += "0";
  }
  U += String(G[2]);
  if (G[3] < 100) {
    U += "0";
  }
  if (G[3] < 10) {
    U += "0";
  }
  U += String(G[3]);
  Serial.println(U);
}
void BOM() {
  if (DOAM_CHUAN > DOAM() && TDB == 0) {
    digitalWrite(bom, 1);
  }
  if (DOAM_CHUAN <= DOAM() && TDB == 0) {
    digitalWrite(bom, 0);
  }
  if (millis() - tg1 > 15000 && TDB == 1) {
    digitalWrite(bom, 0);
    TDB = 0;
  }
}
void LCD() {
  lcd.setCursor(0, 0); lcd.print("BOM:");
  lcd.setCursor(0, 1); lcd.print("DEN:");
  lcd.setCursor(8, 0); lcd.print("t*:");
  lcd.setCursor(8, 1); lcd.print("DA:");
  lcd.setCursor(14, 0); lcd.print("*C");
  lcd.setCursor(14, 1); lcd.print("%");

  lcd.setCursor(4, 0);
  if (digitalRead(bom) == 1) {
    lcd.print("BAT");
  }
  if (digitalRead(bom) == 0) {
    lcd.print("TAT");
  }
  lcd.setCursor(4, 1);
  if (digitalRead(den) == 1) {
    lcd.print("BAT");
  }
  if (digitalRead(den) == 0) {
    lcd.print("TAT");
  }
  lcd.setCursor(11, 0);
  if (NHIETDO() < 10) {
    lcd.print(" ");
  }
  if (NHIETDO() < 100) {
    lcd.print(" ");
  }
  lcd.print(NHIETDO());
  lcd.setCursor(11, 1);
  if (DOAM() < 10) {
    lcd.print(" ");
  }
  if (DOAM() < 100) {
    lcd.print(" ");
  }
  lcd.print(DOAM());
}
void NUT() {
  if (TDB == 0) {
    if (nut_bom == 0) {
      digitalWrite(den, 1);
      TDB = 1;
    }
  }
  else {
    if (nut_bom == 0) {
      digitalWrite(den, 0);
      TDB = 0;
    }
  }
  if (TDD == 0) {
    if (nut_den == 0) {
      digitalWrite(den, 1);
      TDD = 1;
    }
  }
  else {
    if (nut_den == 0) {
      digitalWrite(den, 0);
      TDD = 0;
    }
  }
}
int NHIETDO() {
  sensor.requestTemperatures();
  while (!sensor.isConversionComplete());
  return (int)sensor.getTempC();
}
int DOAM() {
  int a = (1023 - analogRead(A1)) / 10;
  if (a > 100) {
    a = 100;
  }
  return a;
}
