#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <FirebaseESP8266.h>
#define FIREBASE_HOST "app-iot-12c22-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "Vhwf8nMP87np6EX9w1MAeLGS4ux7bj8xhSywA1DZ"   
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(D3, DHT11);
#define K1 digitalRead(D7)
#define K2 digitalRead(D4)
#define QT digitalRead(D0)         // Quang trở
#define DAT analogRead(A0)
#define BOM D6
#define DEN D5
int b_status;
int d_status;
int h, t;
int as;
int dad;
int mode1 = 0;
int mode2 = 0;
int TDB, TDD;
int cb, last_cb, cd, last_cd;
int16_t i;

#define WIFI_SSID "Dungne"                      // TEN WIFI
#define WIFI_PASSWORD "12345678@"                // PASSWORD WIFI
FirebaseData fb;
unsigned long tg1, tg2;
ESP8266WebServer server(80);         // chon cong giao tiep la 80
String form;
void homepage()        ////TAO GIAO DIEN WEB
{
  form = " ";
  form += "<html>" ;
  form += "<head>";
  form += "<meta http-equiv='Content-Type' content='text/html' charset='UTF-8'/>";
  //    form += "<meta charset="UTF-8">";
  form += "<meta http-equiv='refresh' content='5;  url=/' >";
  form += "<title>Web IOT</title>";
  form += "<script>";


  form += "            function startTime() "; //lay thoi gian thuc
  form += "            {";
  form += "                var today = new Date();";

  form += "                var h = today.getHours();";
  form += "                var m = today.getMinutes();";
  form += "                var s = today.getSeconds();";

  form += "                m = checkTime(m);";
  form += "                s = checkTime(s);";

  form += "                document.getElementById('timer').innerHTML = h + ':' + m + ':' + s;";

  form += "                var t = setTimeout(function() {";
  form += "                    startTime();";
  form += "                }, 500);";
  form += "            }";

  form += "            function checkTime(i) ";
  form += "            {";
  form += "                if (i < 10) {";
  form += "                    i = '0' + i;";
  form += "                }";
  form += "                return i;";
  form += "            }";
  form += "        </script>";


  form += "</head>";

  form += "<style type = 'text/css'>";
  form += "body {background-color:black;";
  form += "          background-size:cover;";

  form += "}";
  form += "a { ";
  form += "display: inline-block;";
  form += " width: 32px;";
  form += " height: 32px;";
  form += "}";

  form += "h1 {";
  form += "  font: 4em normal Arial, Helvetica, sans-serif;";
  form += " padding: 3px;  margin: 0;";
  form += " text-align:center;";
  form += " color:yellow;";
  form += "}";
  form += "h2 {";
  form += " font: 2em normal Arial, Helvetica, sans-serif;";
  form += " padding: 3px;  margin: 0;";
  form += " text-align:center;";
  form += " color:cyan;";
  form += "}";
  form += "h3 {";
  form += " font: 2em normal Arial, Helvetica, sans-serif;"; //font chu
  form += " padding: 3px;  margin: 0;"; //kich thuoc chu
  form += " text-align:center;";
  form += " color:white;"; //mau chu
  form += "}";
  form += ".setting {width:960px; margin:0 auto; padding:30px; border:1px solid #333; color:#fff; }";
  form += "</style>";
  form += "<body background='https://i.pinimg.com/736x/08/ef/de/08efde7b8d918a1a23f6099f72a6d7fc.jpg' onload='startTime()' >"; //hien thi logo
  form += "<img src= 'https://upload.wikimedia.org/wikipedia/commons/4/42/Logo_%C4%90%E1%BA%A1i_h%E1%BB%8Dc_S%C6%B0_ph%E1%BA%A1m_K%E1%BB%B9_thu%E1%BA%ADt_%C4%90%C3%A0_N%E1%BA%B5ng.png' width='150' height='150'>";
  form += "  <p>";
  form += "  <center>";
  form += "  <h1>GIÁM SÁT VÀ ĐIỀU KHIỂN THIẾT BỊ</h1>"; //tieu de hien thi
  form += "  <h3>";

  //  form += "  <br>";
  //  form += "  CHE DO:     &nbsp  &nbsp  &nbsp"; if (flag_tt == false) {
  //    form += " TAY ";
  //  }
  //  else {
  //    form += " TU DONG ";
  //  }
  //  form += "  <br/>";

  form += "  <br>";
  form += "  TRẠNG THÁI BƠM:   &nbsp   &nbsp  &nbsp";
  if (b_status == 0) {
    form += " &nbsp   &nbsp  &nbsp &nbsp &nbsp TẮT &nbsp &nbsp &nbsp   &nbsp  &nbsp &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'http://icons.iconarchive.com/icons/iconsmind/outline/512/Light-Bulb-icon.png' width='55' height='55'> &nbsp  &nbsp  &nbsp ";
    form += "  <a href='./on1'><img src='https://icons.iconarchive.com/icons/hopstarter/soft-scraps/256/Button-Blank-Green-icon.png'width='60' height='60' /></a>";
  }
  else if (b_status == 1) {
    form += "  BẬT TỰ ĐỘNG &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'https://cdn3.iconfinder.com/data/icons/business-office/256/Business_Ideas-512.png' width='70' height='70'>&nbsp  &nbsp  &nbsp ";
    form += "  <a href='./on3'><img src='    https://icons.iconarchive.com/icons/hopstarter/soft-scraps/256/Button-Blank-Yellow-icon.png' width='60' height='60' /></a>";
  }
  else {
    form += "  BẬT THỦ CÔNG &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'https://cdn3.iconfinder.com/data/icons/business-office/256/Business_Ideas-512.png' width='55' height='55'>&nbsp  &nbsp  &nbsp ";
    form += "  <a href='./off1'> <img src='https://icons.iconarchive.com/icons/hopstarter/soft-scraps/256/Button-Blank-Red-icon.png' width='60' height='60' /></a>";

  }

  form += "  <br/>";

  form += "   <br>";
  form += "  TRẠNG THÁI ĐÈN:    &nbsp   &nbsp  &nbsp";
  if (d_status == 0) {
    form += " &nbsp   &nbsp  &nbsp &nbsp &nbsp TẮT &nbsp &nbsp &nbsp   &nbsp  &nbsp &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'http://icons.iconarchive.com/icons/iconsmind/outline/512/Light-Bulb-icon.png' width='55' height='55'> &nbsp  &nbsp  &nbsp ";
    form += "  <a href='./on2'><img src='https://icons.iconarchive.com/icons/hopstarter/soft-scraps/256/Button-Blank-Green-icon.png'width='60' height='60' /></a>";
  }
  else if (d_status == 1) {
    form += "  BẬT TỰ ĐỘNG &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'https://cdn3.iconfinder.com/data/icons/business-office/256/Business_Ideas-512.png' width='70' height='70'>&nbsp  &nbsp  &nbsp ";
    form += "  <a href='./on3'><img src='    https://icons.iconarchive.com/icons/hopstarter/soft-scraps/256/Button-Blank-Yellow-icon.png' width='60' height='60' /></a>";
  }
  else {
    form += "  BẬT THỦ CÔNG &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'https://cdn3.iconfinder.com/data/icons/business-office/256/Business_Ideas-512.png' width='55' height='55'>&nbsp  &nbsp  &nbsp ";
    form += "  <a href='./off2'> <img src='https://icons.iconarchive.com/icons/hopstarter/soft-scraps/256/Button-Blank-Red-icon.png' width='60' height='60' /></a>";

  }
  form += "  <br/>";

  form += "<h2>";
  form += " <br>";
  form += "  NHIỆT ĐỘ:";
  form += (String)t ;
  form += "<sup>o</sup>c   &nbsp  &nbsp  &nbsp  &nbsp ĐỘ ẨM: ";
  form += (String)h;
  form += "&nbsp  &nbsp  &nbsp  &nbsp ĐỘ ẨM ĐẤT: ";
  form += (String)dad;
  form += "%";
  form += "<br/>";
  form += "<br>";
  form += "<div id='timer'></div>";
  form += "<br/>";
  form += "</h2>";
  form += "  </center>";
  form += "</h3>";
  form += "</body>";
  form += "</html>";
}///ket thuc giao dien wep

