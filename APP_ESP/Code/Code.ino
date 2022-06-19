#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "DHT.h" //thu vien dht
#define DHTPIN D3     // what pin we're connected t
#define DHTTYPE DHT11   // DHT 11 

#define k1    D7
#define k2    D4
#define cbas D0 //ngo vao cam bien
#define bom D6 //ngo ra dk 3 thiet bi
#define den D5
#define SSID "Teaffee_43 NgôThìNhậm"      // TEN WIFI
#define PASS "01234568910"               // PASSWORD WIFI
//#define SSID "OANH VU"                 // TEN WIFI
//#define PASS "bat3gdiem"               // PASSWORD WIFI
int16_t i;
boolean status1 = false; // bien trang thai
boolean status2 = false;
boolean statusBom = false;
bool flag_tt = 1;
bool stateK1 = 1;
bool stateK2 = 1;
int nhietdo, doam, doAmDat;
unsigned long time_delay;
unsigned int h;
unsigned int t;
void NutNhan();
ESP8266WebServer server(80);         // chon cong giao tiep la 80, xem thêm ở google
long period;
int offset = 1, refresh = 0;
DHT dht(DHTPIN, DHTTYPE);
// ******************* String form to sent to the client-browser ************************************
String form;
void homepage()        ////TAO GIAO DIEN WEB
{
  form = " ";
  form += "<html>" ;
  form += "<head>";
  form += "<meta http-equiv='refresh' content='5;  url=/' >";
  form += "<title>WIFI CONTROLLER</title>";
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
  form += "  <h2>GIAM SAT VA DIEU KHIEN THIET BI</h2>"; //tieu de hien thi
  form += "  <h3>";

  form += "  <br>";
  form += "  CHE DO:     &nbsp  &nbsp  &nbsp"; if (flag_tt == false) {
    form += " TAY ";
  }
  else {
    form += " TU DONG ";
  }
  form += "  <br/>";
  
  form += "  <br>";
  form += "  BOM:     &nbsp  &nbsp  &nbsp"; if (status1 == false) {
    form += "   TINH TRANG: OFF &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'http://icons.iconarchive.com/icons/iconsmind/outline/512/Light-Bulb-icon.png' width='40' height='40'> &nbsp  &nbsp  &nbsp ";
  }
  else {
    form += "  TINH TRANG: ON &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'https://cdn3.iconfinder.com/data/icons/business-office/256/Business_Ideas-512.png' width='40' height='40'>&nbsp  &nbsp  &nbsp ";
  }
  form += "  <a href='./on1'><input type='submit' value='ON' ></a> &nbsp";
  form += "  <a href='./off1'><input type='submit' value='OFF'></a>";
  form += "  <br/>";

  form += "   <br>";
  form += "  DEN:    &nbsp   &nbsp  &nbsp"; if (status2 == false) {
    form += "   TINH TRANG: OFF &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'http://icons.iconarchive.com/icons/iconsmind/outline/512/Light-Bulb-icon.png' width='40' height='40'> &nbsp  &nbsp  &nbsp ";
  }
  else {
    form += "  TINH TRANG: ON &nbsp  &nbsp  &nbsp ";
    form += "<img src= 'https://cdn3.iconfinder.com/data/icons/business-office/256/Business_Ideas-512.png' width='40' height='40'>&nbsp  &nbsp  &nbsp ";
  }
  form += "  <a href='./on2'><input type='submit' value='ON' ></a> &nbsp";
  form += "  <a href='./off2'><input type='submit' value='OFF'></a>";
  form += "  <br/>";

  form += "<h2>";
  form += " <br>";
  form += "  NHIET DO:"; form += (String)nhietdo ;
  form += "<sup>o</sup>c   &nbsp  &nbsp  &nbsp  &nbsp DO AM: "; form += (String)doam;
  form += "&nbsp  &nbsp  &nbsp  &nbsp DO AM DAT: "; form += (String)doAmDat;
  form += "%";
  form += "<br/>";
  form += "<br>";
  form += "        <div id='timer'></div>";
  form += "<br/>";
  form += "</h2>";
  form += "  </center>";
  form += "</h3>";
  form += "</body>";
  form += "</html>";
}///ket thuc giao dien wep

