/*
   Arduino time counter and checking temperature for control fogging machine
   [RMUTL Senior Project]
   Hardware : Arduino UNO, LCD, Relay, Keypad, DHT, Soil moisture, RTC
   Author   : Arduino Siam (bavensky)
   Date     : 24/04/2017

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

#define addrH  11
#define addrM  22
#define addrT  33
#define addrS  44
#define addrStop  55
int addrHour, addrMinute, addrTemp, addrSoil;
byte setHour, setMinute;

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
int t, h;


RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int _hour, _min,  _sec;
int _day, _month,  _year;


LiquidCrystal_I2C lcd(0x3f, 16, 2);


#define SOIL  A1
byte soilValue = 0;


#define SOLENOID  12

boolean activeTime = false;
boolean timeDone = false;
boolean tempDone = false;
boolean soilDone = false;
boolean pressState = false;
byte countPass = 0;
int stopCount = 0;
int mode, numKey, numKey1, numKey2, numKey3, numKey4;
int colLCD = 10;
int curSorcount1 = 9;
int curSorcount2 = 9;


void readDHT() {
  t = dht.readTemperature();;
  h = dht.readHumidity();
}

void readTime() {
  DateTime now = rtc.now();
//    daysOfTheWeek[now.dayOfTheWeek()]
  _hour   = now.hour();
  _min    = now.minute();
  _sec    = now.second();
  _day    = now.day();
  _month  = now.month();
  _year   = now.year();
}

void setting() {
  lcd.setCursor(0, 0);
  lcd.print("setting mode :  ");
  lcd.setCursor(0, 1);
  lcd.print(" Fogging Machine");
  Serial.println("setting");
  if (customKeypad.getKey() == '#') mode = 0;
}

void setup() {
  Serial.begin(9600);

  pinMode(SOLENOID, OUTPUT);

  dht.begin();

  lcd.begin();

  rtc.begin();
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.setCursor(0, 0);
  lcd.print("    WELCOME     ");
  lcd.setCursor(0, 1);
  lcd.print("Fogging Machine ");
  delay(2000);
  Serial.println("Done...");
}

void loop() {
  readTime();
  readDHT();
  soilValue = map(analogRead(SOIL), 1023, 100, 0, 100);


  digitalWrite(SOLENOID, HIGH);

  lcd.setCursor(0, 0);
  lcd.print("Fogging Machine ");

  lcd.setCursor(0, 1);
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
  if (_hour <= 12) lcd.print("am ");
  else lcd.print("pm ");
  delay(50);


  char customKey = customKeypad.getKey();
  if (customKey == '1') {
    lcd.clear();

    numKey1 = 0;
    numKey2 = 0;
    numKey3 = 0;
    numKey4 = 0;

    addrHour = EEPROM.read(addrH);
    addrMinute = EEPROM.read(addrM);

    mode = 1;
    delay(200);
  }
  if (customKey == '2') {
    lcd.clear();

    numKey1 = 0;
    numKey2 = 0;
    numKey3 = 0;
    numKey4 = 0;


    addrTemp = EEPROM.read(addrT);

    mode = 2;
    delay(200);
  }
  if (customKey == '3') {
    lcd.clear();

    numKey1 = 0;
    numKey2 = 0;
    numKey3 = 0;
    numKey4 = 0;


    addrSoil = EEPROM.read(addrS);

    mode = 3;
    delay(200);
  }


  while (mode == 1) {
    mode1();
  }
  while (mode == 2) {
    mode2();
  }
  while (mode == 3) {
    mode3();
  }
  while (mode == 4) {
    setting();
  }
}
