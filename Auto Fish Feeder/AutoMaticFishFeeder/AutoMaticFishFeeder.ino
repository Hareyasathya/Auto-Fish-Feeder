#include <Wire.h>
#include <EEPROM.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;
int pos = 0; 
#define relay 7
#define btn1 6 
#define btn2 5 
#define btn3 4 
#define btn4 2


LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
RTC_DS1307 RTC;
int starthr=0,startmin=0,offhr=0,offmin=0;
int HOUR,MINUT,SECOND,DAY,MONTH,YEAR;

byte Aalpha[8] ={  0b01110,
                   0b10001,
                   0b11111,
                   0b10001,
                   0b10001,
                   0b00000,
                   0b00000,
                   0b00000
                  };
 byte Malpha[8] ={ 0b10001,
                   0b11011,
                   0b10101,
                   0b10001,
                   0b10001,
                   0b00000,
                   0b00000,
                   0b00000
                   };                                      
 byte Palpha[8]={  0b11100,
                   0b10010,
                   0b11100,
                   0b10000,
                   0b10000,
                   0b00000,
                   0b00000,
                   0b00000
                   };

void setup() {
  // Masukkan kode BTN3up di sini, untuk dijalankan sekali:
   Wire.begin();
   RTC.begin();
   lcd.begin(16,2);
   Serial.begin(9600);
   myservo.attach(3);
   //myservo.write(45); 
   pinMode(btn1, INPUT);
   pinMode(btn2, INPUT);
   pinMode(btn3, INPUT);
   pinMode(btn4, INPUT);
   pinMode(relay, OUTPUT);
   digitalWrite(relay,LOW); 
   lcd.setCursor(0,0);
   lcd.print("Auto Fish Feeder");
   Serial.print("Auto Fish Feeder"); 
   lcd.setCursor(0,1);
   lcd.print("  DEVICE ON/OFF ");
   Serial.print("  DEVICE ON/OFF "); 
   delay(3000);
 if(!RTC.isrunning())
 {
 RTC.adjust(DateTime(__DATE__,__TIME__));
 }
}

void loop() {
  // Masukkan kode utama di sini, agar bisa dijalankan berulang kali:
DateTime now = RTC.now();
if(digitalRead(btn4)==LOW){
  deviceontime();
  deviceofftime();
}
 
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("TIME:");
 Serial.print("TIME:");
 lcd.setCursor(6,0);
 printDigits(HOUR=now.hour()); 
 lcd.print(":");
 Serial.print(":");
 printDigits(MINUT=now.minute());
 lcd.print(":");
 Serial.print(":");
 printDigits(SECOND=now.second());
 if(HOUR < 12){                  // menambahkan AM/PM sufffix
          lcd.createChar(5,Aalpha);
          lcd.createChar(6,Malpha);
          lcd.setCursor(14,0);
          lcd.write(5);
          lcd.setCursor(15,0);
          lcd.write(6);
          
    }
   else{
          lcd.createChar(5,Palpha);
          lcd.createChar(6,Malpha);
          lcd.setCursor(14,0);
          lcd.write(5);
          lcd.setCursor(15,0);
          lcd.write(6);
   } 
 lcd.setCursor(0,1);
 lcd.print("DATE: ");
 Serial.print("DATE: ");
 printDigits(DAY=now.day());
 lcd.print("/");
 Serial.print("/");
 printDigits(MONTH=now.month());
 lcd.print("/");
 Serial.print("/");
 lcd.print(YEAR=now.year());
 digitalWrite(relay,LOW);
 myservo.write(pos);
 delay(1000);
 if(HOUR== EEPROM.read(0) && MINUT == EEPROM.read(1)){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  DEVICE ON ");
  Serial.print(" DEVICE ON ");
  digitalWrite(relay,HIGH);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
  myservo.write(pos);
  delay(5000);
  myservo.write(180);
  delay(1000);
 /* for (pos = 0; pos <= 180; pos += 1) { // dari 0 derajat ke 180 derajat
    myservo.write(pos);              // memberi tahu servo untuk ke posisi di variable 'pos'
    delay(300);                       // menunggu 30ms untuk servo untuk mencapai posisi
  }
  for (pos = 180; pos >= 0; pos -= 1) { // dari 180 derajat ke 0 derajat
    myservo.write(pos);              // memberi tahu servo untuk ke posisi di variable 'pos'
    delay(300);                       //  menunggu 30ms untuk servo untuk mencapai posisi
  } 
   */
  CheckTime();
 }
}

