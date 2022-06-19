#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define phun 8
#define bom 7
#define dca 5
#define dcb 6
#define dht11 A0
#define dat A1
#define mua A2
#define nang A3
DHT dht(dht11, DHT11);

unsigned long tg;
unsigned long tg1;
unsigned long tg2;
String G = "";

int S[10];
int NHIETDO_CHUAN = 0;
int DAT_CHUAN = 0;
int TDB = 0;
int TDP = 0;

void setup() {
  Serial.begin(115200);
  tg1 = millis();
  tg2 = millis();
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  // lcd.noBacklight();
  pinMode(dca, OUTPUT);
  pinMode(dcb, OUTPUT);
  pinMode(bom, OUTPUT);
  pinMode(phun, OUTPUT);
  digitalWrite(dca, 0);
  digitalWrite(dcb, 1);
  LCD();
}
void loop() {
  tg = millis();
  BOM();
  PHUN();
  KEOLUOI();
  LCD1();
  DOWN_DL();
 // Serial.println(millis() - tg);
}
void DOWN_DL() {
  if (Serial.available()) {
    String N = "";
    N = Serial.readStringUntil('\r');
    N.trim();
    if (N.substring(0, 1) == "0") {
      //  Serial.println("gui");
      UP_DL();
      NHIETDO_CHUAN = N.substring(1, 4).toInt();
      DAT_CHUAN = N.substring(4, 7).toInt();
    }
    if (N == "B" ) {
      if (TDB == 0) {
        digitalWrite(bom, 1);
        tg1 = millis();
        TDB = 1;// Serial.println("Bombat");
      }
      else {
        digitalWrite(bom, 0);
        TDB = 0; //Serial.println("Bomtat");
      }
   //   Serial.flush();
    }
    if (N == "P" ) {
      if (TDP == 0) {
        digitalWrite(phun, 1);
        tg2 = millis();
        TDP = 1;// Serial.println("Phunbat");
      }
      else {
        digitalWrite(phun, 0);
        TDP = 0;// Serial.println("Phuntat");
      }
    //  Serial.flush();
    }
  }
}
void UP_DL() {
  S[0] = digitalRead(bom);
  S[1] = digitalRead(phun);
  S[2] = MUA();
  S[3] = NANG();
  S[4] = NHIETDO();
  S[5] = KK();
  S[6] = DAT();

  G = "";
  G += String(S[0]);
  G += String(S[1]);

  G += String(S[2]);
  G += String(S[3]);
  if (S[4] < 100) {
    G += "0";
  }
  if (S[4] < 10) {
    G += "0";
  }
  G += String(S[4]);

  if (S[5] < 100) {
    G += "0";
  }
  if (S[5] < 10) {
    G += "0";
  }
  G += String(S[5]);
  if (S[6] < 100) {
    G += "0";
  }
  if (S[6] < 10) {
    G += "0";
  }
  G += String(S[6]);
  Serial.println(G);
}
void BOM() {
  if (MUA() == 1 && TDB == 0) {
    digitalWrite(bom, 0);
    // Serial.println("Bomtat");
  }
  if (MUA() == 0 && TDB == 0 && DAT() < DAT_CHUAN ) {
    digitalWrite(bom, 1);
  }
  if (MUA() == 0 && TDB == 0 && DAT() > DAT_CHUAN) {
    // Serial.println("Bomtat1");
    digitalWrite(bom, 0);
  }
  if (tg - tg1 > 15000 && TDB == 1) {
    digitalWrite(bom, 0);
    TDB = 0;
  }
}
void PHUN() {
  if (NHIETDO() < NHIETDO_CHUAN && TDP == 0) {
    digitalWrite(phun, 0);
    //Serial.println("Phuntat");
  }
  if (NHIETDO() > NHIETDO_CHUAN && TDP == 0) {
    digitalWrite(phun, 1);
  }
  if (tg - tg2 > 15000 && TDP == 1) {
    digitalWrite(phun, 0);
    TDP = 0;
  }
}
void KEOLUOI() {
  if (NANG() == 1) {
    digitalWrite(dca, 1);
    digitalWrite(dcb, 0);
  }
  if (NANG() == 0) {
    digitalWrite(dca, 0);
    digitalWrite(dcb, 1);
  }
}
void LCD() {
  lcd.setCursor(0, 0); lcd.print("BOM");
  lcd.setCursor(0, 1); lcd.print("PS");
  lcd.setCursor(0, 2); lcd.print("MUA");
  lcd.setCursor(0, 3); lcd.print("NANG");
  lcd.setCursor(11, 1); lcd.print("t*");
  lcd.setCursor(11, 2); lcd.print("KK");
  lcd.setCursor(11, 3); lcd.print("DAT");
  lcd.setCursor(4, 0); lcd.print(":");
  lcd.setCursor(4, 1); lcd.print(":");
  lcd.setCursor(4, 2); lcd.print(":");
  lcd.setCursor(4, 3); lcd.print(":");
  lcd.setCursor(14, 1); lcd.print(":");
  lcd.setCursor(14, 2); lcd.print(":");
  lcd.setCursor(14, 3); lcd.print(":");
}
void LCD1(){
  lcd.setCursor(5, 0);
  if (digitalRead(bom) == 1) {
    lcd.print("BAT");
  }
  if (digitalRead(bom) == 0) {
    lcd.print("TAT");
  }
  lcd.setCursor(5, 1);
  if (digitalRead(phun) == 1) {
    lcd.print("BAT");
  }
  if (digitalRead(phun) == 0) {
    lcd.print("TAT");
  }
  lcd.setCursor(5, 2);
  if (MUA() == 1) {
    lcd.print("Co   ");
  }
  if (MUA() == 0) {
    lcd.print("Khong");
  }
  lcd.setCursor(5, 3);
  if (NANG() == 1) {
    lcd.print("Co   ");
  }
  if (NANG() == 0) {
    lcd.print("Khong");
  }

  lcd.setCursor(15, 1);

  if (NHIETDO() < 10) {
    lcd.print(" ");
  }
  if (NHIETDO() < 100) {
    lcd.print(" ");
  }
  lcd.print(NHIETDO());
  lcd.setCursor(18, 1);
  lcd.print("*C");
  lcd.setCursor(15, 2);

  if (KK() < 10) {
    lcd.print(" ");
  }
  if (KK() < 100) {
    lcd.print(" ");
  }
  lcd.print(KK());
  lcd.setCursor(18, 2);
  lcd.print("%");

  lcd.setCursor(15, 3);
  if (DAT() < 10) {
    lcd.print(" ");
  }
  if (DAT() < 100) {
    lcd.print(" ");
  }
  lcd.print(DAT());
  lcd.setCursor(18, 3);
  lcd.print("%");
}
int NHIETDO() {
  int t = dht.readTemperature();
  return t;
}
int KK() {
  int a = dht.readHumidity();
  return a;
}
int DAT() {
  int a = (1023 - analogRead(dat)) / 10;
  if (a > 100) {
    a = 100;
  }
  return a;
}

int NANG() {
  int b = analogRead(nang);
  if (b > 40) {
    b = 0;
  }
  else {
    b = 1;
  }
  return b;
}
int MUA() {
  int c = analogRead(mua);
  if (c < 500) {
    c = 1;
  }
  else {
    c = 0;
  }
  return c;
}
