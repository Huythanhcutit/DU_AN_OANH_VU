#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#define FIREBASE_HOST "ql-kho-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "Zn51GmLMNefQimfF6ScBZV7ybUvUaJprXxPciujd"
#define WIFI_SSID "DOANTN"
#define WIFI_PASSWORD "99999999"
FirebaseData fbdt;
int ccs, cd, cq;
int last_ccs, last_cd, last_cq;
int R[10];
void setup() {
  Serial.begin(250000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);      // khởi chạy chế độ STATION
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {     // đợi trong tgian kết nối
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected: ");
  Serial.print("SSID: "); Serial.println(WIFI_SSID);
  Serial.print("PASS: "); Serial.println(WIFI_PASSWORD);
  Serial.print("IP  : "); Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);     // khởi cahyj thư viện firebase
  delay(100);
  Firebase.setString(fbdt, "KHO/ccs", "0");
  Firebase.setString(fbdt, "KHO/cd", "0");
  Firebase.setString(fbdt, "KHO/cq", "0");
  Serial.println("Setup Done!!!");
}
void loop() {
  DOWN();
  UP();
}
void DOWN () {
  last_ccs = ccs;
  last_cd = cd;
  last_cq = cq;
  Firebase.getString(fbdt, "KHO/ccs");
  ccs = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "KHO/cd");
  cd = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "KHO/cq");
  cq = fbdt.stringData().toInt();
  if (ccs - last_ccs == 1) {
    Serial.println("1S");
  }
  if (ccs - last_ccs == -1) {
    Serial.println("0S");
  }
  if (cd - last_cd == 1) {    
    Serial.println("1D");
  }
  if (cd - last_cd == -1) {
    Serial.println("0D");
  }
  if (cq - last_cq == 1) {
    Serial.println("1Q");
  }
  if (cq - last_cq == -1) {
    Serial.println("0Q");
  }
}
void UP() {
  if (Serial.available()) {
    String N = Serial.readStringUntil('\r');
    N.trim();
    //    Serial.println(N);
    if (N.length() == 16) {
      Firebase.setString(fbdt, "KHO/tr", N.substring(15, 16));
      Firebase.setString(fbdt, "KHO/h", N.substring(0, 5));
      Firebase.setString(fbdt, "KHO/t", N.substring(5, 10));
      Firebase.setString(fbdt, "KHO/cc", N.substring(10, 11));
      Firebase.setString(fbdt, "KHO/cs", N.substring(11, 12));
      Firebase.setString(fbdt, "KHO/d", N.substring(12, 13));
      Firebase.setString(fbdt, "KHO/q", N.substring(13, 14));
      Firebase.setString(fbdt, "KHO/ch", N.substring(14, 15));
    }
  }
}
