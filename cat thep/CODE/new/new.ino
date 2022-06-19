#define NUT1 digitalRead(6)
#define NUT2 digitalRead(5)
#define NUT3 digitalRead(4)
#define NUT4 digitalRead(3)
#define EN   digitalRead(2)
#define EP A0
#define LUOI A1
#define DC A3
#define CAT A4
#define CTAC A5
#define CB_KL A7

int l;
int bien;


void setup() {
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

}
void loop(){
  
}
int CAITHONGSO(int bien, int duoi, int tren) {
  if (NUT3 == 0) {
    delay(10);
    if (NUT3 == 0) {
      bien++;
      if (bien > tren) {
        bien = duoi;
      }
      delay(10);
      while (NUT3 == 0) {}
    }
  }
  if (NUT4 == 0) {
    delay(10);
    if (NUT4 == 0) {
      bien--;
      if (bien < duoi) {
        bien = tren;
      }
      delay(10);
      while(NUT4==0){}
    }
  }
  return bien;
}
void DEM() {
  int dem = 0;
  digitalWrite(EP, 0);
  digitalWrite(DC, 1);
  while (dem < l * 125) {
    while (EN == 1) {}
    while (EN == 0) {}
    dem++;
  }
  digitalWrite(DC, 0);
}
int KL() {
  int a = analogRead(CB_KL);
  if (a > 500) {
    a = 0;
  }
  else {
    a = 1;
  }
  return a;
}
