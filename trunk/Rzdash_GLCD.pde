char VERSION[5] = "R21";

#include <inttypes.h>
#include <avr/pgmspace.h>
#include "variables.h"
#include "floatToString.h"
#include "ecu_constants.h"
#include "fetchEcu.h"
#include "fetchEMS.h"
#include "fetchSensors.h"

#include <ks0108.h>
#include "SystemFont5x7.h"   // system font
#include "splash.h"

#include "display.h"
#include "leds.h"
#include "sound.h"
#include "menu.h"
#include "settings.h"
#include "serial.h"


/*==============================================================================
 * SETUP()
 *============================================================================*/

void setup() {
  
//  TCCR0B = TCCR0B & 0b11111000 | 0x03; //PWM @ 1 Khz for pins 4 & 13
  TCCR1B = TCCR1B & 0b11111000 | 0x02; //PWM @ 4 Khz for pins 11 & 12 (buzzer)
  TCCR2B = TCCR2B & 0b11111000 | 0x05; //PWM @ 30.5 hz for pins 9 & 10 (solenoid)
  TCCR3B = TCCR3B & 0b11111000 | 0x01; //PWM @ 31 Khz for pins 2 & 3 & 5 (backlight)
  TCCR4B = TCCR4B & 0b11111000 | 0x03; //PWM @ 488 hz for pins 6 & 7 & 8
  TCCR5B = TCCR5B & 0b11111000 | 0x05; //PWM @ 30.5 hz for pins 45 & 46 (blinking leds)

//  analogReference(EXTERNAL);
  pinMode(ShifterPin, OUTPUT);      //shifter
  
  pinMode(ButtonA, INPUT);
  pinMode(ButtonB, INPUT);
  digitalWrite(ButtonA, HIGH);
  digitalWrite(ButtonB, HIGH);
  
  pinMode(LcdReset, OUTPUT);
  pinMode(BackLightPin, OUTPUT);
  digitalWrite(LcdReset, HIGH); 
  
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
     pinMode(BarGraphPins[thisLed], OUTPUT); 
   }
  
  DataMode(CROME14); //set default OBD mode
  
  Serial.begin(38400); //debug & datalog over usb serial
  Serial1.begin(38400); //ECU connection

  beepOn();  
  GLCD.Init(NON_INVERTED);   // initialise the library, non inverted writes pixels onto a clear 
  GlcdClear();
  GLCD.Update();
//  GLCD.SelectFont(pa14); // switch to fixed width system font
//  GLCD.SelectFont(im30); // switch to fixed width system font
  GLCD.SelectFont(System5x7); // switch to fixed width system font
  lcdBackLight(150);

  GlcdSplash();
  beepOff();
  while (millis() <= 2000) {
  GLCD.Update();}
  GlcdClear();
  delay(200);
  GLCD.Update();
  GlcdClear();
  
  
  if (!serialCheckEcu()) 
    BadEcu();
    
  else 
    GoodEcu();
  
}

/*==============================================================================
 * LOOP()
 *============================================================================*/

void loop() {


if (digitalRead(ButtonB) == LOW) {
  if (millis() - previousMillis[2]> 500) {
    previousMillis[2] = millis();  
    NextMenu(); 
    BarCreated = false;
    beepLoopOn(100);
  }
}

if (digitalRead(ButtonA) == LOW) {
  if (millis() - previousMillis[2]> 500) {
    previousMillis[2] = millis();  
    GlcdClear();
    Settings();
    BarCreated = false;
  }
}

ShowMenu(0);
Shifter(30);


serialTimeout(250);
serialFastRelay();
lcdBackLight(BackLight);

//if (millis() - previousMillis[4] > 10 ) {
//previousMillis[4] = millis();
GLCD.Update();
//}

beepLoopOff();
}


