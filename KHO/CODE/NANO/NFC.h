//#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h> // thu vien "RFID".

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long MASO, uidDecTemp; // hien thi so UID dang thap phan
byte bCounter, readBit;
unsigned long ticketNumber;

void SETUP_NFC(){
  SPI.begin();
  mfrc522.PCD_Init();
//  Serial.println("Prilozhite kartu / Waiting for card...");
  }
