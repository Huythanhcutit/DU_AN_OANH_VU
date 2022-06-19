#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>      
char auth[] = "u-nb2N0YfInKRnbgDk7JezYT0ZOL25eX";      
char ssid[] = "Thach";
char pass[] = "12345678a";

int R[15];
String N = "";
int data1;
int data2;
int data3;
int data4;
int data5;
int data6;
int data7;
int data8;
int data9;
int data10;
int data11;
int data12;
int data13;
int data14;
int data15;

void setup() {
  Serial.begin(57600);
  Blynk.begin(auth, ssid, pass);
}
void loop() {
  Blynk.run();
  UP();
}
void UP() {
  if (Serial.available()) {    
    N = Serial.readStringUntil('\r');
    N.trim();
    if (N.length()==15) {
    //  Serial.println(N);
      R[0] = N.substring(0, 1).toInt();          
      R[1] = N.substring(1, 2).toInt();
      R[2] = N.substring(2, 3).toInt();
      R[3] = N.substring(3, 4).toInt();
      R[4] = N.substring(4, 5).toInt();
      R[5] = N.substring(5, 6).toInt();
      R[6] = N.substring(6, 7).toInt();
      R[7] = N.substring(7, 8).toInt();
      R[8] = N.substring(8, 9).toInt();
      R[9] = N.substring(9, 10).toInt();
      R[10] = N.substring(10, 11).toInt();
      R[11] = N.substring(11, 12).toInt();
      R[12] = N.substring(12, 13).toInt();
      R[13] = N.substring(13, 14).toInt();
      R[14] = N.substring(14, 15).toInt();
      
    }
  }
  Blynk.virtualWrite(V0, R[0]);
  Blynk.virtualWrite(V1, R[1]);
  Blynk.virtualWrite(V2, R[2]);
  Blynk.virtualWrite(V3, R[3]);
  Blynk.virtualWrite(V4, R[4]);
  Blynk.virtualWrite(V5, R[5]);
  Blynk.virtualWrite(V6, R[6]);           
  Blynk.virtualWrite(V7, R[7]);
  Blynk.virtualWrite(V8, R[8]);
  Blynk.virtualWrite(V9, R[9]);
  Blynk.virtualWrite(V10, R[10]);
  Blynk.virtualWrite(V11, R[11]);
  Blynk.virtualWrite(V12, R[12]);
  Blynk.virtualWrite(V13, R[13]);
  Blynk.virtualWrite(V14, R[14]);
}
BLYNK_WRITE(V0)           
{
  int valuev1 = param.asInt();
  data1 = 1 - data1;
  if (data1 == 1) {
    Serial.println("CSN");
  }
}
BLYNK_WRITE(V1)           //  Den
{
  int valuev2 = param.asInt();
  data2 = 1 - data2;
  if (data2 == 1) {
    Serial.println("FN");
  }
}
BLYNK_WRITE(V2)           //  Quat
{
  int valuev3 = param.asInt();
  data3 = 1 - data3;
  if (data3 == 1) {
    Serial.println("LN");
  }
}
BLYNK_WRITE(V3)           //  Den
{
  int valuev4 = param.asInt();
  data4 = 1 - data4;
  if (data4 == 1) {
    Serial.println('B');
  }
}
BLYNK_WRITE(V4)           //  Quat
{
  int valuev5 = param.asInt();
  data5 = 1 - data5;
  if (data5 == 1) {
    Serial.println("LB");
  }
}
BLYNK_WRITE(V5)           //  Den
{
  int valuev6 = param.asInt();
  data6 = 1 - data6;
  if (data6 == 1) {
    Serial.println("CSK");
  }
}
BLYNK_WRITE(V6)           //  Quat
{
  int valuev7 = param.asInt();
  data7 = 1 - data7;
  if (data7 == 1) {
    Serial.println("FK");
  }
}
BLYNK_WRITE(V7)           //  Den
{
  int valuev8 = param.asInt();
  data8 = 1 - data8;
  if (data8 == 1) {
    Serial.println("LK");
  }
}
BLYNK_WRITE(V8)           
{
  int valuev9 = param.asInt();
  data9 = 1 - data9;
  if (data9 == 1) {
    Serial.println("CCK");
  }
}
BLYNK_WRITE(V10)           
{
  int valuev11 = param.asInt();
  data11 = 1 - data11;
  if (data11 == 1) {
    Serial.println("CS");
  }
}

BLYNK_WRITE(V11)         
{
  int valuev12 = param.asInt();
  data12 = 1 - data12;
  if (data12 == 1) {
    Serial.println("CC");
  }
}
