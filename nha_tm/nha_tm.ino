#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "Hx3actC61IV_jdo8M5E4eKN2Tpic_LUl";
char ssid[] = "Ku";
char pass[] = "1234567890";
// bien toan cuc

//DHT dht(D2, DHTTYPE);
String inputString = "";
String chuoiSo = "";

int xongChuoi = 0;
int demBit = 0;
int sensorData = 0;
int nhietdo = 0;
int kytuSo(String a);
BlynkTimer timer;
// nut nhan
BLYNK_WRITE(V7) //Button Widget is writing to pin V1
{
  int pinV7 = param.asInt();
  if (pinV7 == 1)
  {
    Serial.println('A');
  }


}
BLYNK_WRITE(V8) //Button Widget is writing to pin V1
{
  int pinV8 = param.asInt();
  if (pinV8)
  {
    Serial.println('B');
  }

}
BLYNK_WRITE(V9) //Button Widget is writing to pin V1
{
  int pinV9 = param.asInt();
  if (pinV9)
  {
    Serial.println('C');
  }

}
BLYNK_READ(V5) //nhietdo
{
  if (xongChuoi == 1)
  {
    chuoiSo = "";
    chuoiSo = inputString;
    inputString = "";
    xongChuoi = 0;
  }


  sensorData = kytuSo(chuoiSo[0]) * 10 + kytuSo(chuoiSo[1]);
  //int sensorData = analogRead(A0);
  Blynk.virtualWrite(V5, sensorData);
  //Serial.println(chuoiSo);


}
BLYNK_READ(V6) //khi gas
{

  int gas = kytuSo(chuoiSo[2]);
  Blynk.virtualWrite(V6, gas);
  //Serial.println(sensorData);

}
BLYNK_CONNECTED() {
  // Request Blynk server to re-send latest values for all pins
  Blynk.syncAll();

  // You can also update individual virtual pins like this:
  //Blynk.syncVirtual(V0, V2);

  // Let's write your hardware uptime to Virtual Pin 2
  int value = millis() / 1000;
  //Blynk.virtualWrite(V2, value);
}
WidgetLED led2(V2), led3(V3); //register to virtual pin 1
void blinkLedWidget()
{
  if (kytuSo(chuoiSo[3]) == 1)
  {
    //led1.setValue(255);
    Blynk.virtualWrite(V7, HIGH);
  }
  else
  {
    //led1.setValue(0);
    Blynk.virtualWrite(V7, LOW);
  }
  if (kytuSo(chuoiSo[4]) == 1)
  {
    // led2.setValue(255);
    Blynk.virtualWrite(V8, HIGH);
  }
  else
  {
    //led2.setValue(0);
    Blynk.virtualWrite(V8, LOW);
  }
  if (kytuSo(chuoiSo[5]) == 1)
  {
    //led3.setValue(255);
    Blynk.virtualWrite(V9, HIGH);
  }
  else
  {
    //led3.setValue(0);
    Blynk.virtualWrite(V9, LOW);
  }

}
WidgetTerminal terminal(V1);

void setup()
{
  // Debug console
  Serial.begin(115200);

  inputString.reserve(200);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(1000L, blinkLedWidget);
  terminal.clear();

  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server

  terminal.println(F("              DO AN TOT NGHIEP"));
  terminal.println(F(" "));
  terminal.println(F("SVTH: "));
  terminal.println(F("        Nguyen Duc Thang"));
  terminal.println(F("        Dang Duc Huong"));
  terminal.println(F("        Duong The Hoa"));
  terminal.println(F("GVHD: "));
  terminal.println(F("        Tran Van Chinh "));
  terminal.flush();
}

void loop()
{
  Blynk.run();
  timer.run();
  if (Serial.available()) {
    //Serial.write(Serial.read());
    char inChar = (char)Serial.read();
    inputString += inChar;
    demBit += 1;
    if (demBit == 6)
    {
      demBit = 0;
      xongChuoi = 1;

    }
  }
}


int kytuSo(char a)
{
  if (a == '0')
  {
    return 0;
  }
  else if (a == '1')
  {
    return 1;
  }
  else if (a == '2')
  {
    return 2;
  }
  else if (a == '3')
  {
    return 3;
  }
  else if (a == '4')
  {
    return 4;
  }
  else if (a == '5')
  {
    return 5;
  }
  else if (a == '6')
  {
    return 6;
  }
  else if (a == '7')
  {
    return 7;
  }
  else if (a == '8')
  {
    return 8;
  }
  else if (a == '9')
  {
    return 9;
  }
}
