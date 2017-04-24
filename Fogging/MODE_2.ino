void mode2() {
  char inChar = customKeypad.getKey();
  if (inChar) {
    delay(200);
    switch (inChar) {
      case '1': numKey = 1; break;
      case '2': numKey = 2; break;
      case '3': numKey = 3; break;
      case '4': numKey = 4; break;
      case '5': numKey = 5; break;
      case '6': numKey = 6; break;
      case '7': numKey = 7; break;
      case '8': numKey = 8; break;
      case '9': numKey = 9; break;
      case '0': numKey = 0; break;
    }

    curSorcount2 += 1;
    countPass += 1;
  }

  if (countPass == 1) {
    numKey1 = numKey;
  } else if (countPass == 2) {
    numKey2 = numKey;

    numKey1 = numKey1 * 10;
    addrTemp = numKey1 + numKey2;
    countPass += 1;
  }

  readDHT();
  lcd.setCursor(0, 0);
  lcd.print("Mode2  Set Temp ");
  lcd.setCursor(0, 1);
  if (countPass < 2) {
    lcd.print("temp: ");
    lcd.print(t);
    lcd.print("*C ");
    lcd.print(numKey1);
    lcd.print(numKey2);
    lcd.print("*C ");
    lcd.setCursor(curSorcount2, 1);
    lcd.noCursor();
    delay(50);
    lcd.cursor();
    delay(50);
  } else {
    lcd.print("Set TEMP = ");
    lcd.print(addrTemp);
    lcd.print("*C ");
  }

  if (inChar == '*') {
    lcd.clear();
    countPass = 0;
    curSorcount2 = 11;
    timeDone = false;
    mode = 0;
  }

  if (inChar == '#' && countPass != 4) {
    lcd.clear();
    addrTemp = EEPROM.read(addrT);
    countPass = 0;
    tempDone = true;
  }

  if (inChar == '#' || countPass == 4) {
    lcd.clear();
    EEPROM.write(addrT, addrTemp);
    countPass = 0;
    tempDone = true;
  }

  while (tempDone == true) {
    readDHT();
    lcd.setCursor(0, 0);
    lcd.print("Mode2  temp=");
    lcd.print(t);
    lcd.print("*C   ");
    lcd.setCursor(0, 1);
    if (addrTemp <= 9) lcd.print("0");
    lcd.print("Active--> ");
    lcd.print(addrTemp);
    lcd.print("*C   ");

    if (t >= addrTemp) {
      digitalWrite(SOLENOID, LOW);
    } else {
      digitalWrite(SOLENOID, HIGH);
    }

    char inChar = customKeypad.getKey();
    if (inChar == '*') {
      lcd.clear();
      tempDone = false;
      curSorcount2 = 11;
      mode = 0;
    }
  }
}
