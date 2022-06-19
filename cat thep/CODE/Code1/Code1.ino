#include <LiquidCrystal.h>
LiquidCrystal lcd( 12, 11, 10, 9, 8, 7);
#define nut1 digitalRead(6)  // set
#define nut2 digitalRead(5) // mode
#define nut3 digitalRead(4)  // up
#define nut4 digitalRead(3)  // down
#define en   digitalRead(2)
#define ep A0  // kẹp
#define luoi A1  // kéo
#define den A2
#define dc A3
#define cat A4
#define cb_luoi A6
#define cb_kl A7
#define congtac A5
int l = 0;   // do dai
int s = 0;   // so luong
int s0 = 0;
int mode = 0;
int dem = 0;
int bien = 0;
unsigned long tg1;
unsigned long tg2;
void setup() {
  tg1 = millis();
  Serial.begin(9600);
  lcd.begin(16, 2);


  pinMode(6, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A7, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  // Timer1.initialize(15000);
  //  attachInterrupt(0, DEM, FALLING);
}
void loop() {
  digitalWrite(den,1);
  if(millis() % 500< 100){
    lcd.begin(16,2);
  }
  LCD();
  START();
  while (KL() == 0) {
    mode = 0;
    digitalWrite(dc, 0);
 //   digitalWrite(den, 1);
  }
}
void START() {
  if (nut2 == 0) {
    delay(20);
    if (nut2 == 0) {
      mode++;
      while (nut2 == 0) {}
    }
  }
  if (mode == 0) {
 //   lcd.begin(16, 2);
    LCD();
    digitalWrite(dc, 0);
    l = 0;
    s = 0;
    s0 = 0;
  }
  if (mode == 1) {  
    SET_BEGIN();     // cắt lấy điểm đầu tiên

    LCD();
  }
  if (mode == 2) {   // cài độ dài mỗi thanh 
    LCD();
    l = CAITHONGSO(l, 0, 300);
  }
  if (mode == 3) {   // số lượng cần cắt
    s = CAITHONGSO(s, 0, 100);
  }
  if (mode == 4) {   // bắt đầu cắt 
    digitalWrite(den,0);
    LCD();
    if(l>0 && s>0){
    while (s0 < s) {
       if(millis() % 500< 100){
    lcd.begin(16,2);
  }
      LCD();
      DEM();
      CAT();
    }
    digitalWrite(ep, 1);
    digitalWrite(cat,0);
    mode = 0;
  }
  else{
    mode = 0;
  }
  }
}
void LCD() {
  lcd.setCursor(0, 0); lcd.print("MODE:");
  lcd.setCursor(0, 1); lcd.print("DAI:");
  lcd.setCursor(9, 1); lcd.print("SL:");
  lcd.setCursor(6, 0); lcd.print(mode);
  lcd.setCursor(4, 1);
  if (l < 10) {
    lcd.print(" ");
  }
  if (l < 100) {
    lcd.print(" ");
  }
  lcd.print(l);
  lcd.setCursor(12, 1);
  if (s < 10) {
    lcd.print(" ");
  }
  if (s < 100) {
    lcd.print(" ");
  }
  lcd.print(s);
}
void CAT() {
  digitalWrite(ep, 1);
  Serial.println("ep");
  digitalWrite(cat, 1);
  delay(3000);
  digitalWrite(luoi, 1);
  Serial.println("cat");
  delay(200);
  while (digitalRead(congtac) == 1) {}
    digitalWrite(luoi, 0);
    delay(1500);
    digitalWrite(ep, 0);
    
    Serial.println("cat xong");
    dem = 0;
    s0++;

  }
  void DEM() {
    int dem = 0;
    digitalWrite(ep, 0);
    digitalWrite(dc, 1);
    while (dem < l * 125) {
      while (en == 1) {}
      while (en == 0) {}
      dem++;
      // Serial.println(dem);
    }
    digitalWrite(dc, 0);

  }
  void SET_BEGIN() {
    if (nut1 == 0) {
      delay(20);
      if (nut1 == 0) {
        digitalWrite(dc, 1);
        bien = 1;
      }
    }
    if (bien == 1) {
      digitalWrite(dc, 0);
      digitalWrite(ep, 1);
      digitalWrite(cat, 1);
      delay(3000);
      Serial.print(digitalRead(congtac));
      digitalWrite(luoi, 1);
     while (digitalRead(congtac) == 1) {}
      digitalWrite(luoi, 0);
      delay(1000);
      digitalWrite(cat, 0);
    }
    bien = 0;
  }
  int CAITHONGSO(int bien, int duoi, int tren) {
    if (nut3 == 0) {
      delay(10);
      if (nut3 == 0) {
        bien++;
        if (bien > tren) {
          bien  = duoi;
        }
        delay(10);
        while (nut3 == 0) {}
      }
    }
    if (nut4 == 0) {
      delay(10);
      if (nut4 == 0) {
        bien--;
        if (bien < duoi) {
          bien = tren;
        }
        delay(10);
        while (nut4 == 0) {}
      }
    }
    return bien;
  }
  int KL() {
    int a = analogRead(cb_kl);
    if (a > 500) {
      a = 0;
    }
    else {
      a = 1;
    }
    return a;
  }
