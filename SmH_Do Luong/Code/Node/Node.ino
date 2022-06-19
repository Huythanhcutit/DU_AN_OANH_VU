#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "2ij6SJB5-u8IsfYBq2Xc_nzz5YW5Nd5H";
char ssid[] = "Huypro";
char pass[] = "6899trang";

int G[6];
String R = "";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V2, "Ben ngoai:");
}
void loop() {
  Blynk.run();
  RECEIVE();
}
void RECEIVE() {
  if (Serial.available()) {                   // khi nhận đc chuỗi từ ảrduino
    R = Serial.readStringUntil('\r');
    R.trim();
    if (R.length() == 10) {
      G[0] = R.substring(0, 1).toInt();
      G[1] = R.substring(1, 2).toInt();                          // tách rời chuỗi thành các thông số
      G[2] = R.substring(2, 3).toInt();
      G[3] = R.substring(3, 7).toInt();
      G[4] = R.substring(7, 10).toInt();
    }
  }
  Blynk.virtualWrite(V0, G[0]);   // ĐÈN
  Blynk.virtualWrite(V1, G[1]);   // CỬA
  if (G[2] == 1) {
    Blynk.virtualWrite(V3, "Co nguoi");
  }
  else {                                                           //gửi lên blynk
    Blynk.virtualWrite(V3,"Khong co nguoi");
  }
  Blynk.virtualWrite(V4,G[3]);
  Blynk.virtualWrite(V5,G[4]);
  
}
