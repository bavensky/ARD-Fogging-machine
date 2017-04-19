void mode3() {
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
    countPass += 1;
  }

  if (countPass == 1) {
    numKey1 = numKey;
  } else if (countPass == 2) {
    numKey2 = numKey;
  } else if (countPass == 3) {
    numKey3 = numKey;

    if (numKey1 != 0) {
      numKey1 = numKey1 * 100;
      numKey2 = numKey2 * 10;
      addrSoil = numKey1 + numKey2 + numKey3;
    } else if (numKey1 == 0 && numKey2 != 0) {
      numKey2 = numKey2 * 10;
      addrSoil = numKey2 + numKey3;
    } else {
      addrSoil = numKey3;
    }
    countPass += 1;
    
    Serial.println(addrSoil);
    if (addrSoil > 100) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Mode3  Set Soil ");
      lcd.setCursor(0, 1);
      lcd.print("Set SOIL = FALSE");
      delay(2000);
      countPass = 0;
      numKey1 = 0;
      numKey2 = 0;
      numKey3 = 0;
      numKey4 = 0;
      addrSoil = EEPROM.read(addrS);
      mode = 3;
    }
  }

  soilValue = map(analogRead(SOIL), 1023, 100, 0, 100);
  lcd.setCursor(0, 0);
  lcd.print("Mode3  Set Soil ");
  lcd.setCursor(0, 1);
  if (countPass < 3) {
    lcd.print("soil: ");
    if (soilValue <= 9) {
      lcd.print("00");
    } else if (soilValue >= 10 && soilValue <= 99) {
      lcd.print("0");
    }
    lcd.print(soilValue);
    lcd.print("% ");
    lcd.print(numKey1);
    lcd.print(numKey2);
    lcd.print(numKey3);
    lcd.print("%  ");
  } else {
    lcd.print("Set SOIL = ");
    lcd.print(addrSoil);
    lcd.print("%  ");
  }

  if (inChar == '*') {
    lcd.clear();
    countPass = 0;
    soilDone = false;
    mode = 0;
  }

  if (inChar == '#' && countPass != 5) {
    lcd.clear();
    addrSoil = EEPROM.read(addrS);
    countPass = 0;
    soilDone = true;
  }

  if (inChar == '#' || countPass == 5) {
    lcd.clear();
    EEPROM.write(addrS, addrSoil);
    countPass = 0;
    soilDone = true;
  }

  while (soilDone == true) {
    soilValue = map(analogRead(SOIL), 1023, 100, 0, 100);

    lcd.setCursor(0, 0);
    lcd.print("Mode3  soil=");
    if (soilValue <= 9) {
      lcd.print("00");
    } else if (soilValue >= 10 && soilValue <= 99) {
      lcd.print("0");
    }
    lcd.print(soilValue);
    lcd.print("% ");
    lcd.setCursor(0, 1);
    lcd.print("Active--> ");
    if (addrSoil <= 9) {
      lcd.print("00");
    } else if (addrSoil >= 10 && addrSoil <= 99) {
      lcd.print("0");
    }
    lcd.print(addrSoil);
    lcd.print("%   ");

    if (addrSoil <= soilValue) {
      digitalWrite(SOLENOID, LOW);
    } else {
      digitalWrite(SOLENOID, HIGH);
    }

    char inChar = customKeypad.getKey();
    if (inChar == '*') {
      lcd.clear();
      soilDone = false;
      mode = 0;
    }
  }
}