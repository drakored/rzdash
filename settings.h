
boolean IsSelected = false;
int pause = 250;

void selectRom () {
  
  ButtonBbyte = 0;
 
 GLCD.Update();
 
// delay(pause);
 
 while (true) {
   
    GLCD.CursorTo(0, 0); 
    GLCD.Puts("Select Rom:");
   
  if (digitalRead(ButtonB) == LOW) {
  if (millis() - previousMillis[2]> pause) {
    previousMillis[2] = millis();  
    ButtonBbyte++;
    beepDelay(100);
  }
}

  if (digitalRead(ButtonA) == HIGH) {
    ButtonAbyte = 0;
}
   
   if  (ButtonBbyte > 3){
          ButtonBbyte = 0;
   }
   
   if (ButtonBbyte == 0){
    GLCD.CursorTo(0, 2); 
    GLCD.Puts("> Crome 1.4+");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    previousMillis[2] = millis();  
    DataMode(CROME14);
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else if (iCmdArray == &CROME14_ARRAY[0]){
    GLCD.CursorTo(0, 2); 
    GLCD.Puts("* Crome 1.4+");
   }  
   else {
     GLCD.CursorTo(0, 2); 
     GLCD.Puts("  Crome 1.4+");   
   }
   
   if (ButtonBbyte == 1){
    GLCD.CursorTo(0, 3); 
    GLCD.Puts("> Crome -1.2");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    DataMode(CROME12);
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else if (iCmdArray == &CROME12_ARRAY[0]){
    GLCD.CursorTo(0, 3); 
    GLCD.Puts("* Crome -1.2");
   }  
   else {
     GLCD.CursorTo(0, 3); 
     GLCD.Puts("  Crome -1.2");
   }
   
   if (ButtonBbyte == 2){
    GLCD.CursorTo(0, 4); 
    GLCD.Puts("> NG60");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    DataMode(NG60);
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else if (iCmdArray == &NG60_ARRAY[0]){
    GLCD.CursorTo(0, 4); 
    GLCD.Puts("* NG60");
   }
   else {
     GLCD.CursorTo(0, 4); 
     GLCD.Puts("  NG60");
 }
 
   if (ButtonBbyte == 3){
    GLCD.CursorTo(0, 7); 
    GLCD.Puts("> Quit");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else {
     GLCD.CursorTo(0, 7);
     GLCD.Puts("  Quit");
   }
   
   GLCD.Update();
 }
}


void selectBackLight () {
    
  ButtonBbyte = 0;
  char cBackLight[] = "000";
 
 GLCD.Update();
// delay(pause);
 
 while (true) {
   
    GLCD.CursorTo(0, 0); 
    GLCD.Puts("Change Backlight:");
   
  if (digitalRead(ButtonB) == LOW) {
  if (millis() - previousMillis[2]> pause) {
    previousMillis[2] = millis();  
    ButtonBbyte++;
    beepDelay(100);
  }
}

  if (digitalRead(ButtonA) == HIGH) {
    ButtonAbyte = 0;
}
   
   if  (ButtonBbyte > 1){
          ButtonBbyte = 0;
   }
   if (BackLight >= 200) {
          BackLight = 2;
   }
   sprintf(cBackLight,"%d",BackLight);   
   

   if (ButtonBbyte == 0){
    GLCD.CursorTo(0, 2); 
    GLCD.Puts("> Luminosity: ");
    GLCD.Puts("    ");
    GLCD.CursorTo(14, 2); 
    GLCD.Puts(cBackLight);
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    BackLight++;
    delay(30);
      }
    }
   }
   else {
     GLCD.CursorTo(0, 2);
     GLCD.Puts("  Luminosity: ");
     GLCD.Puts(cBackLight);
   }
   
   if (ButtonBbyte == 1){
    GLCD.CursorTo(0, 7); 
    GLCD.Puts("> Quit");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else {
     GLCD.CursorTo(0, 7);
     GLCD.Puts("  Quit");
   }
   lcdBackLight(BackLight);
   GLCD.Update();
 }
}


void selectOilTemp () {
  
}


void selectOilPress () {
  
}


void selectBuzzer () {
  
   ButtonBbyte = 0;
 
 GLCD.Update();
 
// delay(pause);
 
 while (true) {
   
    GLCD.CursorTo(0, 0); 
    GLCD.Puts("Buzzer:");
   
  if (digitalRead(ButtonB) == LOW) {
  if (millis() - previousMillis[2]> pause) {
    previousMillis[2] = millis();  
    ButtonBbyte++;
    beepDelay(100);
  }
}

  if (digitalRead(ButtonA) == HIGH) {
    ButtonAbyte = 0;
}
   
   if  (ButtonBbyte > 2){
          ButtonBbyte = 0;
   }
   
   if (ButtonBbyte == 0){
    GLCD.CursorTo(0, 2); 
    GLCD.Puts("> On");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beep = true;
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else if (beep){
    GLCD.CursorTo(0, 2); 
    GLCD.Puts("* On");
   }  
   else {
     GLCD.CursorTo(0, 2); 
     GLCD.Puts("  On");   
   }
   
   if (ButtonBbyte == 1){
    GLCD.CursorTo(0, 3); 
    GLCD.Puts("> Off");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beep = false;
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else if (!beep){
    GLCD.CursorTo(0, 3); 
    GLCD.Puts("* Off");
   }  
   else {
     GLCD.CursorTo(0, 3); 
     GLCD.Puts("  Off");
   }
   
   if (ButtonBbyte == 2){
    GLCD.CursorTo(0, 7); 
    GLCD.Puts("> Quit");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else {
     GLCD.CursorTo(0, 7);
     GLCD.Puts("  Quit");
   }
   
   GLCD.Update();
 } 
}


void selectShiftLight () {
   
 ButtonBbyte = 0;
 char cShiftRpm[] = "00000";
   
 GLCD.Update();
// delay(pause);
 
 while (true) {
   
   
    GLCD.CursorTo(0, 0); 
    GLCD.Puts("Shiftlight:");
   
  if (digitalRead(ButtonB) == LOW) {
  if (millis() - previousMillis[2]> pause) {
    previousMillis[2] = millis();  
    ButtonBbyte++;
    beepDelay(100);
  }
}

  if (digitalRead(ButtonA) == HIGH) {
    ButtonAbyte = 0;
}
   
   if  (ButtonBbyte > 3){
          ButtonBbyte = 0;
   }
   sprintf(cShiftRpm,"%d",ShifterRpm);   
   
   if (ButtonBbyte == 0){
    GLCD.CursorTo(0, 2); 
    GLCD.Puts("> On");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    shiftlight = true;
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else if (shiftlight){
    GLCD.CursorTo(0, 2); 
    GLCD.Puts("* On");
}  
   else {
     GLCD.CursorTo(0, 2); 
     GLCD.Puts("  On");   
   }
   
   if (ButtonBbyte == 1){
    GLCD.CursorTo(0, 3); 
    GLCD.Puts("> Off");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    shiftlight = false;
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else if (!shiftlight){
    GLCD.CursorTo(0, 3); 
    GLCD.Puts("* Off");
}    
   else {
     GLCD.CursorTo(0, 3); 
     GLCD.Puts("  Off");
   }
   
   if (ButtonBbyte == 2){
    GLCD.CursorTo(0, 5); 
    GLCD.Puts("> RPM: ");
    GLCD.Puts("      ");
    GLCD.CursorTo(7, 5); 
    GLCD.Puts(cShiftRpm);
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    ShifterRpm+=250;
    delay(250);
    if (ShifterRpm >= 11000)
          ShifterRpm = 5000;
      }
    }
   }
   else {
     GLCD.CursorTo(0, 5); 
     GLCD.Puts("  RPM: ");
     GLCD.Puts("      ");
     GLCD.CursorTo(7, 5); 
     GLCD.Puts(cShiftRpm);
   }
   
   if (ButtonBbyte == 3){
    GLCD.CursorTo(0, 7); 
    GLCD.Puts("> Quit");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    break;
      }
    }
   }
   else {
     GLCD.CursorTo(0, 7);
     GLCD.Puts("  Quit");
   }
   
   GLCD.Update();
 }  
}


void Settings () {
  
 ButtonAbyte = 0;  
 ButtonBbyte = 0; 
 beepDelay(100);
 
 GLCD.Update();
 
// delay(pause);
 
 while (true) {
   
    GLCD.CursorTo(0, 0); 
    GLCD.Puts("Settings:");
   
  if (digitalRead(ButtonB) == LOW) {
  if (millis() - previousMillis[2]> pause) {
    previousMillis[2] = millis();  
    ButtonBbyte++;
    beepDelay(100);
    }
  }
  
  if (digitalRead(ButtonA) == HIGH) {
    ButtonAbyte = 0;
}
   
   if  (ButtonBbyte > 4){
          ButtonBbyte = 0;
   }
   
   if (ButtonBbyte == 0){
    GLCD.CursorTo(0, 2); 
    GLCD.Puts("> Set Rom mode");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    selectRom();
      }
    }
   }
   else {
     GLCD.CursorTo(0, 2); 
     GLCD.Puts("  Set Rom mode");   
   }
   
   if (ButtonBbyte == 1){
    GLCD.CursorTo(0, 3); 
    GLCD.Puts("> Set Backlight");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    selectBackLight ();
      }
    }
   }
   else {
     GLCD.CursorTo(0, 3); 
     GLCD.Puts("  Set Backlight");
   }
   
   if (ButtonBbyte == 2){
    GLCD.CursorTo(0, 4); 
    GLCD.Puts("> Buzzer On/Off");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    selectBuzzer();
      }
    }
   }
   else {
     GLCD.CursorTo(0, 4); 
     GLCD.Puts("  Buzzer On/Off");
 }
 
    if (ButtonBbyte == 3){
    GLCD.CursorTo(0, 5); 
    GLCD.Puts("> Shift Light");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beepDelay(100);
    GlcdClear();
    ButtonBbyte = 0;
    ButtonAbyte = 1;
    selectShiftLight();
      }
    }
   }
   else {
     GLCD.CursorTo(0, 5); 
     GLCD.Puts("  Shift Light");
 }
 
 
   if (ButtonBbyte == 4){
    GLCD.CursorTo(0, 7); 
    GLCD.Puts("> Quit");
    if (digitalRead(ButtonA) == LOW && ButtonAbyte == 0) {
      if (millis() - previousMillis[2]> pause) {
    beepDelay(100);
    GlcdClear();
    break;
      }
    }
   }
   else {
     GLCD.CursorTo(0, 7);
     GLCD.Puts("  Quit");
   }
   
   GLCD.Update();
 }
}

