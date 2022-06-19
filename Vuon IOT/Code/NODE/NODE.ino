#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = " zIXIqJselcxvA72MWJKAAjCAtLGcQgQj";
char ssid[] = "Huannguyen";
char pass[] = "huannguyen123";

int data1 = 0;
int data2 = 0;
int data7 = 0;
int data07 = 0;
int data8 = 0;
int data08 = 0;

unsigned long tg;
unsigned long tg1;

int R[10];
String S = "0";
String N = "";

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  tg = millis();
  Blynk.run();
  Serial.println("hjdfjgv");
//  UP_DL();
//  DOWN_DL();

}

void UP_DL() {
  if (Serial.available()) {

    N = Serial.readStringUntil('\r');
    N.trim();
    if (N.length() == 13) {
      R[0] = N.substring(0, 1).toInt() ;
      R[1] = N.substring(1, 2).toInt();
      R[2] = N.substring(2, 3).toInt();
      R[3] = N.substring(3, 4).toInt();
      R[4] = N.substring(4, 7).toInt();
      R[5] = N.substring(7, 10).toInt();
      R[6] = N.substring(10, 13).toInt();
    }
  }
  Blynk.virtualWrite(V0, R[0]);  // TT Bơm
  Blynk.virtualWrite(V1, R[1]);   // TT Phun Sương
  Blynk.virtualWrite(V2, R[2]);  // TT mưa

  Blynk.virtualWrite(V3, R[3]);  // TT nắng
  Blynk.virtualWrite(V4, R[4]);   // Nhiệt độ
  Blynk.virtualWrite(V5, R[5]);  //  Độ ẩm kk
  Blynk.virtualWrite(V6, R[6]);  // Độ ẩm đất
}
void DOWN_DL() {
  S = "0";
  if (data7 < 100) {
    S += "0";
  }
  if (data7 < 10) {
    S += "0";
  }
  S += String(data7);
  if (data8 < 100) {
    S += "0";
  }
  if (data8 < 10) {
    S += "0";
  }
  S += String(data8);
  if (tg - tg1 > 2600) {
    Serial.println(S);
    tg1 = millis();
  }
}
BLYNK_WRITE(V0)           //  đèn 220V - V1
{
  int valuev5 = param.asInt();
  data1 = 1 - data1;
  if (data1 == 1) {
    Serial.println("B");
  }
}
BLYNK_WRITE(V1)           //  đèn 220V - V1
{
  int valuev5 = param.asInt();
  data2 = 1 - data2;
  if (data2 == 1) {
    Serial.println("P");
  }
}
BLYNK_WRITE(V7)
{
  int valuev7 = param.asInt();      // giá trị đk độ ẩm đất - V1
  data07 = 1;
  if (data07 == 1) {
    data7 = valuev7;
  }
  else {
    data7 = 0;
  }
}
BLYNK_WRITE(V8)
{
  int valuev8 = param.asInt();      // giá trị đk độ ẩm đất - V1
  data08 = 1;
  if (data08 == 1) {
    data8 = valuev8;
  }
  else {
    data8 = 0;
  }
}
