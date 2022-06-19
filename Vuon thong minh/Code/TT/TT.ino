#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial lora(9, 10);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //RS,E,D4,D5,D6,D7

String G = "";
 String G1 = "";
  String G2 = "";
String F1 = "";
String F2 = "";
int GG[10];
unsigned long tg;
unsigned long tg1;
unsigned long tg2;


void setup() {
  Serial.begin(115200);
  lora.begin(9600);
  lcd.begin(20, 4);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11, 0);
  digitalWrite(12, 0);
  tg1 = millis();
  tg2 = millis();
  Serial.setTimeout(100);
  lora.setTimeout(100);
 // lcd.setCursor(1,1); lcd.println("vuon thong minh");
}

void loop() {
  XULY();
  LCD();

}
void XULY() {
  if (Serial.available()) {
  String N = "";
    N = Serial.readStringUntil(',');
    N.trim(); //Serial.println(N);
    if (N.substring(0, 1) == "0") {
      F1 = "1" + N.substring(1, 7) + ","; //lora.println(F1);Serial.println(F1);
      F2 = "2" + N.substring(7, 13)+ ","; //lora.println(F2); Serial.println(F2);
      SEND_VUON();
    }
    else {
      lora.println(N +",");
    }
  }
}
void SEND_VUON() {
  //lora.readString();
  lora.println(F1); //Serial.println("GuiVuon1");
  while (lora.available() == 0) {}
  if (lora.available()) {
    G1 = lora.readStringUntil(',');
    G1.trim(); //Serial.println(G1);
  }
  lora.readString();
  lora.println(F2); //Serial.println("GuiVuon2");
  while (lora.available() == 0) {}
  if (lora.available()) {
    G2 = lora.readStringUntil(',');
    G2.trim();/// Serial.println(G2);
  }
 
  Serial.flush();
  G = G2.substring(1, 10) + G1.substring(1, 10) +"," ;
 // Serial.print("G: ");
 if(G.length()==19){
  Serial.println(G);
  //LCD();  
 }
}
void LCD() {
  lcd.setCursor(0, 0); lcd.print("V1:");
  lcd.setCursor(12, 0); lcd.print("DAT:");
  lcd.setCursor(12, 1); lcd.print("KK:");
  lcd.setCursor(0, 1); lcd.print("D:");
  lcd.setCursor(6, 0); lcd.print("B:");
  lcd.setCursor(6, 1); lcd.print("P:");
  lcd.setCursor(0, 2); lcd.print("V2:");
  lcd.setCursor(12, 2); lcd.print("DAT:");
  lcd.setCursor(12, 3); lcd.print("KK:");
  lcd.setCursor(0, 3); lcd.print("D:");
  lcd.setCursor(6, 2); lcd.print("B:");
  lcd.setCursor(6, 3); lcd.print("P:");
  lcd.setCursor(19, 0); lcd.print("%");
  lcd.setCursor(19, 1); lcd.print("%");
  lcd.setCursor(19, 2); lcd.print("%");
  lcd.setCursor(19, 3); lcd.print("%");

  lcd.setCursor(2, 1);
  if (G.substring(0, 1).toInt() == 1) {
    lcd.print("ON ");
  }
  if (G.substring(0, 1).toInt() == 0) {
    lcd.print("OFF");
  }
  lcd.setCursor(2, 3);
  if (G.substring(9, 10).toInt() == 1) {
    lcd.print("ON ");
  }
  if (G.substring(9, 10).toInt() == 0) {
    lcd.print("OFF");
  }
  lcd.setCursor(8, 0);
  if (G.substring(1, 2).toInt() == 1) {
    lcd.print("ON ");
  }
  if (G.substring(1, 2).toInt() == 0) {
    lcd.print("OFF");
  }
  lcd.setCursor(8, 2);
  if (G.substring(10, 11).toInt() == 1) {
    lcd.print("ON ");
  }
  if (G.substring(10, 11).toInt() == 0) {
    lcd.print("OFF");
  }
  lcd.setCursor(8, 1);
  if ( G.substring(2, 3).toInt() == 1) {

    lcd.print("ON ");
  }
  if ( G.substring(2, 3).toInt() == 0) {
    lcd.print("OFF");
  }
  lcd.setCursor(8, 3);
  if (G.substring(11, 12).toInt() == 1) {
    lcd.print("ON ");
  }
  if (G.substring(11, 12).toInt() == 0) {
    lcd.print("OFF");
  }

  lcd.setCursor(16, 0);
 
  if (G.substring(3, 6).toInt()< 10) {
    lcd.print(" ");
  }
  if (G.substring(3, 6).toInt() < 100) {
    lcd.print(" ");
  }
  lcd.print(G.substring(3, 6).toInt());
  // lcd.setCursor(19,0);
  // lcd.print("%");

  lcd.setCursor(16, 2);
 
  if (G.substring(12, 15).toInt() < 10) {
    lcd.print(" ");
  }
  if (G.substring(12, 15).toInt() < 100) {
    lcd.print(" ");
  }
  lcd.print(G.substring(12, 15).toInt());
  // lcd.setCursor(19,2);
  //lcd.print("%");

  lcd.setCursor(16, 1);
  if (G.substring(6, 9).toInt() < 10) {
    lcd.print(" ");
  }
  if (G.substring(6, 9).toInt() < 100) {
    lcd.print(" ");
  }
  lcd.print(G.substring(6, 9).toInt());
  // lcd.setCursor(19,1);
  // lcd.print("%");

  lcd.setCursor(16, 3);
  
  if (G.substring(15, 18).toInt() < 10) {
    lcd.print(" ");
  }
  if (G.substring(15, 18).toInt() < 100) {
    lcd.print(" ");
  }
  lcd.print(G.substring(15, 18).toInt());
  // lcd.setCursor(19,3);
  // lcd.print("%");
  
}
