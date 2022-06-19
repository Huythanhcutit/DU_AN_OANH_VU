
#include<Servo.h>
#define hn digitalRead(4)
#define dc 3
#define kl digitalRead(A5)
#define nut1 digitalRead(9)
#define nut2 digitalRead(10)
Servo SV1;
Servo SV2;
Servo SV3;
Servo SV4;
Servo SV5;
int S1 = 90;
int S2 = 90;
int S3 = 90;
int S4 = 90;
int S5 = 140;
int bien = 0;
int KL = 0;
int PK = 0;
String G = "";
int mode = 0;
int k=0;
void setup() {
  Serial.begin(9600);
  SV1.attach(8);
  SV2.attach(7);
  SV3.attach(6);
  SV4.attach(5);
  SV5.attach(A4);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  while (mode == 0) {
    if (nut1 == 0) {
      mode = 1;
      digitalWrite(dc, 1);
    }
  }
}
void loop() {
  STOP();
  CHO();
  digitalWrite(dc, 1);
  CAPPHOI();
  while (hn == 1) {
    if (kl == 0) {
      bien = 1;
    }
    STOP();
  }
  while (hn == 0) {STOP();}
  digitalWrite(dc, 0);
  STOP();
  // Serial.println(bien);
  if (bien == 1) {
    GAP();
    NHA1();
    KL++;
  }
  else {
    GAP();
    NHA2();
    PK++;
  }
  G = "";
  if (KL < 100) {
    G += '0';
  }
  if (KL < 10) {
    G += '0';
  }
  G += String(KL);
  if (PK < 100) {
    G += '0';
  }
  if (PK < 10) {
    G += '0';
  }
  G += String(PK);
  Serial.println(G);
  bien = 0;
}
void STOP() {
  if (nut2 == 0) {
    mode = 0;
    while (mode == 0) {
      if (digitalRead(dc)==1){
        digitalWrite(dc,0);
        k=1;
      }
    if (nut1 == 0) {
      mode = 1;
    }
    }
   if(k==1){
    digitalWrite(dc,1);
    k=0;
    }
  }
}
void NHA2() {
  Servo2(60, 10);   // rá 1  0 76  147
  Servo3(155, 10);   //rá 2   0 107 88
  Servo1(0, 10);
  Servo3(88, 10);   //rá 2   0 107 88
  Servo2(100, 10);   // rá 1  0 76  147
  delay(500);
  Servo4(70, 3);
}

void NHA1() {
  Servo2(60, 10);   // rá 1  0 76  147
  Servo3(155, 10);   //rá 2   0 107 88
  Servo1(0, 10);
  Servo2(76, 10);   // rá 1  0 76  147
  Servo3(155, 10);   //rá 2   0 107 88
  delay(500);
  Servo4(70, 3);
}
void CAPPHOI() {
  Servo5(70, 15);
  delay(500);
  SV5.write(140);
}
void CHO() {
  Servo4(70, 5);
  Servo2(71, 20);
  Servo3(129, 20);
  Servo1(70, 20);
  delay(500);
  Servo4(70, 5);

}
void GAP() {
  Servo4(70, 5);
  Servo1(70, 20);
  Servo2(71, 20);
  Servo3(129, 20);
  Servo2(82, 20);
  Servo3(110, 20);
  Servo2(95, 20);
  Servo3(100, 20);
  Servo2(103, 20);
  Servo2(106, 20);
  Servo3(95, 20);
  delay(500);
  Servo4(147, 5);
  delay(200);

}
void Servo1(int goc, int dl) {
  if (goc > S1) {
    for (S1; S1 <= goc; S1++) {
      SV1.write(S1);
      delay(dl);
      STOP();
    }
  }
  if (goc < S1) {
    for (S1; S1 >= goc; S1--) {
      SV1.write(S1);
      delay(dl);
      STOP();
    }
  }
}
void Servo2(int goc, int dl) {
  if (goc > S2) {
    for (S2; S2 <= goc; S2++) {
      SV2.write(S2);
      delay(dl);
    STOP();
    }
  }
  if (goc < S2) {
    for (S2; S2 >= goc; S2--) {
      SV2.write(S2);
      delay(dl);
      STOP();
    }
  }
}
void Servo3(int goc, int dl) {
  if (goc > S3) {
    for (S3; S3 <= goc; S3++) {
      SV3.write(S3);
      delay(dl);
      STOP();
    }
  }
  if (goc < S3) {
    for (S3; S3 >= goc; S3--) {
      SV3.write(S3);
      delay(dl);
      STOP();
    }
  }
}
void Servo4(int goc, int dl) {
  if (goc > S4) {
    for (S4; S4 <= goc; S4++) {
      SV4.write(S4);
      delay(dl);
      STOP();
    }
  }
  if (goc < S4) {
    for (S4; S4 >= goc; S4--) {
      SV4.write(S4);
      delay(dl);
      STOP();
    }
  }

}

void Servo5(int goc, int dl) {
  if (goc > S5) {
    for (S5; S5 <= goc; S5++) {
      SV5.write(S5);
      delay(dl);
      STOP();
    }
  }
  if (goc < S5) {
    for (S5; S5 >= goc; S5--) {
      SV5.write(S5);
      delay(dl);
      STOP();
    }
  }
}
