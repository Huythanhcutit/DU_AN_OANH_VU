#include<TimerOne.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7);//RS,E,D4,D5,D6,D7

#define nut1 6  // set
#define nut2 5  // mode
#define nut3 4  // up
#define nut4 3  // down
#define en 2
#define xl1 A0  // kẹp
#define xl2 A1  // kéo
#define den A2
#define dc A3
#define cat A4
#define cb_luoi A6
#define cb_phoi A7
int l = 0;
int sl = 0;
unsigned long tg1;
int mode = 0;
int a = 0;
int s;    // chu vi encoder, đo khi test thật = ??
int xung = 0;


void setup() {
  Serial.begin(250000);
  lcd.begin(16,2);
  pinMode(nut1, INPUT_PULLUP);
  pinMode(nut2, INPUT_PULLUP);
  pinMode(nut3, INPUT_PULLUP);
  pinMode(nut4, INPUT_PULLUP);
  pinMode(en, INPUT_PULLUP);
  pinMode(xl1,OUTPUT);
  pinMode(xl2,OUTPUT);
  pinMode(den,OUTPUT);
  pinMode(dc,OUTPUT);
  pinMode(cat,OUTPUT);
Timer1.initialize(100000);
attachInterrupt(0,XUNG, FALLING);
   tg1 = millis();
   while(digitalRead(nut1)==1){}
}

void loop() {
//  if(mode==0){
//    digitalWrite(dc,1 - digitalRead(nut1));
//    a = 1;
//    if(a ==1){
//    CAT_SET(); 
//    a = 0; 
//    }
//  }
//  START();  
   
}
void LCD(){

  
}
void START(){
  if(digitalRead(nut2)==0){
 mode++;
  while(digitalRead(nut2)==0){}
  }
  if(mode==1){   
   l = CAITHONGSO(l, 0,300);
   Serial.println(l);
  }
  if(mode==2){
   sl = CAITHONGSO(sl,0,10);
    Serial.println(sl);
  }
  if(mode==3){
  CAT();
    mode = 0;
  }  
}
void CAT(){
  for(int i; i<=sl; i++){
    digitalWrite(dc,1);
    if(DEM_EN()==l){
      digitalWrite(dc,0);
      CAT_SET();
    xung = 0; 
    lcd.setCursor(2,1); lcd.print(i); 
  }
}
}
void CAT_SET(){
  digitalWrite(cat,1);
  digitalWrite(xl1,1);
   if(millis() - tg1>300){
  digitalWrite(xl2,1);
   }
   if(millis() - tg1 > 5000){
    digitalWrite(xl2,0);
    digitalWrite(xl1,0);
   }
}

int CAITHONGSO(int bien, int duoi,int tren){
  if(digitalRead(nut3)==0){
    bien++;
    if(bien>tren){
      bien  = duoi;
    }
    delay(10); 
    while (digitalRead(nut3)==0) {}
  }
  if(digitalRead(nut4)==0){
    bien--;
    if(bien<duoi){
      bien = tren;
    }
    delay(10);
    while (digitalRead(nut4)==0) {}
  }
  return bien;
}
int DEM_EN(){
  if(digitalRead(en)==0){
   xung++;
   while(
  }
return (xung/600)*s;
 
}
