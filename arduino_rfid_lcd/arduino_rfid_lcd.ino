/*
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SDA: Pin 10
* RST: Pin 9
*/
#include <SoftwareSerial.h>
#include <SPI.h>
#include <RFID.h>
 
#define SS_PIN 10
#define RST_PIN 9
 
RFID rfid(SS_PIN, RST_PIN);
SoftwareSerial  MySerial(2,3);
 
// Setup variables:
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;
 
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  MySerial.begin(9600);
//  Serial.println("Phan Quoc Viet");
//  Serial.println("Please swipe the card :");
}
 
void loop()
{
 
    if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
    serNum0 = rfid.serNum[0];
    serNum1 = rfid.serNum[1];
    serNum2 = rfid.serNum[2];
    serNum3 = rfid.serNum[3];
    serNum4 = rfid.serNum[4];
     
//    Serial.println("Your UID is : ");
    Serial.print(rfid.serNum[0],DEC);
    Serial.print("-");
    Serial.print(rfid.serNum[1],DEC);
    Serial.print("-");
    Serial.print(rfid.serNum[2],DEC);
    Serial.print("-");
    Serial.print(rfid.serNum[3],DEC);
    Serial.print("-");
    Serial.print(rfid.serNum[4],DEC);
    Serial.println();
          }
    }
 
    rfid.halt();
    if(Serial.available()>0)
    {
          char a = Serial.read();
          Serial.write(a);
          MySerial.write(a);
    }
//    delay(200);   
}
