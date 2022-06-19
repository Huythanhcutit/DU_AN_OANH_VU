#include <ArduinoJson.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>     // bmp 0x76     bh1750 0x23
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <BH1750.h>
#define MUA 1 - digitalRead(A3)
BH1750 lightMeter(0x23);
Adafruit_BMP280 bmp; // I2C
int counter = 0;
float t, p, l;
String json;
unsigned long tg;
DynamicJsonBuffer jsonBuffer(100);
JsonObject& root = jsonBuffer.createObject();
void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  while (!bmp.begin(0x76, 0x58)) {
    Serial.println("Not Connect BMP");
    delay(500);
  }
  lightMeter.begin();
  Serial.println(F("BH1750 Test"));
}
void loop() {
  BMP();
  BH();
  LORA();
}
void BH() {
  l = lightMeter.readLightLevel();
}
void BMP() {
  t = bmp.readTemperature();
  p = bmp.readPressure();

}
void LORA() {
  root["m"] = MUA;
  root["t"] = t;
  root["p"] = p;
  root["l"] = l;
  if (millis() - tg > 3000) {
    LoRa.beginPacket();
    root.printTo(LoRa);
    LoRa.endPacket();
    root.printTo(Serial);
    Serial.println();
    tg = millis();
  }

}
