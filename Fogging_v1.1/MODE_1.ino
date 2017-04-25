void mode1() {
  readTime();

  // mode set start time
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

    curSorcount1 += 1;
    if (curSorcount1 == 11) {
      curSorcount1 += 1;
    }

    countPass += 1;
  }

  if (countPass == 1) {
    numKey1 = numKey;
  } else if (countPass == 2) {
    numKey2 = numKey;
  } else if (countPass == 3) {
    numKey3 = numKey;
  } else if (countPass == 4) {
    numKey4 = numKey;

    if (numKey1 != 0) {
      numKey1 = numKey1 * 10;
      addrHour = numKey1 + numKey2;
    } else {
      addrHour = numKey2;
    }

    if (numKey3 != 0) {
      numKey3 = numKey3 * 10;
      addrMinute = numKey3 + numKey4;
    } else {
      addrMinute = numKey4;
    }

    countPass += 1;
  }


  lcd.setCursor(0, 0);
  lcd.print("Mode1 Time Start");
  if (countPass <= 4) {
    lcd.setCursor(0, 1);
    if (_hour <= 9 ) lcd.print("0");
    lcd.print(_hour);
    lcd.print(":");
    if (_min <= 9 ) lcd.print("0");
    lcd.print(_min);
    lcd.print("m.  ");
    lcd.print(numKey1);
    lcd.print(numKey2);
    lcd.print(":");
    lcd.print(numKey3);
    lcd.print(numKey4);
    lcd.print("m.   ");
    lcd.setCursor(curSorcount1, 1);
    lcd.noCursor();
    delay(50);
    lcd.cursor();
    delay(50);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Set Time: ");
    if (addrHour <= 9 ) lcd.print("0");
    lcd.print(addrHour);
    lcd.print(":");
    if (addrMinute <= 9 ) lcd.print("0");
    lcd.print(addrMinute);
    lcd.print("m. ");


    // if setting time false go back to mode 1
    if (addrHour > 23 || addrMinute > 59) {
      lcd.setCursor(0, 1);
      lcd.print("Set Time: FALSE ");
      delay(2000);
      lcd.clear();
      countPass = 0;
      curSorcount1 = 9;
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;

      addrHour = EEPROM.read(addrH);
      addrMinute = EEPROM.read(addrM);
      mode = 1;
    }
  }

  if (inChar == '*') {
    timeDone = false;
    countPass = 0;
    curSorcount1 = 9;
    numKey1 = 0;
    numKey2 = 0;
    numKey3 = 0;
    numKey4 = 0;
    lcd.clear();
    mode = 0;
  }

  if (inChar == '#' || countPass == 6) {
    EEPROM.write(addrH, addrHour);
    EEPROM.write(addrM, addrMinute);

    readTime();
    setHour = _hour + addrHour;
    setMinute = _min + addrMinute;

    if (setMinute > 59) {
      setHour += 1;
      setMinute = setMinute - 60;
    }
    if (setHour > 23) {
      setHour = setHour - 24;
    }

    countPass = 0;
    curSorcount1 = 9;
    timeDone = true;
    lcd.clear();
    numKey1 = 0;
    numKey2 = 0;
    numKey3 = 0;
    numKey4 = 0;
  }

  if (inChar == '#') {
    addrHour = EEPROM.read(addrH);
    addrMinute = EEPROM.read(addrM);
    readTime();
    setHour = _hour + addrHour;
    setMinute = _min + addrMinute;

    if (setMinute > 59) {
      setHour += 1;
      setMinute = setMinute - 60;
    }
    if (setHour > 23) {
      setHour = setHour - 24;
    }

    countPass = 0;
    curSorcount1 = 9;
    timeDone = true;
    lcd.clear();
    numKey1 = 0;
    numKey2 = 0;
    numKey3 = 0;
    numKey4 = 0;
  }







  // mode set stop time
  while (timeDone == true) {
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

      curSorcount1 += 1;
      if (curSorcount1 == 11) {
        curSorcount1 += 1;
      }

      countPass += 1;
    }

    if (countPass == 1) {
      numKey1 = numKey;
    } else if (countPass == 2) {
      numKey2 = numKey;
    } else if (countPass == 3) {
      numKey3 = numKey;
    } else if (countPass == 4) {
      numKey4 = numKey;

      if (numKey1 != 0) {
        numKey1 = numKey1 * 10;
        addrHour_S = numKey1 + numKey2;
      } else {
        addrHour_S = numKey2;
      }

      if (numKey3 != 0) {
        numKey3 = numKey3 * 10;
        addrMinute_S = numKey3 + numKey4;
      } else {
        addrMinute_S = numKey4;
      }

      countPass += 1;
    }

    lcd.setCursor(0, 0);
    lcd.print("Mode1 Time Stop ");
    if (countPass <= 4) {
      lcd.setCursor(0, 1);
      if (_hour <= 9 ) lcd.print("0");
      lcd.print(_hour);
      lcd.print(":");
      if (_min <= 9 ) lcd.print("0");
      lcd.print(_min);
      lcd.print("m.  ");
      lcd.print(numKey1);
      lcd.print(numKey2);
      lcd.print(":");
      lcd.print(numKey3);
      lcd.print(numKey4);
      lcd.print("m.   ");
      lcd.setCursor(curSorcount1, 1);
      lcd.noCursor();
      delay(50);
      lcd.cursor();
      delay(50);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Set Time: ");
      if (addrHour_S <= 9 ) lcd.print("0");
      lcd.print(addrHour_S);
      lcd.print(":");
      if (addrMinute_S <= 9 ) lcd.print("0");
      lcd.print(addrMinute_S);
      lcd.print("m. ");
      // if setting time false go back to mode 1
      if (addrHour_S > 23 || addrMinute_S > 59) {
        lcd.setCursor(0, 1);
        lcd.print("Set Time: FALSE ");
        delay(2000);
        lcd.clear();
        countPass = 0;
        curSorcount1 = 9;
        numKey1 = 0;
        numKey2 = 0;
        numKey3 = 0;
        numKey4 = 0;

        addrHour_S = EEPROM.read(addrSH);
        addrMinute_S = EEPROM.read(addrSM);
        mode = 1;
      }
    }

    if (inChar == '*') {
      timeDone = false;
      activeTime = false;
      countPass = 0;
      curSorcount1 = 9;
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;
      lcd.clear();
      mode = 0;
    }

    if (inChar == '#' || countPass == 6) {
      EEPROM.write(addrSH, addrHour_S);
      EEPROM.write(addrSM, addrMinute_S);

      readTime();
      stopHour = setHour + addrHour_S;
      stopMinute = setMinute + addrMinute_S;

      if (stopMinute > 59) {
        stopHour += 1;
        stopMinute = stopMinute - 60;
      }
      if (stopHour > 23) {
        stopHour = stopHour - 24;
      }

      countPass = 0;
      curSorcount1 = 9;
      timeDone = false;
      activeTime = true;
      lcd.clear();
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;
    }

    if (inChar == '#') {
      addrHour_S = EEPROM.read(addrSH);
      addrMinute_S = EEPROM.read(addrSM);
      readTime();
      stopHour = setHour + addrHour_S;
      stopMinute = setMinute + addrMinute_S;

      if (stopMinute > 59) {
        stopHour += 1;
        stopMinute = stopMinute - 60;
      }
      if (stopHour > 23) {
        stopHour = stopHour - 24;
      }

      countPass = 0;
      curSorcount1 = 9;
      timeDone = false;
      activeTime = true;
      lcd.clear();
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;
    }

  }








  while (activeTime == true) {

    // start fogging machine
    digitalWrite(SOLENOID, HIGH);

    readTime();
    lcd.setCursor(0, 0);
    lcd.print("Mode1     ");
    if (_hour <= 9) lcd.print("0");
    lcd.print(_hour);
    lcd.print(":");
    if (_min <= 9) lcd.print("0");
    lcd.print(_min);
    lcd.print("m  ");


    lcd.setCursor(0, 1);
    lcd.print("Active--> ");
    if (setHour <= 9 ) lcd.print("0");
    lcd.print(setHour);
    lcd.print(":");
    if (setMinute <= 9 ) lcd.print("0");
    lcd.print(setMinute);
    lcd.print("m  ");


    // stop time
    if (setHour == _hour && setMinute == _min) {
      boolean state = true;
      while (state == true) {
        Serial.println("stopTime");
        digitalWrite(SOLENOID, LOW);

        readTime();
        lcd.setCursor(0, 0);
        lcd.print("Mode1     ");
        if (_hour <= 9) lcd.print("0");
        lcd.print(_hour);
        lcd.print(":");
        if (_min <= 9) lcd.print("0");
        lcd.print(_min);
        lcd.print("m  ");

        lcd.setCursor(0, 1);
        lcd.print("Stop  --> ");
        if (stopHour <= 9 ) lcd.print("0");
        lcd.print(stopHour);
        lcd.print(":");
        if (stopMinute <= 9 ) lcd.print("0");
        lcd.print(stopMinute);
        lcd.print("m  ");

        if (stopHour == _hour && stopMinute == _min) {
          digitalWrite(SOLENOID, HIGH);
          state = false;
        }

        char inChar = customKeypad.getKey();
        if (inChar == '*') {
          countPass = 0;
          curSorcount1 = 9;
          numKey1 = 0;
          numKey2 = 0;
          numKey3 = 0;
          numKey4 = 0;
          lcd.clear();
          state = false;
          activeTime = false;
          timeDone = false;
          mode = 0;
        }
      }

      addrHour = EEPROM.read(addrH);
      addrMinute = EEPROM.read(addrM);
      setHour = _hour + addrHour;
      setMinute = _min + addrMinute;

      if (setMinute > 59) {
        setHour += 1;
        setMinute = setMinute - 60;
      }
      if (setHour > 23) {
        setHour = setHour - 24;
      }

      addrHour_S = EEPROM.read(addrSH);
      addrMinute_S = EEPROM.read(addrSM);
      stopHour = setHour + addrHour_S;
      stopMinute = setMinute + addrMinute_S;

      if (stopMinute > 59) {
        stopHour += 1;
        stopMinute = stopMinute - 60;
      }
      if (stopHour > 23) {
        stopHour = stopHour - 24;
      }
      Serial.println("END");
    }

    char inChar = customKeypad.getKey();
    if (inChar == '*') {
      countPass = 0;
      curSorcount1 = 9;
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;
      lcd.clear();
      activeTime = false;
      timeDone = false;
      mode = 0;
    }
  }
}
