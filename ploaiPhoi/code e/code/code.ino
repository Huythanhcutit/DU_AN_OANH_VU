#define CB analogRead(A7)
#define XL1 A1
#define XL2 A0
#define XL3 A2
#define DC A3
#define START digitalRead(4)
#define STOP  digitalRead(5)

#include <TimerOne.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd( 11, 10, 9, 8, 7,6);
//#include "HX711.h"
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;
//HX711 scale;   /// nguongwx laf 260
int loai = 0;
int chuan = 40;
int nhe = 20;
int sp1, sp2, sp3;
int mode = 0;
void setup() {
  lcd.begin(16, 2);
 // INITCAN();
  lcd.setCursor(0, 0); lcd.print("SP1:");
  lcd.setCursor(5, 0); lcd.print("SP2:");
  lcd.setCursor(10, 0); lcd.print("SP3:");
  Serial.begin(9600);
  pinMode(XL1, OUTPUT); pinMode(XL2, OUTPUT); pinMode(XL3, OUTPUT);
  pinMode(DC, OUTPUT); pinMode(4, INPUT_PULLUP); pinMode(5, INPUT_PULLUP);
  while (mode == 0) {
    if (Serial.available()) {
      if (Serial.read() == 'A') {
        mode = 1;
        digitalWrite(DC, 1);
      }
    }
    if (START == 0) {
      mode = 1;
      digitalWrite(DC, 1);
    }
  }
  Timer1.initialize(100000);
  Timer1.attachInterrupt(NGAT);
}

void loop() {
  // caaps phooi ra
  digitalWrite(DC, 1); digitalWrite(XL1, 1);
  while (CB > 500) {}
  digitalWrite(DC, 0); digitalWrite(XL1, 0);
  delay(500);
  int a = CAN();
  if (a > chuan) {
    sp1++;
    digitalWrite(XL2, 1); delay(2000);
    digitalWrite(XL2, 0);
  }
  if (a <= chuan && a > nhe) {
    sp2++;
    digitalWrite(XL3, 1); delay(2000);
    digitalWrite(XL3, 0);
  }
  if (a <= nhe) {
    sp3++;
    digitalWrite(DC, 1);
    while (CB < 500) {}
    delay(10);
  }
  
  lcd.setCursor(1, 1); lcd.print(sp1);
  lcd.setCursor(6, 1); lcd.print(sp2);
  lcd.setCursor(11, 1); lcd.print(sp3);

  String data1 = String(sp1);if(sp1<10)data1 = "0"+data1;
  String data2 = String(sp2);if(sp2<10)data2 = "0"+data2;
  String data3 = String(sp3);if(sp3<10)data3 = "0"+data3;
  String data = data1 + data2 + data3;
  Serial.println(data);
}

void NGAT() {
  if (mode == 1) {
    if (Serial.available()) {
      if (Serial.read() == 'B') {
        mode = 0;
        digitalWrite(DC, 0);
      }
    }
    if (STOP == 0) {
      mode = 0;
      digitalWrite(DC, 0);
    }
  }
  if (mode == 0) {
    if (Serial.available()) {
      if (Serial.read() == 'A') {
        mode = 1;
        digitalWrite(DC, 1);
      }
    }
    if (START == 0) {
      mode = 1;
      digitalWrite(DC, 1);
    }
  }
}


//int CAN() {
//  //scale.get_units();
//  float cannang = scale.get_units();
//  if (cannang < 0) {
//    cannang = 0;
//  }
//  return (int)cannang;
//}
//void INITCAN() {
//  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
//  (scale.read());     // print a raw reading from the ADC
//  (scale.read_average(20));
//  (scale.get_value(5));
//  (scale.get_units(5), 1);
//  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
//  scale.tare();               // reset the scale to 0
//  (scale.read());                 // pr
//  (scale.read_average(20));       // p
//  (scale.get_value(5));   // print th
//  (scale.get_units(5), 1);        //
//  //Serial.println("Readings:");
//
//}
