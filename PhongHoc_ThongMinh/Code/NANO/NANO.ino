#include<LiquidCrystal.h>              // Khai báo thư viện     // LCD
#include <SoftwareSerial.h>            // Serial ảo
#include"DS1307.h"                     // Thư viện thời gian thực
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
SoftwareSerial node(5, 6); // RX, TX
#define LX analogRead(A0)
#define MC analogRead(A1)
#define VOLUM analogRead(A6)
#define LM35 analogRead(A7)               
#define F 13
#define L 3
#define NUT1 digitalRead(2)
#define NUT2 digitalRead(4)
int L1;
int L2;
int NHIETDO_SET = 30;                      // set ngưỡng nhiệt độ bật quạt
int ng = 0;
int dem;
int n = 0;
int TDF = 0;
int TDF1;
int TDL = 0;
unsigned long tg,tg1,tg10;
unsigned long tg1manual = 15000;     // thời gian tắt quạt sau khi bật thủ công
unsigned long tg1auto = 15000;       // thời gian tắt quạt sau khi k có người
unsigned long tg2;
unsigned long tg20 = 100000 ;
unsigned long tg2auto = 15000;       // Thời gian tắt đèn sau khi bật thủ công
unsigned long tg2manual = 15000;     // Thời gian tắt đèn sau khi k có người
unsigned long tgv;
int hbd = 6;                         // Giờ bắt đầu
int hkt = 22;                        // Giờ kết thúc
float out ;
String U = "";
int a = 0;
int b = 0;
void setup() {
  Serial.begin(115200);                // Khởi tạo cổng Serial 
  node.begin(115200);                  // ..............Serial ảo
  lcd.begin(16, 2);                    // Bắt đầu cho lcd hoạt động
  Wire.begin();
  pinMode(F, OUTPUT);
  pinMode(L, OUTPUT);                  //    Khai báo đầu ra / đầu vào
  pinMode(2, INPUT_PULLUP);            
  pinMode(4, INPUT_PULLUP);
  //setTime(18, 10, 30, 5, 30, 12, 2021);
}
void loop() {
    READDS1307();
    DIEUKHIEN();
    FAN();      
    LIGHT();    // Bật tắt đèn theo độ sáng
    NGUOI();    // đếm số người trong phòng
    LCD();      
    UP_DL();    
    Serial.println("TDF: " + String(TDF) +"   TDL: " + String(TDL));
}
void LCD() {            // Hiển thị lcd
  lcd.setCursor(0, 0); lcd.print("SNg:");
  lcd.setCursor(4, 0);
  if (n < 100) {
    lcd.print(" ");
  }
  if (n < 10) {
    lcd.print(" ");
  }
  lcd.print(n);
  lcd.setCursor(8, 0); lcd.print("LUX:");
  lcd.setCursor(12, 0);
  if(millis() - tgv >500){
  if (SET() < 100) {
    lcd.print(" ");
  }
  if (SET() < 10) {
    lcd.print(" ");
  }
  lcd.print(SET());
  tgv = millis();
  }
  lcd.setCursor(0, 1); lcd.print("F:");
  lcd.setCursor(2, 1); lcd.print(b);
  lcd.setCursor(4, 1); lcd.print("L:");
  lcd.setCursor(6, 1); lcd.print(a);
  lcd.setCursor(8, 1); lcd.print("t*:");
  lcd.setCursor(11, 1);
  if (NHIETDO() < 100) {
    lcd.print(" ");
  }
  if (NHIETDO() < 10) {
    lcd.print(" ");
  }
  lcd.print(NHIETDO());
  lcd.setCursor(14, 1); lcd.print("*C");
}
void UP_DL() {
  U = "";
   U += String(b);
   U += String(a);
  if (n < 10) {
    U += "0";
  }
  U += String(n);
  if (SET() < 100) {
    U += "0";
  }
  if (SET() < 10) {
    U += "0";
  }
  U += String(SET());
  if (NHIETDO() < 100) {
    U += "0";
  }
  if (NHIETDO() < 10) {
    U += "0";
  }
  U += String(NHIETDO());
   if (millis() - tg > 1000) {////    1s gửi trạng thái lên 1 lần
     node.println(U);              // gửi chuỗi U sang node
     // Serial.println(U);
     tg = millis();
   }
}
void LIGHT() {
  if (gio > hbd && gio < hkt) {  // Xét trong giờ
    if (n >= 1) {
      tg20 = millis();
    }
    if (millis() - tg20 < tg2auto) {   //đếm tgian để tắt đèn sau bao lâu
      if (MCH() == 0) {
       PID(SET());
        a = 1;
         Serial.println("   den");
      }
      else {
        PID(180);
        a = 1;
        Serial.println("   MCH");
      }
    }
    else {
 if (TDL == 1) {
      Serial.println("den bat thu cong   ");
      if (MCH() == 0) {
        PID(SET());
        a = 1;
        Serial.println("thu cong   ");
      }
      else {
        PID(180);
        a = 1;
        Serial.println("MCH1   ");
      }
    }
    else {
      digitalWrite(L, 0);
      a = 0;
    }
    }
  }
  else {                   // xét ngoài giờ
    if (TDL == 1) {
      Serial.println("den bat thu cong");
      if (MCH() == 0) {
        PID(SET());
        a = 1;
        Serial.println("thu cong");
      }
      else {
        PID(180);
        a = 1;
        Serial.println("MCH1");
      }
    }
    else {
      digitalWrite(L, 0);
      a = 0;
    }
  }
}
void PID(int st) {   //  Điều chỉnh độ sáng theo môi trường
  if (st > LUX()) {
    out += 0.4;
  }
  else {
    out -= 0.4;
  }
  if (out > 255) {
    out = 255;
  }
  if (out < 0) {
    out = 0;
  }
  int PWM = (int)out;

  analogWrite(L, PWM);
}
void FAN() {
  if (gio > hbd && gio < hkt) {      // trong giờ
    if (n >= 1) {
      tg10 = millis();
      Serial.println("co nguoi");
    }
    if (millis() - tg10 < tg1auto) {
      if (NHIETDO() > NHIETDO_SET) {
        digitalWrite(F, 1);
        b = 1;
      }
      else {
     if (TDF1 == 1) {
      Serial.println(" quat bat thu cong trong gio   ");
      digitalWrite(F, 1);
      b = 1;
    }
    else {
      digitalWrite(F, 0);
      b = 0;
    }
      }
    }
    else {
    digitalWrite(F,0);
    b = 0;
    }
  }
  else {
    if (TDF == 1) {
      //Serial.println(" quat bat thu cong");
      digitalWrite(F, 1);
      b = 1;
    }
    else {
      digitalWrite(F, 0);
      b = 0;
    }
  }
}
void DIEUKHIEN() {
  if (node.available()) {             // nếu cổng serial có tín hiệu thì...
    String N = "";
    N = node.readStringUntil('\r');
    N.trim();
    Serial.println(N);
    if (N == "F") {
      if (TDF == 0) {
        tg1 == millis();
        TDF = 1 -TDF;
        Serial.println("quat");
      }
    }
    if (N == "L") {
      if (TDL == 0) {
        tg2 == millis();
        TDL = 1 - TDL;
        Serial.println("den");
      }
    }
  }
  NUT();
  if (millis() - tg1 > tg1manual && TDF == 1) {
    TDF = 0;
    tg1 = millis();
  }
  if (millis() - tg2 > tg2manual && TDL == 1) {
    TDL = 0;
    tg2 = millis();
  }
}
void NUT() {
  if (NUT1 == 0) {
    delay(20);
    if (NUT1 == 0) {
        TDF = 1-TDF;
        TDF1 = 1 - TDF1;
        tg1 = millis();
      while (NUT1 == 0) {}
    }
  }
  if (NUT2 == 0) {
    delay(20);
    if (NUT2 == 0) {
        TDL = 1 - TDL;
        tg2 = millis();
      }
      while (NUT2 == 0) {}
    }
  }
