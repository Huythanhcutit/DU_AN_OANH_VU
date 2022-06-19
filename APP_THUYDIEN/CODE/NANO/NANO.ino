#include <ArduinoJson.h>    // thư viện json
#include <SoftwareSerial.h>
SoftwareSerial lora(5, 4);

#define cbS401 2                                  // Cảm biến lưu lượng nước S401
#define MUC1 1 - digitalRead(A0)                  // Khai báo-Đảo mức logic của cảm biến
#define MUC2 1 - digitalRead(A1)
float LUU_LUONG;
unsigned long xung, tg, tg1;

DynamicJsonBuffer jsonBuffer(80);                      // Khai báo vùng nhớ để chứa chuỗi json
JsonObject& root = jsonBuffer.createObject();          // Tạo chuỗi json root
void setup() {
  Serial.begin(115200);         // khởi taỌ cổng serial 
  lora.begin(9600);             // khoiwrr tạo cổng uart kết nối với lora
  pinMode(2, INPUT);
  attachInterrupt(0, DEM_XUNG, FALLING);
}
void loop() {
  if (millis() % 2000 < 1000) {     // ĐO lưu lượng mỗi lần 1s
    
    DO_LUU_LUONG();
  }
  else {
    for(int i = 0;i<=3;i++){       // cứ mỗi lần cảnh báo, gửi dữ liệu đi 4 lần
    SEND();
    xung = 0;  
  }
  LUU_LUONG = 0;
  }
}
void SEND() {
  root["m1"] = MUC1;
  root["m2"] = MUC2;
  root["l"] = LUU_LUONG;
  if (millis() - tg1 > 2500){     // sau 2.5s gửi đi 1 lần
  root.printTo(Serial);
  root.printTo(lora); // gửi
    Serial.println();
    tg1 = millis();
  }
}
void DO_LUU_LUONG() {
  if (xung > 0) {
    LUU_LUONG = 1000 * xung / 98.0 / 60.0;  // CT tính lưu lượng - đơn vị mL/s
//    Serial.println(LUU_LUONG);
  }
}
void DEM_XUNG() {
  xung ++;
  //  Serial.println(xung);
}
