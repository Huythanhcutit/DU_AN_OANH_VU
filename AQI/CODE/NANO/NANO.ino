#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
SoftwareSerial node(3, 2);
int lastpwm, pwm;
int gs;
float e = 2.71828;    // hằng số logarit
unsigned long th, tl, h, l, ppm;
unsigned long tg1;
unsigned long tg2;
unsigned long tg3;

float b;
int t;
int c;
float a1, a2, a3;
int a;
int R[6];
String U = "";
void setup() {
  Serial.begin(115200);
  node.begin(115200);
  lcd.begin(16, 2);
  pinMode(A2, OUTPUT);
}
void loop() {
  //Serial.println(a1);
  CO2();
  NHIETDO();
  GAS();
  CO();
  BUI();
  AQI();
  LCD1();
  UP();

}
void UP() {
  R[0] = ppm;
  R[1] = gs;
  R[2] = c;
  R[3] = b;
  R[4] = t;
  R[6] = a;
  U = "";
  if (ppm < 10) {
    U += "0";
  }
  if (ppm < 100) {
    U += "0";
  }
  if (ppm < 1000) {
    U += "0";
  }
  U += String(ppm);
  if (gs < 10) {
    U += "0";
  }
  if (gs < 100) {
    U += "0";
  }
  if (gs < 1000) {
    U += "0";
  }
  U += String(gs);
  if (c < 10) {
    U += "0";
  }
  if (c < 100) {
    U += "0";
  }
  if (c < 1000) {
    U += "0";
  }
  U += String(c);
  U += String(b);
  if (t < 100) {
    U += "0";
  }
  U += String(t);
  if (a < 10) {
    U += "0";
  }
  if (a < 100) {
    U += "0";
  }
  if (a < 1000) {
    U += "0";
  }
  U += String(a);
  if (millis() - tg2 > 2000) {
    node.println(U);
    Serial.println(U);
    tg2 = millis();
  }
}
void AQI() {
  a1 = (ppm / 410.0) * 100;
  a2 = (gs / 34.0) * 100;
  a3 = (c / 38.0) * 100;
  if (a1 > a2 && a1 > a3) {
    a = a1;
  }
  if (a2 > a1 && a2 > a3) {
    a = a2;
  }
  if (a3 > a1 && a3 > a2) {
    a = a3;
  }
}
void LCD1() {
  lcd.setCursor(0, 0);
  if (ppm < 10) {
    lcd.print(" ");
  }
  if (ppm < 100) {
    lcd.print(" ");
  }
  if (ppm < 1000) {
    lcd.print(" ");
  }
  lcd.print(ppm);
  lcd.setCursor(5, 0);
  if (gs < 10) {
    lcd.print(" ");
  }
  if (gs < 100) {
    lcd.print(" ");
  }
  if (gs < 1000) {
    lcd.print(" ");
  }
  lcd.print(gs);
  lcd.setCursor(10, 0);
  if (c < 10) {
    lcd.print(" ");
  }
  if (c < 100) {
    lcd.print(" ");
  }
  if (c < 1000) {
    lcd.print(" ");
  }
  lcd.print(c);
  lcd.setCursor(0, 1);
  if (b < 10) {
    lcd.print(" ");
  }
  if (b < 100) {
    lcd.print(" ");
  }
  if (b < 1000) {
    lcd.print(" ");
  }
  lcd.print(b);
  lcd.setCursor(9, 1);
  if (t < 10) {
    lcd.print(" ");
  }
  if (t < 100) {
    lcd.print(" ");
  }

  lcd.print(t);
}
void CO() {
  float v = analogRead(A5);
  float Vcb = 5 * v / 1023;
  c = 3.027 * pow(e, 1.0698 * Vcb);
}
void BUI() {
  if (millis() - tg3 > 500) {
    digitalWrite(A2, 0);
    delayMicroseconds(280);
    float val = analogRead(A3);
    delayMicroseconds(40);
    digitalWrite(A2, 1);
    delayMicroseconds(9680);
    b = 0.17 * val * (5.0 / 1024) - 0.1;
    tg3 = millis();
  }
}
void GAS() {
  float v = analogRead(A6);
  float Vcb = 5 * v / 1023;
  gs = 26.572 * pow(e, 1.2894 * Vcb);
}
void NHIETDO() {
  t = (analogRead(A7) * 5.0) / 1023  * 100;    // đọc nhiệt độ từ cảm biến nhiệt độ lm35
}
void CO2() {
  tg1 = millis();
  pwm = digitalRead(A4);
  if (pwm == HIGH) {
    if (pwm != lastpwm) {
      h = tg1;
      tl = h - l;
      lastpwm = pwm;
    }
  }  else {
    if (pwm != lastpwm) {
      l = tg1;
      th = l - h;
      lastpwm = pwm;
      ppm = 5000 * (th - 2) / (th + tl - 4);
    }
  }
}
