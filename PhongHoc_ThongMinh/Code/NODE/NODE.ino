#include <ESP8266WiFi.h>                   // Khai báo thư viện
#include <BlynkSimpleEsp8266.h>
char auth[] = "hrdT7JeRtFmuGNH4X5X9-KDL0OvdSV0T";
char ssid[] = "OANH VU";
char pass[] = "bat3gdiem";
String N = "";
int R[6];
int data1 = 0;
int data2 = 0;
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  UP_DL();
}
void UP_DL() {
  if (Serial.available()) {///////// nếu mà có tín hiệu từ cổng serial thì...
    N = Serial.readStringUntil('\r');
    N.trim();
    if(N.length()==10){
    R[0] = N.substring(0, 1).toInt();   // Quat
    R[1] = N.substring(1, 2).toInt();   // Den
    R[2] = N.substring(2, 4).toInt();   // So nguoi         tách các giá trị trạng thái ra từ chuỗi
    R[3] = N.substring(4, 7).toInt();   // Set do sang
    R[4] = N.substring(7, 10).toInt();   // Nhiet do
  }
  }
  Blynk.virtualWrite(V0, R[0]);
  Blynk.virtualWrite(V1, R[1]);
  Blynk.virtualWrite(V2, R[2]);           ///  Gửi các giá trị lên app 
  Blynk.virtualWrite(V3, R[3]);
  Blynk.virtualWrite(V4, R[4]);
}
BLYNK_WRITE(V0)           //  Quat
{
  int valuev1 = param.asInt();
  data1 = 1 - data1;
  if (data1 == 1) {
    Serial.println('F');
  }
}
BLYNK_WRITE(V1)           //  Den
{
  int valuev2 = param.asInt();
  data2 = 1 - data2;
  if (data2 == 1) {
    Serial.println('L');
  }
}
