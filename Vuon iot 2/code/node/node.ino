#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "96h9V3iqy1PImsMauNJkMmOKzXDiE4ZM";
char ssid[] = "VAN01";
char pass[] = "12346789";

int data0 = 0;
int data1 = 0;
int data2 = 0;
int data02 = 0;
unsigned long tg1;
int R[5];
String S = "0";
String N = "";


void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  tg1 = millis();
}

void loop() {
  Blynk.run();
  DOWN_DL(); 
  UP_DL();
}
void UP_DL() {
  if (Serial.available()) {
    N = Serial.readStringUntil('\r');
    N.trim();
    if(N.length()==8){
    R[0] = N.substring(0, 1).toInt() ;
    R[1] = N.substring(1, 2).toInt();
    R[2] = N.substring(2, 5).toInt();
    R[3] = N.substring(5, 8).toInt();
    }
  }
  Blynk.virtualWrite(V0, R[0]);  // TT Bơm
  Blynk.virtualWrite(V1, R[1]);   // TT Đèn

  Blynk.virtualWrite(V3, R[2]);  // Nhiệt độ
  Blynk.virtualWrite(V4, R[3]);   // Độ ẩm
} 

void DOWN_DL() {
  S = "0";
  if (data2 < 100) {
    S += "0";
  }
  if (data2 < 10) {
    S += "0";
  }
  S += String(data2);
  if (millis() - tg1 > 2500) {
    Serial.println(S);
    tg1 = millis();
  }
}
BLYNK_WRITE(V0)           //  đèn 220V - V1
{
  int valuev0 = param.asInt();
  data0 = 1 - data0;
  if (data0 == 1) {
    Serial.println('B');
  }
}
BLYNK_WRITE(V1)           //  đèn 220V - V1
{
  int valuev1 = param.asInt();
  data1 = 1 - data1;
  if (data1 == 1) {
    Serial.println('D');
  }
}
BLYNK_WRITE(V2)
{
  int valuev2 = param.asInt();      // giá trị đk độ ẩm đất - V1
  data02 = 1;
  if (data02 == 1) {
    data2 = valuev2;
  }
  else {
    data2 = 0;
  }
}
