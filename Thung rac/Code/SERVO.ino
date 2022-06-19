void HUT() {
  Servo2(17, 1);
  digitalWrite(BOM, 1);
  digitalWrite(VAN, 0);
  Servo1(78, 17);
  Servo1(170, 10);
  Servo2(180, 2);
  delay(500);
  digitalWrite(VAN, 1);
  digitalWrite(BOM, 0);
  delay(200);
  digitalWrite(VAN, 0);
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
}

void NAP(int goc, int dl) {
  if (goc > S4) {
    for (S4; S4 <= goc; S4++) {
      SV4.write(S4);
      SV3.write(S4 + 12);
      delay(dl);
    }
  }
  if (goc < S4) {
    for (S4; S4 >= goc; S4--) {
      SV4.write(S4);
      SV3.write(S4 + 12);
      delay(dl);
    }
  }
}