void setup() {
  Serial.begin(9600);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
  pinMode(D0, INPUT); //dinh nghia ngo vao
  pinMode(BOM, OUTPUT); //dinh nghia ngo ra
  pinMode(DEN, OUTPUT);
  //   attachInterrupt(digitalPinToInterrupt(D4), NUT, FALLING);
  //  attachInterrupt(digitalPinToInterrupt(D7), NUT, FALLING);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);      // khởi động chế độ bắt wifi
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
  server.on("/", []() {
    homepage();
    server.send(200, "text/html", form);

  });


  server.on("/on1", []() {                        //HAM THUC HIEN KHI NHAN DUOC GIA TRI on1 tu web
    //  Serial.println("a");
    //    digitalWrite(BOM, 1);
    //    b_status = true;
    TDB = 1;
    homepage();
    server.send(200, "text/html", form);
  });


  server.on("/off1", []() {
    //  Serial.println("b");
    //    digitalWrite(BOM, 0);
    //    b_status = 0;
    TDB = 0;
    homepage();
    server.send(200, "text/html", form);
  });

  server.on("/on2", []() {
    //  Serial.println("c");
    //    digitalWrite(DEN, 1);
    //   d_status = true;
    TDD = 1;
    homepage();
    server.send(200, "text/html", form);
  });

  server.on("/off2", []() {
    //  Serial.println("d");
    //   digitalWrite(DEN, 0);
    //   d_status = false;
    TDD = 0;
    homepage();
    server.send(200, "text/html", form);
  });
  server.begin();
  Serial.println("Server on ");
  char result[16];
  sprintf(result, "%3d.%3d.%1d.%3d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);

  Serial.println(result);
  dht.begin();
  lcd.init();
  lcd.backlight();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  // khởi động thư viện firebase
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("DIA CHI IP WEB");
  lcd.setCursor(0, 1);
  lcd.print(result);         // In địa chỉ IP của mạng wifi kết nối đến
  delay(4000);
  lcd.clear();
}
void loop() {
  server.handleClient();
  GET_FB();
  CB();
  LOAD();
  NUT();
  LCD();
  if (millis() - tg2 > 1500) {
    SET_FB();
    tg2 = millis();
    //    Serial.println("b_status: " + String(b_status) + "   " + "d_status: " + String(d_status));
  }
}
void LCD() {
  lcd.setCursor(0, 0); lcd.print("t:");
  lcd.setCursor(5, 0); lcd.print("h:");
  lcd.setCursor(11, 0); lcd.print("D:");
  lcd.setCursor(0, 1); lcd.print("BOM:");
  lcd.setCursor(9, 1); lcd.print("DEN:");
  lcd.setCursor(2, 0);
  if (t < 10) {
    lcd.print(" ");
  }
  lcd.print(t);
  lcd.setCursor(7, 0);
  if (h < 10) {
    lcd.print(" ");
  }
  if (h < 100) {
    lcd.print(" ");
  }
  lcd.print(h);
  lcd.setCursor(13, 0);
  if (dad < 10) {
    lcd.print(" ");
  }
  if (dad < 100) {
    lcd.print(" ");
  }
  lcd.print(dad);
  lcd.setCursor(4, 1);
  if (b_status == 0) {
    lcd.print("OFF");
  }
  if (b_status == 1) {
    lcd.print("OnA");
  }
  if (b_status == 2) {
    lcd.print("OnM");
  }
    lcd.setCursor(13, 1);
  if (d_status == 0) {
    lcd.print("OFF");
  }
  if (d_status == 1) {
    lcd.print("OnA");
  }
  if (d_status == 2) {
    lcd.print("OnM");
  }
}
void LOAD() {
  if (TDB == 0) {
    //   Serial.println("Bơm Tự động");
    if (dad < 30 && t < 34) {
      digitalWrite(BOM, 1);
      b_status = 1;
    }
    if (dad > 40) {
      digitalWrite(BOM, 0);
      b_status = 0;
    }
  }
  else {
    //   Serial.println("Bật bơm cưỡng bức");
    digitalWrite(BOM, 1);
    b_status = 2;
  }
  if (TDD == 0) {
    //  Serial.println("Đèn tự động");
    if (QT == 1) {
      digitalWrite(DEN, 1);
      d_status = 1;
    }
    else {
      //    Serial.println("Bật đèn cưỡng bức");
      digitalWrite(DEN, 0);
      d_status = 0;
    }
  }
  else {
    digitalWrite(DEN, 1);
    d_status = 2;
  }
}
void SET_FB() {
  Firebase.setInt(fb, "DATA/b", b_status);
  Firebase.setInt(fb, "DATA/d", d_status);
  Firebase.setInt(fb, "DATA/dad", dad);
  Firebase.setInt(fb, "DATA/t", t);
  Firebase.setInt(fb, "DATA/h", h);

}
void NUT() {
  //  if (micros() - tg1 > 150000) {
  if (K1 == 0) {
    TDB = !TDB;
    while (K1 == 0) {}
  }
  if (K2 == 0) {
    TDD = !TDD;
    while (K2 == 0) {}
  }
  //  }
}
void GET_FB() {
  last_cb = cb; last_cd = cd;
  Firebase.getString(fb, "DATA/cb");
  cb = fb.stringData().toInt();
  // TDB = cb;
  Firebase.getString(fb, "DATA/cd");
  cd = fb.stringData().toInt();
  //  TDD = cd;
  if (cb - last_cb == 1) {
    TDB = 1;
  }
  if (cb - last_cb == -1) {
    TDB = 0;
  }  if (cd - last_cd == 1) {
    TDD = 1;
  }
  if (cd - last_cd == -1) {
    TDD = 0;
  }

}
void CB() {
  dad = map(DAT, 490, 1023, 100, 0);
  if (dad > 100) dad = 100;
  h = dht.readHumidity();
  t = dht.readTemperature();


}
