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
#define CB_PIR  analogRead(A7)
#define DEN 9
unsigned long tg1;
unsigned long tg2;
int e;
int pre_e;
float tichphan;
float viphan;
float out;
int mode = 0;
int set_L = 0;
int SET = EEPROM.read(0);


void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  Serial.begin(9600);
  setTime(21, 31, 30, 4, 20, 10, 2021);

}

void loop() {
  READDS1307();
  LCD();
  if (gio >BEGIN_HR && gio< END_HR && PIR()==1 && MCH()==0) {
    PID(0.1,0.2);
  }
  else {
    digitalWrite(DEN, 0);
  }
}
int PIR() {    // cb chuyen dong
  if (CB_PIR > 1000) {
    return 1;
  }
  else {
    return 0;
  }
}
int AS() {             // anh sang
  int a = (LDR1 + LDR2 + LDR3 + LDR4) / 4;
  return a;
}
int MCH() {           // may chieu
  if (LDR5 > 500) {
    return 1;
  }
  else {
    return 0;
  }
}
void PID(float Kp, float Ki) {
  pre_e = e;
  e = SET - AS();
  //  out += e * K;

 // viphan = (e - pre_e) / 0.1;
  tichphan += e * 0.1;
  out = Kp * e + Ki * tichphan;

  int PWM = (int)out;
  if (PWM > 255) {
    PWM = 255;
  }
  if (PWM < 0) {
    PWM = 0;
  }
  analogWrite(DEN, PWM);
  Serial.println(AS());
}
void CAIDAT() {
  if (NUT1 == 0) {
    mode++; delay(10);
    while (NUT1 == 1) {}
  }
  if (mode == 1) {
    set_L = CAITHONGSO(SET, 0, 5);
    lcd.setCursor(6,1); lcd.cursor();  // bat con tro
                        lcd.blink();   // nhay con tro
  }
  if(mode == 2){
    BEGIN_HR = CAITHONGSO(BEGIN_HR,0,23);
    lcd.setCursor(6,0); lcd.cursor(); 
                        lcd.blink();
  }
  if(mode == 3){
    END_HR = CAITHONGSO(END_HR,0,23);
    lcd.setCursor(12,0); lcd.cursor();
                         lcd.blink();
  }
  if(mode == 4){
    mode = 0;
    lcd.noCursor();   // tat con tro 
    
  }
}
int CAITHONGSO(int bien, int duoi, int tren) {
  if (NUT2 == 0) {
    bien++; if (bien > tren) {
      bien = duoi;
    }
    delay(10); while (NUT2 == 0) {}
  }
  if (NUT3 == 0) {
    bien--; if (bien < duoi) {
      bien = tren;
    }
    delay(10); while (NUT3 == 0) {}
  }
  return bien;
}
void LCD() {
  lcd.setCursor(2,0); lcd.print("Tu:");
  lcd.setCursor(5,0);
  if(BEGIN_HR<10){ lcd.print(" ");}
  lcd.print(BEGIN_HR);
  lcd.setCursor(7,0); lcd.print("h - ");
  lcd.setCursor(11,0); lcd.print(END_HR);
  if(END_HR<10){ lcd.print(" ");}
  lcd.setCursor(13,0); lcd.print("h");
  lcd.setCursor(1,1); lcd.print("SetL:");
  lcd.setCursor(6,1); lcd.print(SET);
  lcd.setCursor(8,1); lcd.print("DEN:");
  lcd.setCursor(12,1);
  if (digitalRead(DEN) == 1) {
    lcd.print("BAT");
  }
  else {
    lcd.print("TAT");
  }
}
