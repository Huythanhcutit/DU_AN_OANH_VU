#include <ESP8266WiFi.h>                 // thư viện cho phép nodemcu kết nối wifi
#include <FirebaseESP8266.h>             // thư viện firabase
#include <ArduinoJson.h>

FirebaseData fbdt;
#define FIREBASE_HOST "thuydien-d3d48-default-rtdb.firebaseio.com"  // link project
#define FIREBASE_AUTH "czWgBnBR9ggDtdearJw2EOi8uWUf1ZPsO9ubFjPi"    // API
#define WIFI_SSID "Quockhanh"
#define WIFI_PASSWORD "khanh02092000"

#define NANO analogRead(A0)
int sett;
void setup() {
  Serial.begin(57600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);         //khởi động esp chạy ở chế độ bắt wifi
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {       // hàm kiểm tra esp cps kết nối wifi chưa
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());        // in ra serial địa chỉ ip
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  //  khởi tạo kết nối esp với firebase
  delay(3000);

}
void loop() {
  GET_THAM_SO();
  SET_CANH_BAO();
}
void SET_CANH_BAO() {              // đọc dữ liệu gửi sang từ nano
  if (Serial.available()) {
    String N = Serial.readStringUntil('\r');
    N.trim();
    if (N.length() == 2) {
      Firebase.setInt(fbdt, "CAI_DAT/cb", N.substring(0, 1).toInt());
      Firebase.setInt(fbdt, "CAI_DAT/nuoc", N.substring(1, 2).toInt());
    }
  }
}

void GET_THAM_SO() {             // hàm đọc dữ liệu từ firebase
  DynamicJsonBuffer jsonBuffer(300);
  JsonObject& root = jsonBuffer.createObject();
  Firebase.getString(fbdt, "CAI_DAT/set");
  // Serial.println(fbdt.stringData());
  sett = fbdt.stringData().toInt();
  //    Serial.println("GET DATA...");
  Firebase.getString(fbdt, "CAI_DAT/ngay");
  root["ng"] = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "CAI_DAT/thang");
  root["th"] = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "CAI_DAT/nam");
  root["n"] = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "CAI_DAT/gio");
  root["g"] = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "CAI_DAT/phut");
  root["p"] = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "CAI_DAT/a");
  root["a"] = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "CAI_DAT/b");
  root["b"] = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "CAI_DAT/lap");
  root["l"] = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "CAI_DAT/t");
  root["t"] = fbdt.stringData().toInt();
  Firebase.getString(fbdt, "CAI_DAT/vol");
  root["v"] = fbdt.stringData().toInt();
  // Serial.println("CHeCK1");
  //}
  if (NANO > 200) {
    //    Serial.println("CHeCK2");
    if (sett == 1) {
      root.printTo(Serial);
      Serial.println();
      Firebase.setInt(fbdt, "CAI_DAT/set", 0);
      sett = 0;
    }
    else {
      Serial.println('a');
    }
  }
}
