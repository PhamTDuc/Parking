#include <SoftwareSerial.h>
#include <SPI.h>
#include <RFID.h>
 
#define SS_PIN 10
#define RST_PIN 9

SoftwareSerial mySerial(2, 3); // RX, TX
RFID rfid(SS_PIN, RST_PIN);

 int serNum0;
 int serNum1;
 int serNum2;
int serNum3;
int serNum4;
 
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
//  Serial.println("Phan Quoc Viet");
//  Serial.println("Please swipe the card :");
mySerial.begin(9600);
}
 
void loop()
{
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) 
    {
    serNum0 = rfid.serNum[0];
    serNum1 = rfid.serNum[1];
    serNum2 = rfid.serNum[2];
    serNum3 = rfid.serNum[3];
    serNum4 = rfid.serNum[4];
     
//    Serial.println("Your UID is : ");
    Serial.print(rfid.serNum[0],DEC);
    Serial.print(',');
    mySerial.write(rfid.serNum[0]);
    Serial.print(rfid.serNum[1],DEC);
    Serial.print(rfid.serNum[2],DEC);
    Serial.print(rfid.serNum[3],DEC);
    Serial.print(rfid.serNum[4],DEC);
    Serial.println();
    delay(50);
    }
    }
 
    rfid.halt();
  
  
  
  if(Serial.available() > 0){
    Serial.println("Vi tri (0 -> 4): ");
    while(Serial.available() > 0) {// in hết nội dung mà máy tính gửi cho mình, đồng thời gửi cho arduino thứ 2 
    char ch = Serial.read(); //đọc ký tự đầu tiên trogn buffe
    Serial.write(ch); //xuất ra monitor máy tín
    mySerial.write(ch); //gửi dữ liệu cho Arduino thứ 
    }
    Serial.println();
    }
 
}
