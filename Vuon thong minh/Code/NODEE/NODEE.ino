#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>    

char auth[] = "0741PG7zG3rYDuC8z9BdXmisWkoSQYQ8"; 
char ssid[] = "ThanhTrieu";   
char pass[] = "votrieu789";      
unsigned long tg1;
unsigned long tg;
int data1 = 0;
int data2 = 0;
int data3 = 0;
int data4 = 0;
int data5 = 0;
int data6 = 0;

int data8 =0;
int data08 =0;
int data9 = 0;
int data09 = 0;

int data13 = 0;
int data013 = 0;
int data14 = 0;
int data014 = 0;
String F = "";
String T = "";
int R[10];

void setup() {
Blynk.begin(auth, ssid, pass);
Serial.begin(115200);
tg1 = millis();

delay(2000);
}

void loop() {
 tg = millis();
 Blynk.run();
 CHUOI();
 TACH();
}

BLYNK_WRITE(V5)           //  đèn 220V - V1
{
  int valuev5 = param.asInt();
   data1 = 1-data1;
   if(data1==1){
  Serial.println("A,");
}
}
BLYNK_WRITE(V6)           //   bơm 12v - V1
{
  int valuev6 = param.asInt();
 data2 = 1-data2;
   if(data2==1){
  Serial.println("B,");
}
}
BLYNK_WRITE(V7)           //    bơm phun sương - V1
{
  int valuev7 = param.asInt();
  data3 = 1-data3;
   if(data3==1){
 Serial.println("C,");
}
}
BLYNK_WRITE(V8)
{
 int valuev8 = param.asInt();      // giá trị đk độ ẩm đất - V1
 data8 = 1;
 if(data8 ==1){
  data08 = valuev8;
 }
 else { data08 = 0;}
}
BLYNK_WRITE(V9)
{
  int valuev9 = param.asInt();      // giá trị đk độ ẩm kk - V1 
  data9 = 1;
 if(data9 ==1){
  data09 = valuev9;
 }
 else { data09 = 0;}
}

BLYNK_WRITE(V10)           //  đèn 220V - V2
{
  int valuev10 = param.asInt();
 data4 = 1-data4;
   if(data4==1){
 Serial.println("D,");
}
}
BLYNK_WRITE(V11)           //   bơm 12v - V2
{
  int valuev11 = param.asInt();
 data5 = 1-data5;
   if(data5==1){
 Serial.println("E,");
}
}
BLYNK_WRITE(V12)           //    bơm phun sương - V2
{
  int valuev12 = param.asInt();
 data6 = 1-data6;
   if(data6==1){
 Serial.println("F,");
}
}
BLYNK_WRITE(V13)
{
  int valuev13 = param.asInt();      // giá trị đk độ ẩm đất - V2
   data13 = 1;
 if(data13 ==1){
  data013 = valuev13;
 }
 else { data013 = 0;}
}
BLYNK_WRITE(V14)
{
 int valuev14 = param.asInt();      // giá trị đk độ ẩm kk - V2
  data14 = 1;
 if(data14 ==1){
  data014 = valuev14;
 }
 else { data08 = 0;}
}

void TACH(){
  if(Serial.available()){
    T = Serial.readStringUntil(',');
    T.trim();   
    if(T.length()==18){
      R[0] = T.substring(0,1).toInt();
      R[1] = T.substring(1,2).toInt();
      R[2] = T.substring(2,3).toInt();
      R[3] = T.substring(3,6).toInt();
      R[4] = T.substring(6,9).toInt();
      R[5] = T.substring(9,10).toInt();
      R[6] = T.substring(10,11).toInt();
      R[7] = T.substring(11,12).toInt();
      R[8] = T.substring(12,15).toInt();
      R[9] = T.substring(15,18).toInt();     
    }    
  }
  Blynk.virtualWrite(V5,R[0]);   // bóng đèn 220V - V1
  Blynk.virtualWrite(V6,R[1]);    // bơm 12V - V1
  Blynk.virtualWrite(V7,R[2]);   // bơm phun sương - V1
  Blynk.virtualWrite(V3,R[3]);   // độ ẩm đất - V1
  Blynk.virtualWrite(V4,R[4]);   // độ ảm kk - V1
  
  Blynk.virtualWrite(V10,R[5]);   // bóng đèn 220V - V2
  Blynk.virtualWrite(V11,R[6]);    // bơm 12V - V2
  Blynk.virtualWrite(V12,R[7]);   // bơm phun sương - V2
  Blynk.virtualWrite(V15,R[8]);   // độ ẩm đất - V1
  Blynk.virtualWrite(V16,R[9]);   // độ ảm kk - V1
  
 
}
void CHUOI(){
  F ="0";
 if(data08<100){F+="0";}
 if(data08<10){F+="0";}   
 F+= String(data08);
 if(data09<100){F+="0";}
 if(data09<10){F+="0";} 
 F+= String(data09);
 if(data013<100){F+="0";}
 if(data013<10){F+="0";}   
 F+= String(data013);
 if(data014<100){F+="0";}
 if(data014<10){F+="0";} 
 F+= String(data014);
 F+=",";
 if(Serial.available()==0 && tg-tg1>4000){
  Serial.println(F);
  tg1 = millis();
 }
}
