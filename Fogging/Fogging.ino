/*
   Arduino time counter and checking temperature for control fogging machine
   [RMUTL Senior Project]
   Hardware : Arduino UNO, LCD, Relay, Keypad, DHT, Soil moisture, RTC
   Author   : Arduino Siam (bavensky)
   Date     : 11/04/2017

        --Pin out--
    Module        Arduino
    Keypad 4x4 :
    Row1          D3
    Row2          D4
    Row3          D5
    Row4          D6
    Col1          D7
    Col2          D8
    Col3          D9
    Col4          D10

    LCD 1602 I2C :
    VCC           5V
    GND           GND
    SDA           A4
    SCL           A5

    RTC 1307 :
    VCC           5V
    GND           GND
    SDA           A4
    SCL           A5

    DHT22 :
    VCC           5V
    Signal        D2
    GND           GND

    Soil Moisture :
    VCC           5V
    GND           GND
    Analog        A1

    Relay solenoid :
    Tric          D12
    GND           GND

*/



#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include "DHT.h"
#include <Keypad.h>
#include <EEPROM.h>

#define addrH  1
#define addrM  2
#define addrT  3
#define addrS  4
byte addrHour, addrMinute, addrTemp, addrSoil;


const byte ROWS = 4;    // four rows
const byte COLS = 3;    // three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};  // connect to the row
byte colPins[COLS] = {5, 4, 3};     // connect to the column
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);


#define DHTPIN  2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float t, h;


RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int _hour, _min,  _sec;
int _day, _month,  _year;


LiquidCrystal_I2C lcd(0x3f, 16, 2);


#define SOIL  A1
byte soilValue = 0;


#define SOLENOID  13


int mode = 0;


void readDHT() {
  t = dht.readTemperature();;
  h = dht.readHumidity();
}

void readTime() {
  DateTime now = rtc.now();
  //  daysOfTheWeek[now.dayOfTheWeek()]
  _hour   = now.hour();
  _min    = now.minute();
  _sec    = now.second();
  _day    = now.month();
  _month  = now.month();
  _year   = now.year();
}

void setting() {

}
void mode1() {

}
void mode2() {

}
void mode3() {

}


void setup() {
  Serial.begin(9600);

  pinMode(SOLENOID, OUTPUT);

  dht.begin();

  lcd.begin();

  rtc.begin();
  //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));


  //  EEPROM.write(addrH, 1);
  //  EEPROM.write(addrM, 2);
  //  EEPROM.write(addrT, 3);
  //  EEPROM.write(addrS, 4);
  addrHour    = EEPROM.read(addrH);
  addrMinute  = EEPROM.read(addrM);
  addrTemp    = EEPROM.read(addrT);
  addrSoil    = EEPROM.read(addrS);

  Serial.print(addrHour);
  Serial.print(addrMinute);
  Serial.print(addrTemp);
  Serial.println(addrSoil);
}

void loop() {
  readTime();
  readDHT();
  soilValue = map(analogRead(SOIL), 1023, 100, 0, 100);


  char customKey = customKeypad.getKey();
  Serial.println(customKey);
  if (customKey == '1') {
    digitalWrite(SOLENOID, !digitalRead(SOLENOID));
  }

  lcd.setCursor(0, 0);
  if (_day <= 9) lcd.print("0");
  lcd.print(_day);
  lcd.print("/");
  if (_month <= 9) lcd.print("0");
  lcd.print(_month);
  lcd.print("/");
  lcd.print(_year - 2000);
  lcd.print(" ");
  if (_hour <= 9) lcd.print("0");
  lcd.print(_hour);
  lcd.print(":");
  if (_min <= 9) lcd.print("0");
  lcd.print(_min);
  lcd.print("s. ");


  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(t);
  lcd.print(" H:");
  lcd.print(h);
  lcd.print("   ");
  delay(100);
}
