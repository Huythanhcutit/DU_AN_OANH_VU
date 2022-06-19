#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <Q2HX711.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7); //RS,E,D4,D5,D6,D7

const byte hx711_data_pin = 3;
const byte hx711_clock_pin = 2;
Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);

#define hn A7
#define xl_day A1
#define xl_ploai1 A0
#define xl_ploai2 A2
#define  bang A3
int l1 = 0;
int l2 = 0;
int loi = 0;
String G = "";
int s = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  //Timer1.initialize(50000);
  //Timer1.attachInterrupt(NGAT);

  while (digitalRead(4) == 1){can();}
}
void loop() {
  Serial.println("s: ");
  Serial.println(s);
  // NGAT();
  PHANLOAI();
  LCD();
}
void LCD() {
  lcd.setCursor(1, 0); lcd.print("SPL1");
  lcd.setCursor(6 , 0); lcd.print("SPL2");
  lcd.setCursor(11, 0); lcd.print("SPLOI");
  lcd.setCursor(2, 1);
  if (l1 < 10) {
    lcd.print(" ");
  }
  lcd.print(l1);
  lcd.setCursor(7, 1);
  if (l2 < 10) {
    lcd.print(" ");
  }
  lcd.print(l2);
  lcd.setCursor(12, 1);
  if (loi < 10) {
    lcd.print(" ");
  }
  lcd.print(loi);
}
void PHANLOAI() {
    digitalWrite(xl_day, 1);
    digitalWrite(bang, 1);

  while (analogRead(hn) > 400) {
    if (s == 0) {
      digitalWrite(bang, 1);
    }
    else {
      digitalWrite(bang, 0);
    }
  }
  digitalWrite(bang, 0);
  digitalWrite(xl_day, 0);
  delay(500);
  int a = can();
  if (a == 1) {
    digitalWrite(xl_ploai1, 1);
    delay(2000);
    digitalWrite(xl_ploai1, 0);
    a = 0;
    l1++;
  }
  if (a == 2) {
    digitalWrite(xl_ploai2, 1);
    delay(2000);
    digitalWrite(xl_ploai2, 0);
    a = 0;
    l2++;
  }
  if (a == 3) {

    a = 0;
    loi++;

    digitalWrite(bang, 1);
    while (analogRead(hn) < 400) {}
  }

  G = "";
  if (l1 < 10) {
    G += "0";
  }
  G += String(l1);
  if (l2 < 10) {
    G += "0";
  }
  G += String(l2);
  if (loi < 10) {
    G += "0";
  }
  G += String(loi);
  Serial.println(G);
}


void NGAT() {
  while (s == 1) {
    if (Serial.available()) {
      char data = Serial.read();
      if (data == 'A') {
        s = 0;
        digitalWrite(bang, 1);
      }
    }
    if (digitalRead(4) == 0) {
      s = 0;
      digitalWrite(bang, 1);
    }
  }
  if (s == 0) {
    if (Serial.available()) {
      char data = Serial.read();
      if (data == 'B') {
        s = 1;
        digitalWrite(bang, 0);
      }
    }
    if (digitalRead(5) == 0) {
      s = 1;
      digitalWrite(bang, 0);
    }
  }
}

int can() {
  unsigned long tong=0;
  int dem=0;
  while(dem<10){
  tong += (hx711.read() / 1000);
  dem++;
  }
  unsigned long a = tong/10 -8300;
  Serial.println(a);
  if (a > 70) {
    a = 1;
  }
  else if (a < 70 && a > 40) {
    a = 2;
  }
  else {
    a = 3;
  }
  return a;
}
