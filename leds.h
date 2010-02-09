void LedBarGraph (float minimum, float maximum, float value) {
    
   // read the potentiometer:
   // int sensorReading = rpm;
   // map the result to a range from 0 to the number of LEDs:
   int ledLevel = map(value, minimum, maximum, 0, ledCount);
   // loop over the LED array:
   for (int thisLed = 0; thisLed < ledCount; thisLed++) {
     // if the array element's index is less than ledLevel,
     // turn the pin for this element on:
     if (thisLed < ledLevel) {
       digitalWrite(BarGraphPins[thisLed], HIGH);
     } 
     // turn off all pins higher than the ledLevel:
     else {
       digitalWrite(BarGraphPins[thisLed], LOW); 
     }
   }
}


void Shifter(int interval) {
  
  static int ledState = LOW;             // ledState used to set the LED
  
     if (millis() - previousMillis[0] > interval) {
     // save the last time you blinked the LED 
     previousMillis[0]  = millis();   

        if (rpm >= ShifterRpm) {
           // if the LED is off turn it on and vice-versa:
           if (ledState == LOW)
             ledState = HIGH;
           else
             ledState = LOW;

           // set the LED with the ledState of the variable:
           digitalWrite(ShifterPin, ledState);
        }     
   }
}
   
   
void lcdBackLight(int light) {
  light = map(light, 0, 100, 0, 255);
  analogWrite(BackLightPin, light);
}
