#include <Servo.h>            // Khai báo thư viện servo
Servo SV1;
Servo SV2;
int S1 = 90;
int S2 = 90;
void SETUP_SV() {
  SV1.attach(6);   // cửa chính
  SV2.attach(7);    // cửa sổ
  SV1.write(138);
  SV2.write(110);
  
}
void Servo2(int goc, int dl) {    // ct điều khiển servo
  if (goc > S2) {
    for (S2; S2 <= goc; S2++) {
      SV2.write(S2);
      delay(dl);
    }
  }
  if (goc < S2) {
    for (S2; S2 >= goc; S2--) {
      SV2.write(S2);
      delay(dl);
    }
  }
}
void Servo1(int goc, int dl) {
  if (goc > S1) {
    for (S1; S1 <= goc; S1++) {
      SV1.write(S1);
      delay(dl);
    }
  }                                     //  ct điều khiển servo 
  if (goc < S1) {
    for (S1; S1 >= goc; S1--) {
      SV1.write(S1);
      delay(dl);
    }
  }
}
