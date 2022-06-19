#include "DFRobotDFPlayerMini.h"     // thue viện phát loa
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial dfplay(7, 6);     // rx - tx
SoftwareSerial lora(5, 4);
SoftwareSerial node(9, 8);
DFRobotDFPlayerMini LOA;

int ngay, thang, nam, gio, phut, a, b, lap, t, vol;
int m, k, dem, dt, m0;
unsigned long tg, tg1, tg2;
int cb, last_cb, cb_n;
int t1 = 10000;   // tgian delay báo mức nước
int sett;
void setup() {
  Serial.begin(250000);
  dfplay.begin(9600);
  pinMode(2, OUTPUT);
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
}


void loop() {
  LORA();

}
///////////////////// CT nhận dữ liệu từ LORA//////////////////////
void LORA() {
  lora.begin(9600);
  DynamicJsonBuffer jsonBuffer(100);
  JsonObject& root = jsonBuffer.parseObject(lora);
  if (root == JsonObject::invalid())
    return;
  //  root.prettyPrintTo(Serial);
  int MUC1 = root["m1"];
  int MUC2 = root["m2"];
  int LUU_LUONG = root["l"];

  if (MUC1 == 1 && MUC2 == 0) {
    cb = 1;
  }
  else if (MUC1 == 1 && MUC2 == 1) {
    cb = 2;
  }
  else {
    cb = 0;
  }
  if (LUU_LUONG > 10.0) {                // lưu lượng > 10ml/s thì báo nc chảy xiết
    cb_n = 1;
  }
  else {
    cb_n = 0;     // 
  }
  if (millis() - tg2 > 2000) {
    node.begin(57600);
    node.println(String(cb) + String(cb_n));
    Serial.println(String(cb) + String(cb_n));
    tg2 = millis();
  }
  if (cb != 0 && cb_n == 1) {
    Serial.println("LOAD_4");
    LOAD_4();
  }
  else if (cb != 0 && cb_n == 0) {
    Serial.println("LOAD_2");
    LOAD_2();
  }
  else if (cb == 0 && cb_n == 1) {
    Serial.println("LOAD_3");
    LOAD_3();
  }
  if (cb == 0 && cb_n == 0) {
    Serial.println("LOAD_1");
    LOAD_1();
  }
}
void LOAD_4() {
  dfplay.begin(9600);
  VOL2();
  delay(2000);
  LOA.play(89);
  while (CHECK() == 0 ) {}
  delay(10000);

}
/////////////////////////Các CT phát thanh thwo cảnh báo/////////////////
void LOAD_3() {
  dfplay.begin(9600);
  LOA.play(89);
  while (CHECK() == 0 ) {}
  delay(t1);
}
void LOAD_2() {
  dfplay.begin(9600);
  VOL2();
  delay(t1);
}
DynamicJsonBuffer JsonNode(300);
void LOAD_1() {
  node.begin(57600);
  digitalWrite(2, 1);
  while (!node.available()) {}
  String N = node.readStringUntil('\r');
  if (N.length() > 20) {
 //   Serial.println(N.substring(0, 3));
    dem = 0;
    m = 1;
    String M = N;
    JsonObject& root1 = JsonNode.parseObject(M);
//    root1.printTo(Serial);
    ngay = root1["ng"]; // 15
    thang = root1["th"]; // 6
    nam = root1["n"]; // 2022            // tách chuỗi json từ node gửi sang
    gio  = root1["g"]; // 16             // và lưu vào các biến 
    phut  = root1["p"]; // 16
    a = root1["a"]; // 500
    b = root1["b"]; // 1000
    lap  = root1["l"]; // 1
    t = root1["t"]; // 10
    vol = root1["v"]; // 25
    digitalWrite(2, 0);
    IN1();
    LOA.volume(vol);
//    Serial.println("get done");
  }

  if (m == 1 && dem <= lap) {
    dfplay.begin(9600);
    delay(100);
    VOL1();  // phát 1 lần                   //phát thông báo theo các thông số 
    dem++;  // +1
    delay(t * 1000);
//    Serial.println("Phat xong lần " + (String)(dem));
    if (dem == lap) {
      m = 0;
//      Serial.println("Đã xong");
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
  if (gio == 0) {
    LOA.play(84);
    while (CHECK() == 0 ) {
    }

  }
  else {
    LOA.play(gio);      // 1 -> 23  // done
    while (CHECK() == 0 ) {
    }
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