void setup(void) {
  pinMode(k1, INPUT_PULLUP);
  pinMode(k2, INPUT_PULLUP);
  pinMode(cbas, INPUT); //dinh nghia ngo vao
  pinMode(bom, OUTPUT); //dinh nghia ngo ra
  pinMode(den, OUTPUT);
  digitalWrite(bom, 0); //tat het ngo ra
  digitalWrite(den, 0);

  //ESP.wdtDisable();                            // used to debug, disable wachdog timer,
  Serial.begin(9600);                           // full speed to monitor
  WiFi.begin(SSID, PASS);                      // Connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {     // Wait for connection
    delay(500);
    Serial.print(".");
  }
  // Set up the endpoints for HTTP server,  Endpoints can be written as inline functions:

  server.on("/", []() {
    homepage();
    server.send(200, "text/html", form);

  });


  server.on("/on1", []() {                        //HAM THUC HIEN KHI NHAN DUOC GIA TRI on1 tu web
    //  Serial.println("a");
    digitalWrite(bom, 1);
    status1 = true;
    homepage();
    server.send(200, "text/html", form);
  });


  server.on("/off1", []() {
    //  Serial.println("b");
    digitalWrite(bom, 0);
    status1 = false;
    homepage();
    server.send(200, "text/html", form);
  });

  server.on("/on2", []() {
    //  Serial.println("c");
    digitalWrite(den, 1);
    status2 = true;
    homepage();
    server.send(200, "text/html", form);
  });

  server.on("/off2", []() {
    //  Serial.println("d");
    digitalWrite(den, 0);
    status2 = false;
    homepage();
    server.send(200, "text/html", form);
  });
Serial.println("Server on ");
  dht.begin();
  server.begin();                                 // Start the server
  lcd.init();
  lcd.backlight();
  //Serial.print("SSID : ");                        // prints SSID in monitor
  //Serial.println(SSID);                           // to monitor

  char result[16];
  sprintf(result, "%3d.%3d.%1d.%3d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  //Serial.println();
  //Serial.println(result);
  //Serial.println("WebServer ready!   ");
  //Serial.println(WiFi.localIP()); 
  // Serial monitor prints localIP
  lcd.setCursor(0, 0);
  lcd.print("DIA CHI IP WEB");
  lcd.setCursor(0, 1);
  lcd.print(result); 				// In địa chỉ IP của mạng wifi kết nối đến
  time_delay = millis();
  delay(4000);
  lcd.clear();
}

void loop(void) {
  server.handleClient();
  if (millis() - time_delay > 1000) {
    sendSensor();
    //NutNhan();
    time_delay = millis();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");   // ham bao khi sensor k hoat dong
    } else {
      doam = (int)h;
      nhietdo = (int)t;
    }
  }
}

/*================================================================*/
void sendSensor()
{
  lcd.clear();
  //lcd_blynk.clear();
  int value = analogRead(A0);     // Ta sẽ đọc giá trị hiệu điện thế của cảm biến
  doAmDat = map(value, 470, 1024, 100, 0);
  if (doAmDat > 99) {
    doAmDat = 99;
  }
  h = dht.readHumidity();     //Doc gia tri do am
  t = dht.readTemperature();  //Doc gia tri nhiet do

  lcd.setCursor(0, 0);
  lcd.print("ND:");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(8, 0);
  lcd.print("DA:");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("DAD:");
  lcd.print(doAmDat);
  lcd.print("%");
  //Serial.println(doAmDat);

  if (flag_tt == 0) {
    lcd.setCursor(15, 0);
    lcd.print("M");
  }
  if (flag_tt == 1) {
    lcd.setCursor(15, 0);
    lcd.print("A");
  }
  if (digitalRead(bom) == 1) {
    lcd.setCursor(9, 1); lcd.print("BOM MO ");
    status1 = 1;
  }
  if (digitalRead(bom) == 0) {
    lcd.setCursor(9, 1); lcd.print("BOM TAT");
    status1 = 0;
  }
  // đoạn chương trình chọn chế độ chạy tự động hay bằng tay
  switch (flag_tt)
  {
    case 0:
      NutNhan();
      lcd.setCursor(15, 0); lcd.print("M");
      if (!digitalRead(k2)) {
        while (!digitalRead(k2));
        stateK2 = !stateK2;
        digitalWrite(bom, stateK2);
        if (stateK2 == 0) {
          digitalWrite(bom, 0);
        }
        if (stateK2 == 1) {
          digitalWrite(bom, 1);
        }
      }
      break;
    case 1:
      NutNhan();
      lcd.setCursor(15, 0); lcd.print("A");
      if (doAmDat < 20 || t < 34) {

        digitalWrite(bom, HIGH);
      }
      if (doAmDat > 80) {
        digitalWrite(bom, LOW);
      }

      if (digitalRead(cbas) == 1) {
        status2 = true;
        digitalWrite(den, 1);
      } else {
        status2 = false;
        digitalWrite(den, 0);
      }
      break;
  }
}
/*================================================================*/
void NutNhan()// chương trình gọi nút  nhấn chọn chế độ bằng tay hay tự động
{
  if (!digitalRead(k1)) {
    while (!digitalRead(k1));
    stateK1 = !stateK1;
    flag_tt = stateK1;
  }
}