int SET() {
  int a = map(VOLUM, 0, 1023, 0, 500);
  return a;
}
void NGUOI() {                         // CT con đếm người ra vào
  if (analogRead(A2) > 900) {
    L1 = 0;
  }
  else {
    L1 = 1;
  }
  if (analogRead(A3) > 900) {
    L2 = 0;
  }
  else {
    L2 = 1;
  }
  if (L1 == 0 && L2 == 0 && dem == 1) {
    ng = 0;
    dem = 0;
  }
  if (L1 == 0 && L2 == 1) { 
    ng = 1;
  }
  if (L1 == 1 && L2 == 0) {
    ng = 2;
  }
  if (ng == 1) {
    if (L1 == 0 && L2 == 0 && dem == 0) {
      n++;
      dem = 1;
    }
  }
  if (ng == 2) {
    if (L1 == 0 && L2 == 0 && dem == 0) {
      n--;
      dem = 1;
    }
  }
  if (n < 0) {
    n = 0;
  }
}        //////////////////////////////////////
int NHIETDO() {
  float t = (LM35 * 5.0 * 100) / 1023;   // ct 
  return (int)t;
}
int MCH() {
  if (MC > 900) {
    return 1;
  }
  else {
    return 0;
  }
}
int LUX() {
  int b = LX - 250 ;
  return b;
}
