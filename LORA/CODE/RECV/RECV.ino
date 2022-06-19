#include <ESP8266WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include "ThingSpeak.h"
#include <ArduinoJson.h>

#define ss 15
#define rst 16
#define dio0 4
#define WIFI_SSID "OANH VU"
#define WIFI_PASSWORD "bat3gdiem"

String json = "";
int t ;
int p ;
int l ;
int m ;
unsigned long myChannelNumber = 1742501;
const char * myWriteAPIKey = "4GJQKD0R2RGLMI5G";
String myStatus = "";
WiFiClient  client;
void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);         //khởi động esp chạy ở chế độ bắt wifi
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {       // hàm kiểm tra esp cps kết nối wifi chưa
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());
  while (!Serial);
  LoRa.setPins(ss, rst, dio0);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  ThingSpeak.begin(client);   // Initialize ThingSpeak
}
void loop() {
  LORA();
 // THINGSP();
}
void THINGSP() {
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, p);
  ThingSpeak.setField(3, l);
  ThingSpeak.setField(4, m);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    Serial.println("Channel update successful.");
  }
  else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(15000);
}
void LORA() {
  if (LoRa.parsePacket()) {
    if (LoRa.available()) {
      json = LoRa.readStringUntil('\r');
    }
    DynamicJsonBuffer jsonBuffer(120);
    JsonObject& root = jsonBuffer.parseObject(json);
    //     root.printTo(Serial);
    m = root["m"];
    t = root["t"];
    p = root["p"];
    l = root["l"];
    THINGSP();
  }
//      Serial.print(String(m) + "  ");
//    Serial.print(String(t) + "  ");
//    Serial.print(String(p) + "  ");
//    Serial.println(String(l));
}
