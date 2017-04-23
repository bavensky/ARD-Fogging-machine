void mode1() {
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
  lcd.print("Mode1  Set Time ");
  if (countPass <= 4) {
    lcd.setCursor(0, 1);
    if (addrHour <= 9 ) lcd.print("0");
    lcd.print(addrHour);
    lcd.print(":");
    if (addrMinute <= 9 ) lcd.print("0");
    lcd.print(addrMinute);
    lcd.print("m.  ");
    lcd.print(numKey1);
    lcd.print(numKey2);
    lcd.print(":");
    lcd.print(numKey3);
    lcd.print(numKey4);
    lcd.print("m.   ");
    lcd.setCursor(curSorcount1, 1);
    lcd.noCursor();
    delay(100);
    lcd.cursor();
    delay(100);
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

    //    Serial.print("Sent1 ");
    //    Serial.print(_hour);
    //    Serial.print(":");
    //    Serial.print(_min);
    //    Serial.print("   ");
    //    Serial.print(setHour);
    //    Serial.print(":");
    //    Serial.println(setMinute);
    //    delay(3000);

    countPass = 0;
    curSorcount1 = 9;
    timeDone = true;
    lcd.clear();
    numKey1 = 0;
    numKey2 = 0;
    numKey3 = 0;
    numKey4 = 0;
    //    addrHour = EEPROM.read(addrH) // read set time stop fogging
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

    //    Serial.print("Sent2 ");
    //    Serial.print(_hour);
    //    Serial.print(":");
    //    Serial.print(_min);
    //    Serial.print("   ");
    //    Serial.print(setHour);
    //    Serial.print(":");
    //    Serial.println(setMinute);
    //    delay(3000);

    countPass = 0;
    curSorcount1 = 9;
    timeDone = true;
    lcd.clear();
    numKey1 = 0;
    numKey2 = 0;
    numKey3 = 0;
    numKey4 = 0;
    //    addrHour = EEPROM.read(addrH) // read set time stop fogging
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
      curSorcount2 += 1;
      if (curSorcount2 == 11) {
        curSorcount2 = 10;
      }
      countPass += 1;
    }

    if (countPass == 1) {
      numKey1 = numKey;
    } else if (countPass == 2) {
      numKey2 = numKey;

      if (numKey1 != 0) {
        numKey1 = numKey1 * 10;
        stopCount = numKey1 + numKey2;
      } else {
        stopCount = numKey2;
      }

      countPass += 1;
    }

    lcd.setCursor(0, 0);
    lcd.print("Mode1 Stop Time ");
    lcd.setCursor(0, 1);
    lcd.print("Stop : ");
    lcd.print(EEPROM.read(addrStop));
    lcd.print(" ");
    lcd.print(numKey1);
    lcd.print(numKey2);
    lcd.print("m. ");
    lcd.setCursor(curSorcount2, 1);
    lcd.noCursor();
    delay(100);
    lcd.cursor();
    delay(100);

    if (inChar == '*') {
      countPass = 0;
      curSorcount2 = 9;
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;
      lcd.clear();
      mode = 0;
    }

    if (inChar == '#' || countPass == 4) {
      EEPROM.write(addrStop, stopCount);

      readTime();
      stopCount = setMinute + stopCount;

      if (stopCount > 59) {
        stopCount = stopCount - 60;
      }

      countPass = 0;
      curSorcount2 = 9;
      lcd.clear();
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;
      timeDone = false;
      activeTime = true;
    }

    if (inChar == '#') {
      EEPROM.read(addrStop);
      stopCount = setMinute + stopCount;

      if (stopCount > 59) {
        stopCount = stopCount - 60;
      }

      countPass = 0;
      curSorcount2 = 9;
      lcd.clear();
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;
      timeDone = false;
      activeTime = true;
    }
  }


  while (activeTime == true) {
    readTime();
    lcd.setCursor(0, 0);
    lcd.print("Mode1  ");
    if (_hour <= 9) lcd.print("0");
    lcd.print(_hour);
    lcd.print(":");
    if (_min <= 9) lcd.print("0");
    lcd.print(_min);
    lcd.print(":");
    if (_sec <= 9) lcd.print("0");
    lcd.print(_sec);
    lcd.print("m. ");

    lcd.setCursor(0, 1);
    lcd.print("Active--> ");
    if (setHour <= 9 ) lcd.print("0");
    lcd.print(setHour);
    lcd.print(":");
    if (setMinute <= 9 ) lcd.print("0");
    lcd.print(setMinute);


    // update time
    if (setHour == _hour && setMinute == _min) {
      readTime();

      while (stopCount != _min) {
        readTime();
        lcd.setCursor(0, 0);
        lcd.print("Mode1  ");
        if (_hour <= 9) lcd.print("0");
        lcd.print(_hour);
        lcd.print(":");
        if (_min <= 9) lcd.print("0");
        lcd.print(_min);
        lcd.print(":");
        if (_sec <= 9) lcd.print("0");
        lcd.print(_sec);
        lcd.print("m. ");
        lcd.setCursor(0, 1);
        lcd.print("stopCount--> ");;
        if (stopCount <= 9 ) lcd.print("0");
        lcd.print(stopCount);
        lcd.print("m  ");
        digitalWrite(SOLENOID, LOW);
      }

      //      setHour = _hour + addrHour;
      //      setMinute = _min + addrMinute;
      //      stopCount = setMinute + stopCount;
      //
      //      if (stopCount > 59) {
      //        stopCount = stopCount - 59;
      //      }
      //      if (setMinute > 59) {
      //        setHour += 1;
      //        setMinute = setMinute - 59;
      //      }
      //      if (setHour > 23) {
      //        setHour = setHour - 23;
      //      }

      digitalWrite(SOLENOID, HIGH);
      timeDone = false;
      activeTime = false;
      mode = 0;
    }


    char inChar = customKeypad.getKey();
    if (inChar == '*') {
      lcd.clear();
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;

      countPass = 0;
      timeDone = false;
      activeTime = false;
      mode = 0;
    }
  }
}
