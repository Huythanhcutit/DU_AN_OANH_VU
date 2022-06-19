#include<Servo.h>
#include <LiquidCrystal_I2C.h>
#include<DHT.h>
#include <MQ135.h>
#include"DS1307.h"
#include"SERVO.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
int ttcua = 0 ;    // biến trạng thái của cửa bật/tắt
DHT dht(A3, DHT11);
int t;             // Nhiệt độ
MQ135 mq135ss = MQ135(A6);
#define CAMUNG digitalRead(A2)
#define PIR1 analogRead(A7)
#define TRIG 8
#define ECHO 7
#define LOA 5
#define DEN 4
int hbd = 18;     // giờ bắt đầu
int hkt = 6;      // Giờ kết thúc
unsigned long tg1;
unsigned long tg2;
unsigned long tgkcn = 5000;
unsigned long tgcua = 5000;
int SET_NDO = 35;    // Cài ngưỡng nhiệt độ
int KC = 7;          // Cài khoảng cách phát hiện người
int ppm ;
float e = 2.71828;    // hằng số logarit
int G[6];
String R = "";

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  CUA.attach(6);
  pinMode(TRIG, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  READDS1307();               // đọc thời gian từ ds1307
  LCD();                      // hiển thị lcd
  NHIETDO();                  
  DOOR();
  KK();
  PHATHIENNGUOI();
  SEND();
}
void SEND() {                    // gửi thông số sang Nodemcu
  G[0] = digitalRead(DEN);
  G[1] = ttcua ;
  G[2] = SRF();
  G[3] = ppm;
  G[4] = t;
  R = "";
  R += String(G[0]);
  R += String(G[1]);
  R += String(G[2]);
  if (G[3] < 1000) {
    R += "0";
  }
  if (G[3] < 100) {
    R += "0";
  }
  if (G[3] < 10) {
    R += "0";
  }
  R += String(G[3]);
  if (G[4] < 100) {
    R += "0";
  }
  if (G[4] < 10) {
    R += "0";
  }
  R += String(G[4]);
  Serial.println(R);
}
void LCD() {
  lcd.setCursor(0, 0); lcd.print("Den");
  lcd.setCursor(4, 0); lcd.print("Cua");
  lcd.setCursor(9, 0); lcd.print("PPM");
  lcd.setCursor(13, 0); lcd.print("NDo");
  lcd.setCursor(0, 1);
  if (digitalRead(DEN) == 1) {
    lcd.print("ON ");
  }
  else {
    lcd.print("OFF");
  }
  lcd.setCursor(4, 1);
  if (ttcua == 1) {
    lcd.print("Ope");
  }
  else {
    lcd.print("Clo");
  }

  lcd.setCursor(13, 1);
  if (t < 10) {
    lcd.print(" ");
  }
  lcd.print(t);
  lcd.setCursor(8, 1);
  if (ppm < 1000) {
    lcd.print(" ");
  }
  if (ppm < 100) {
    lcd.print(" ");
  }
  if (ppm < 10) {
    lcd.print(" ");
  }
  lcd.print(ppm);
}
void KK() {           // mq135
  float v = analogRead(A6);
  float Vcb = 5 * v / 1023;
  ppm = 26.572 * pow(e, 1.2894 * Vcb);           // công thức thực thế
}
void PHATHIENNGUOI() {
  if (gio > hbd || gio < hkt ) {
    if (PIR()==1) {                   // đọc analog, khi giá trị > 500 thì là mức 1( có người)
      tg1 = millis();
    }
    if (millis() - tg1 < tgkcn) {
      digitalWrite(DEN, 1);
    }
    else {
      digitalWrite(DEN, 0);
    }
  }
}
void NHIETDO() {
  t = dht.readTemperature();       // đọc nhiệt độ từ cb dht11
  //  Serial.print(t);
  if (t > SET_NDO) {
    digitalWrite(LOA, 1);
  }
  else {
    digitalWrite(LOA, 0);
  }
}
void DOOR() {
  if (CAMUNG == 1 || SRF() == 1) {      // khi chạm tay hoặc có người thì...
    tg2 = millis();                       
  }
  if (millis() - tg2 < tgcua) {
    SV(180, 5);
    ttcua = 1;
    //    Serial.print("mo cua");
  }
  else {
    SV(85, 5);
    ttcua = 0;
    //    Serial.print("dong cua");
  }
}

int SRF() {            // cảm biến siêu âm
  unsigned long thoigian;
  digitalWrite(TRIG, 1);         // Phát siêu âm đi
  delayMicroseconds(5);
  digitalWrite(TRIG, 0);
  thoigian = pulseIn(ECHO, HIGH);       // tính thời gina xung quay lại
  int khoangcach = thoigian / 2 / 29.412;     // tính khoảng cách
  if (khoangcach != 0) {
    khoangcach = khoangcach;
  }
  if (khoangcach < KC) {
    return 1 ;
  }
  else {
    return 0;
  }
}
int PIR(){       // biến dổi digital cảm biến chuyển động
  if(PIR1<500){
   return 0;
}
else{
  return 1;
}
}
