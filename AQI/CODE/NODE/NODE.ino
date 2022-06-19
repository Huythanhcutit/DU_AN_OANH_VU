#include<SoftwareSerial.h>
SoftwareSerial nano(D1, D2);       // tạo cổng serial ảo
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL1QNY-cxG"
#define BLYNK_DEVICE_NAME "Khong Khi"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI
String N = "";
String M = "";
int R[6];
#include "BlynkEdgent.h"
void setup()
{
  Serial.begin(115200);
  nano.begin(115200);
  pinMode(D2, OUTPUT);
  pinMode(D1, INPUT);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  UP();
}
void UP() {
  if (nano.available()) {     // nếu có tín hiệu từ cổng serial thì...
    N = nano.readStringUntil('\r');
    N.trim();
    if (N.length() == 23) {
      R[0] = N.substring(0, 4).toInt();     //co2
      R[1] = N.substring(4, 8).toInt();     //gas
      R[2] = N.substring(8, 12).toInt();     //co
      R[3] = N.substring(14, 16).toInt();   //bui
      R[4] = N.substring(16, 19).toInt();   //nhiet do
      R[5] = N.substring(19, 23).toInt();   // aqi
    }
    if (R[5] > 0 && R[5] <= 50) {
      M = "Very Good";
    }
    if (R[5] > 50 && R[5] <= 150) {
      M = "Good";
    }
    if (R[5] > 150 && R[5] <= 300) {
      M = "Bad";
    }
    if (R[5] > 300) {
      M = "Very Bad";
    }
  }
  Blynk.virtualWrite(V0, R[0]);     // gửi giá trị lên pin tương ứng của blynk
  Blynk.virtualWrite(V1, R[1]);
  Blynk.virtualWrite(V2, R[2]);
  Blynk.virtualWrite(V3, "0." + String(R[3]));
  Blynk.virtualWrite(V4, R[4]);
  Blynk.virtualWrite(V5, R[5]);
  Blynk.virtualWrite(V6, M);
}
