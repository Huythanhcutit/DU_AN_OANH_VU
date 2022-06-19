#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>

Adafruit_BMP280 bmp; // I2C

void setup()
{
  delay(2000);
  Serial.begin(9600);

  while(!bmp.begin(0x76,0x58)) {
    Serial.println("Not Connect BMP");
    delay(500);
  }
}

void loop()
{
  Serial.println("Temperature: " + String(bmp.readTemperature()) + "*C");
  Serial.println("Pressure: " + String(bmp.readPressure()) + "Pa");
  Serial.println("Approx Altitude: " + String(bmp.readAltitude()) + "m");
  Serial.println("----------------------------------------");
  delay(4000);
}
