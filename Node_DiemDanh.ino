#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "5 AE SIEU NHAN"
#define WIFI_PASSWORD "12345678910jqk"

#define FIREBASE_HOST "diemdanh-6d4f3-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ILHFAtsTatG8ceRZSMKheTOQ8p1X8xh9FbkvduoR"

FirebaseData fbdt;


void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);      // khởi động chế độ bắt wifi
  Serial.print("Connecting Wifi");
  while (WiFi.status() != WL_CONNECTED) {     // đợi trong tgian kết nối
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected: ");
  Serial.print("SSID: "); Serial.println(WIFI_SSID);
  //  Serial.print("PASS: "); Serial.println(WIFI_PASSWORD);
  Serial.print("IP  : "); Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  testUpData();
  
}
void testUpData() {
  if (Serial.available()) {
    String N = Serial.readStringUntil('\r');
    N.trim();
    if (N.length() == 6) {
      String hv = N.substring(0, 2);
      String check = N.substring(5, 6);
      Firebase.setString(fbdt, "dtcs/" + hv, check);
      switch(hv.substring(1,2).toInt()){
        case 1:
        Serial.println("Văn Huy Thành");
        break;
        case 2:
        Serial.println("Lê Văn Đây");
        break;
        case 3:
        Serial.println("Nguyễn Văn Anh Quân");
        break;
      }
      
    }
    if (N.length() == 7) {
      String hv = N.substring(0, 3);
      String check = N.substring(6, 7);
      Firebase.setString(fbdt, "dtcs/" + hv, check);
      
      Serial.println("Van Huy Thanh");
    }
    if (N.length() == 8) {
      Firebase.deleteNode(fbdt, "/dtcs");
      String b = N.substring(0, 4);
      String check = N.substring(7, 8);

      Firebase.setString(fbdt, "dtcs/" + b, check);
       Serial.println("Đang Cài Đặt Buổi " + check + "...");
      for (int i = 1; i <= 50; i++) {
        Firebase.setString(fbdt, "dtcs/s" + (String)i, " ");
       
      }
      Serial.println("Cài Đặt Xong \n");
      

     
      
    }
  }
}
