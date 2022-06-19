#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<SoftwareSerial.h>
SoftwareSerial nano(D1, D2);
// Set these to run example.
#define FIREBASE_HOST "include-app-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "NfF8G3rpXczeYoXSFnu1oLML2MPMkGrOV0iFS0Zb"
#define WIFI_SSID "E506"
#define WIFI_PASSWORD "Toantraidep"

String N = "";
String M = "";
int R[7];
float bui;
void setup() {
  Serial.begin(115200);
  nano.begin(115200);
  pinMode(D2, OUTPUT);
  pinMode(D1, INPUT);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop() {
SUB();
UP();
}
void UP(){
  Firebase.setFloat("co2", R[0]);
  if (Firebase.failed()) {
    Serial.print("Failed co2");
    Serial.println(Firebase.error());
    return;
  }
    Firebase.setFloat("gas", R[1]);
  if (Firebase.failed()) {
    Serial.print("Failed gas");
    Serial.println(Firebase.error());
    return;
  }
    Firebase.setFloat("co", R[2]);
  if (Firebase.failed()) {
    Serial.print("Failed co");
    Serial.println(Firebase.error());
    return;
  }
    Firebase.setFloat("bui", bui);
  if (Firebase.failed()) {
    Serial.print("Failed co2");
    Serial.println(Firebase.error());
    return;
  }
    Firebase.setFloat("temp", R[4]);
  if (Firebase.failed()) {
    Serial.print("Failed temp");
    Serial.println(Firebase.error());
    return;
  }
    Firebase.setFloat("aqi", R[5]);
  if (Firebase.failed()) {
    Serial.print("Failed aqi");
    Serial.println(Firebase.error());
    return;
  }
}
void SUB() {
  if (Serial.available()) {     // nếu có tín hiệu từ cổng serial thì...
    N = Serial.readStringUntil('\r');
    N.trim();
    // Serial.println(N);
    if (N.length() == 23) {
      R[0] = N.substring(0, 4).toInt();     //co2
      R[1] = N.substring(4, 8).toInt();     //gas
      R[2] = N.substring(8, 12).toInt();     //co
      R[3] = N.substring(12, 13).toInt();   //bui
      R[6] = N.substring(14, 16).toInt();   //bui
      R[4] = N.substring(16, 19).toInt();   //nhiet do
      R[5] = N.substring(19, 23).toInt();   // aqi
      bui = (R[3] + R[6]/100.0) ;
    }
  }
}
