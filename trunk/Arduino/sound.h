void beepDelay(int duration) {

  if (beep) {  
    analogWrite(SoundPin, 124);  //50% duty as specified in HY-05 buzzer datasheet
    delay(duration);
    analogWrite(SoundPin, 0);
              }
}

void beepOn() {
  if (beep) { 
    beepTime = millis();
    analogWrite(SoundPin, 124);  //50% duty as specified in HY-05 buzzer datasheet
              }
}

void beepOff() {
  
    analogWrite(SoundPin, 0);  //0% duty
}

void beepLoopOn(int duration) {
    if (beep) { 
        if (!beepIsOn) {
    analogWrite(SoundPin, 124);  //50% duty as specified in HY-05 buzzer datasheet
    beepTime = millis();
    beepDuration = duration;
    beepIsOn = true;
                       }
                }
}

void beepLoopOff() {
    if (millis() - beepTime > beepDuration) {
    analogWrite(SoundPin, 0);
    beepIsOn = false;
    }
}

