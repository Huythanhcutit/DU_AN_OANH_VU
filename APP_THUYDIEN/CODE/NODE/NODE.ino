#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SoftwareSerial.h>           // khai báo các thư viện 
#include "DFRobotDFPlayerMini.h"
#include <ArduinoJson.h>
SoftwareSerial dfplay(D6, D5);     // rx - tx
//SoftwareSerial lora(D7, D0);
DFRobotDFPlayerMini LOA;
FirebaseData fbdt;
#define FIREBASE_HOST "thuydien-d3d48-default-rtdb.firebaseio.com"  // link project
#define FIREBASE_AUTH "czWgBnBR9ggDtdearJw2EOi8uWUf1ZPsO9ubFjPi"    // API
#define WIFI_SSID "chinh"
#define WIFI_PASSWORD "1234567890chinh"

int ngay, thang, nam, gio, phut, a, b, lap, t, vol;
int m, k, dem, dt, m0;
unsigned long tg, tg1;
int cb, last_cb;
int MUC1,MUC2;
float LUU_LUONG;
int t1 = 10000;   // tgian delay báo mức nước
void setup() {
  Serial.begin(250000);
  dfplay.begin(9600);              // khỏi tạo cổng serial ảo giữa esp và dfplayer
//  lora.begin(9600);
  pinMode(D6, INPUT); pinMode(D5, OUTPUT);

  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!LOA.begin(dfplay)) {  //Use softwareSerialto communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  LOA.volume(25);  //Set volume value .
  delay(1000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);         //khởi động esp chạy ở chế độ bắt wifi
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {       // hàm kiểm tra esp cps kết nối wifi chưa
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  //  khởi tạo kết nối esp với firebase
  delay(3000);
}
void loop() {
//  last_cb = cb;
//  if (MUC1 == 1 || MUC2 == 1) {
//    m0 = 1;
//  }
//  if (MUC1 == 1 && MUC2 == 0)   cb = 1;
//  else if (MUC1 == 1 && MUC2 == 1)   cb = 2;
//  else {
//    m0 = 0;
//    cb = 0;
//  }
//  if (cb - last_cb != 0)    Firebase.setInt(fbdt, "CAI_DAT/cb", cb);
//
//  if (m0 == 0) {
//    LOAD_1();
//  }
//  else          LOAD_2();
}
//void RECEIVE() {
//  if (lora.available()) {
//    String N = lora.readStringUntil('\r');
//    N.trim();;
//    JsonObject& root = jsonBuffer.parseObject(N);
//    DynamicJsonBuffer jsonBuffer(120)
//    MUC1 = root["m1"];
//    MUC2 = root["m2"];
//    LUU_LUONG = root["l"];
//  }
//}
void LOAD_2() {
  VOL2();
  delay(t1);
}
void LOAD_1() {
  tg1 = millis();
  Firebase.getString(fbdt, "CAI_DAT/set");
  if (fbdt.stringData() == "1") {
    m = 1;             // khi mà đọc biến set = 1 thì cho m =1
    dem = 0;
    Serial.println("GET DATA...");
    Firebase.getString(fbdt, "CAI_DAT/ngay");
    ngay = fbdt.stringData().toInt();
    Firebase.getString(fbdt, "CAI_DAT/thang");
    thang = fbdt.stringData().toInt();
    Firebase.getString(fbdt, "CAI_DAT/nam");
    nam = fbdt.stringData().toInt();
    Firebase.getString(fbdt, "CAI_DAT/gio");
    gio = fbdt.stringData().toInt();
    Firebase.getString(fbdt, "CAI_DAT/phut");
    phut = fbdt.stringData().toInt();
    Firebase.getString(fbdt, "CAI_DAT/a");
    a = fbdt.stringData().toInt();
    Firebase.getString(fbdt, "CAI_DAT/b");
    b = fbdt.stringData().toInt();
    Firebase.getString(fbdt, "CAI_DAT/lap");
    lap = fbdt.stringData().toInt();
    Firebase.getString(fbdt, "CAI_DAT/t");
    t = fbdt.stringData().toInt();
    Firebase.getString(fbdt, "CAI_DAT/vol");
    vol = fbdt.stringData().toInt();
    LOA.volume(vol);
    IN1();
    Firebase.setString(fbdt, "CAI_DAT/set", "0");
  }
  dt = millis() - tg1;
  if (m == 1 && dem <= lap) {
    VOL1();  // phát 1 lần
    dem++;  // +1
    delay(t * 1000);
    Serial.println("Phat xong lần " + (String)(dem - 1));
    if (dem == lap) {
      m = 0;
      Serial.println("Đã xong");
    }
  }
}
void VOL2() {
  if (cb == 1) {
    LOA.play(87);
    while (CHECK() == 0 ) {}
  }
  if (cb == 2) {
    LOA.play(88);
    while (CHECK() == 0 ) {}
  }
}
///////////////////////HÀM PHÁT THANH//////////////
void VOL1() {   // ghép các file âm thanh thành 1 đoạn phát thanh hoàn chỉnh
  LOA.play(75);        // Thông báo...
  while (CHECK() == 0 ) {}                                  //  HÀM CHECK() : kiểm tra xem đoạn trước đã phát xong chưa...... phát đoạn sau
  LOA.play(gio);      // 1 -> 23  // done
  while (CHECK() == 0 ) {
  }
  LOA.play(76);     // giờ
  while (CHECK() == 0 ) {
  }
  LOA.play(phut);    // 1 ->59   // done
  while (CHECK() == 0 ) {
  }
  LOA.play(77);   // phút ngày
  while (CHECK() == 0 ) {
  }
  LOA.play(ngay);    // 1 -> 31   // done
  while (CHECK() == 0 ) {
  }
  LOA.play(78);    // tháng
  while (CHECK() == 0 ) {
  }
  if (thang == 4) {
    LOA.play(60);
    while (CHECK() == 0 ) {}
  }
  else {
    LOA.play(thang);     // 1 -> 12
    while (CHECK() == 0 ) {}
  }
  LOA.play(79);
  // năm
  while (CHECK() == 0 ) {}
  LOA.play(nam - 1961);
  // 2022 -> 2035 <=> 61 -> 74     / done
  while (CHECK() == 0 ) {}
  LOA.play(80);
  // hồ chứa sẽ... từ
  while (CHECK() == 0 ) {}

  if (a_nghin() > 0) {
    LOA.play(a_nghin());
    // done
    while (CHECK() == 0 ) {}
    LOA.play(81);
    // nghìn
    while (CHECK() == 0 ) {}
    if (a_tram() != 0) {
      //serial .println(a_tram());
      LOA.play(a_tram());             // done
      while (CHECK() == 0 ) {}
      LOA.play(82);
      // Trăm m3/s đến ...
      while (CHECK() == 0 ) {}
    }
    else {
      LOA.play(85);
      while (CHECK() == 0 ) {}
    }
  }
  else {
    if (a_tram() != 0) {
      //serial .println(a_tram());
      LOA.play(a_tram());             // done
      while (CHECK() == 0 ) {}
      LOA.play(82);
      // Trăm m3/s đến ...
      while (CHECK() == 0 ) {}
    }
    else {
      LOA.play(85);
      while (CHECK() == 0 ) {}
    }
  }

  if (b_nghin() > 0) {
    LOA.play(b_nghin());
    // done
    while (CHECK() == 0 ) {}
    LOA.play(81);
    // nghìn
    while (CHECK() == 0 ) {}
    if (b_tram() != 0) {
      LOA.play(b_tram());
      // done
      while (CHECK() == 0 ) {}
      LOA.play(83);
      // trăm m3/s... đề nghị
      while (CHECK() == 0 ) {}
    }
    else {
      LOA.play(86);
      while (CHECK() == 0 ) {}
    }
  }
  else {
    if (b_tram() != 0) {
      LOA.play(b_tram());
      // done
      while (CHECK() == 0 ) {}
      LOA.play(83);
      // trăm m3/s... đề nghị
      while (CHECK() == 0 ) {}
    }
    else {
      LOA.play(86);
      while (CHECK() == 0 ) {}
    }
  }

}
void IN1() {
  Serial.print("Date: "); Serial.print(ngay); Serial.print("-"); Serial.print(thang); Serial.print("-"); Serial.println(nam);
  Serial.print("Time: "); Serial.print(gio); Serial.print(" : "); Serial.println(phut);
  Serial.print("A:    "); Serial.println(a);
  Serial.print("B:    "); Serial.println(b);
  Serial.print("Lap:  "); Serial.println(lap);
  Serial.print("t:    "); Serial.println(t);
  Serial.print("vol:  "); Serial.println(vol);
}
int CHECK() {
  k = 0;
  if (LOA.available()) {
    printDetail(LOA.readType(), LOA.read());
  }
  return k;
}
void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      k = 1;
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

int a_nghin() {
  int aa = a / 1000;
  return aa;
}
int a_tram() {
  int aaa = (a % 1000) / 100;
  return aaa;
}
int b_nghin() {
  int bb = b / 1000;
  return bb;
}
int b_tram() {
  int bbb = (b % 1000) / 100;
  return bbb;
}
