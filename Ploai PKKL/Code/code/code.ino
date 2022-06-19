#include<Servo.h>
#define hn 4
#define dc 3
Servo SV1;
Servo SV2;
Servo SV3;
Servo SV4;
int S1;
int S2;
int S3;
int S4;
int a = 0;
int b = 50;
int c = 70;
unsigned long tg1;
unsigned long tg2;
unsigned long tg3;

void setup() {
  Serial.begin(9600);
  SV1.attach(8);
  SV2.attach(7);
  SV3.attach(6);
  SV4.attach(5);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);


}
void loop() {
  Serial.print(a);
  Serial.print("  ");
  Serial.print(b);
  Serial.print("  ");
  Serial.println(c);
  if (digitalRead(9) == 0) {
    tg1 = millis();
    a++;
    if (digitalRead(9) == 1 && millis() - tg1 > 500) {
      a = 0;
    }
  }
  if (digitalRead(10) == 0) {
    tg2 = millis();
    b++;
    if (digitalRead(10) == 1 && millis() - tg2 > 500) {
      b = 0;
    }
  }
  if (digitalRead(11) == 0) {
    tg3 = millis();
    c++;
    if (digitalRead(10) == 1 && millis() - tg3 > 500) {
      c = 0;
    }
  }
  GAP();
  
}  

void GAP() {
    Servo2(100, 8);   // rá 1  0 76  147
  Servo3(97, 8);   //rá 2   0 107 88
  delay(100);
  Servo1(73, 8);   // gắp  70 100 100
  delay(1000);
  Servo4(145, 2);
}
void LEN1() {
  Servo1(0, 8);   // gắp  70 100 100
  Servo2(60, 8);   // rá 1  0 76  147
  Servo3(110, 8);   //rá 2   0 107 88
}
void LEN2() {
  Servo1(0, 3);   // gắp  70 100 100
  Servo2(60, 3);   // rá 1  0 76  147
  Servo3(110, 3);   //rá 2   0 107 88
}
void RA1() {
  Servo2(76, 3);   // rá 1  0 76  147
  Servo3(147, 3);   //rá 2   0 107 88
  Servo1(0, 3);   // gắp  70 100 100
  
  delay(1000);
  Servo4(90, 3);
}
void Servo1(int goc, int dl) {
  if (goc > S1) {
    for (S1; S1 <= goc; S1++) {
      SV1.write(S1);
      delay(dl);
    }
  }
  if (goc < S1) {
    for (S1; S1 >= goc; S1--) {
      SV1.write(S1);
      delay(dl);
    }
  }
  S1 = goc;
}
void Servo2(int goc, int dl) {
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
  S2 = goc;
}
void Servo3(int goc, int dl) {
  if (goc > S3) {
    for (S3; S3 <= goc; S3++) {
      SV3.write(S3);
      delay(dl);
    }
  }
  if (goc < S3) {
    for (S3; S3 >= goc; S3--) {
      SV3.write(S3);
      delay(dl);
    }
  }
  S3 = goc;
}
void Servo4(int goc, int dl) {
  if (goc > S4) {
    for (S4; S4 <= goc; S4++) {
      SV4.write(S4);
      delay(dl);
    }
  }
  if (goc < S4) {
    for (S4; S4 >= goc; S4--) {
      SV4.write(S4);
      delay(dl);
    }
  }
  S4 = goc;
}
