int S = 90;
Servo CUA;
void SV(int goc, int dl) {    // ct điều khiển servo
  if (goc > S) {
    for (S; S <= goc; S++) {
      CUA.write(S);
      delay(dl);
    }
  }
  if (goc < S) {
    for (S; S >= goc; S--) {
      CUA.write(S);
      delay(dl);
    }
  }
}
