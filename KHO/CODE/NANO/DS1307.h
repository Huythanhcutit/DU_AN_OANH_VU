// Khai báo thư viện I2C
#include <Wire.h>
const byte DS1307 = 0x68;
/* khai báo các biến thời gian */
int giay , phut, gio, ngay, thu, thang, nam;

/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int bcd2dec(byte num)
{
  return ((num/16 * 10) + (num % 16));
}
/* Chuyển từ Decimal sang BCD */
int dec2bcd(byte num)
{
  return ((num/10 * 16) + (num % 10));
}
// doc thoi gian tu ds1307
void READDS1307()
{
  Wire.beginTransmission(DS1307);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);

  giay = bcd2dec(Wire.read() & 0x7f);
  phut = bcd2dec(Wire.read() );
  gio  = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
  thu  = bcd2dec(Wire.read() );
  ngay = bcd2dec(Wire.read() );
  thang= bcd2dec(Wire.read() );
  nam  = bcd2dec(Wire.read() );
  nam += 2000;    
}

/* cài đặt thời gian cho DS1307 */
void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr)
{
  yr=yr-2000;
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00)); // đặt lại pointer
  Wire.write(dec2bcd(sec));
  Wire.write(dec2bcd(min));
  Wire.write(dec2bcd(hr));
  Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
  Wire.write(dec2bcd(d)); 
  Wire.write(dec2bcd(mth));
  Wire.write(dec2bcd(yr));
  Wire.endTransmission();
  Serial.println("SetTime finish");
}