void printDigits(int digits)// fungsi void ini berguna untuk menambahkan "0" pada
//awal nomor, sehingga yang ditampilkan menjadi "00:05:00", dan bukan "00:5 :00"
{
  if(digits < 10) 
  {
    lcd.print("0");
    Serial.print("0");
    lcd.print(digits);
  }
  else
  {
    lcd.print(digits);
  }
}
/* fungsi untuk mencocokkan waktu */
void CheckTime()
{
  int checkhrOFF=0,checkminOFF=0;
  while(1)
  { 
  DateTime now = RTC.now();
  lcd.setCursor(0,1);
  lcd.print("TIME: ");
  Serial.print("TIME: ");
  printDigits(HOUR=now.hour()); 
  lcd.print(":");
  Serial.print(":");
  printDigits(MINUT=now.minute());
  lcd.print(":");
  Serial.print(":");
  printDigits(SECOND=now.second());
  checkhrOFF=EEPROM.read(2);
  checkminOFF=EEPROM.read(3);
  if(HOUR == checkhrOFF && MINUT == checkminOFF){
   lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(" Device Turn OFF");
  Serial.print(" Device Turn OFF");
  digitalWrite(relay,LOW);
  myservo.write(pos);
  delay(2000);
  break;   
  }
 }
}
void deviceontime(){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ENTER ON TIME");
        Serial.print("ENTER ON TIME");
        lcd.setCursor(8,1);
        lcd.print("00:00:00");
        Serial.print("00:00:00");
       while(1){
             if(digitalRead(btn1)==LOW){
              starthr++;
              lcd.setCursor(8,1);
              printDigits(starthr);
              //EEPROM.write(0,starthr);
              delay(200);
              if(starthr==24)
              starthr=0;
             }
             if(digitalRead(btn2)==LOW){
              startmin++;
              lcd.setCursor(11,1);
              printDigits(startmin);
             // EEPROM.write(0,startmin);
              delay(200);
              if(startmin==60)
              startmin=0;
             }
              if(digitalRead(btn3)==LOW){
                 
                 EEPROM.write(0,starthr);
                 EEPROM.write(1,startmin);
                 lcd.setCursor(0,0);
                 lcd.print(" START TIME SET ");
                 Serial.print(" START TIME SET ");
                 lcd.setCursor(0,1);
                 lcd.print("AT: ");
                 Serial.print("AT: ");
                 printDigits(EEPROM.read(0));
                 lcd.print(":");
                 Serial.print(":");
                 printDigits(EEPROM.read(1));
                 lcd.print(":00");
                 lcd.print("     ");
                 Serial.print(":00");
                 Serial.print("     ");
                 delay(5000);
                 starthr=0;
                 startmin=0;
                 break;
              }
       }
}


void deviceofftime(){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ENTER OFF TIME");
        Serial.print("ENTER OFF TIME");
        lcd.setCursor(8,1);
        lcd.print("00:00:00");
        Serial.print("00:00:00");
       while(1){
             if(digitalRead(btn1)==LOW){
              offhr++;
              lcd.setCursor(8,1);
              printDigits(offhr);
              //EEPROM.write(0,starthr);
              delay(200);
              if(offhr==24)
              offhr=0;
             }
             if(digitalRead(btn2)==LOW){
              offmin++;
              lcd.setCursor(11,1);
              printDigits(offmin);
             // EEPROM.write(0,startmin);
              delay(200);
              if(offmin==60)
              offmin=0;
             }
              if(digitalRead(btn3)==LOW){
                 EEPROM.write(2,offhr);
                 EEPROM.write(3,offmin);
                 lcd.setCursor(0,0);
                 lcd.print("  OFF TIME SET  ");
                 Serial.print("  OFF TIME SET  ");
                 lcd.setCursor(0,1);
                 lcd.print("AT: ");
                 Serial.print("AT: ");
                 printDigits(EEPROM.read(2));
                 lcd.print(":");
                 Serial.print(":");
                 printDigits(EEPROM.read(3));
                 lcd.print(":00");
                 Serial.print(":00");
                 lcd.print("     ");
                 Serial.print("     ");
                 delay(5000);
                 offhr=0;
                 offmin=0;
                 break;
              }
             
       }
}