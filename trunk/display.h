void GlcdClear() {
  short tx=0;
  short ty=0;
  for (ty=0; ty <= 63; ty++) {
    GLCD.SetDot(tx, ty, WHITE);
    
  for (tx=0; tx <= 127; tx++) {
    GLCD.SetDot(tx, ty, WHITE);
}
  }
}

void BadEcu() {
 GlcdClear();
 GLCD.Update();
    GLCD.CursorTo(5, 3); 
    GLCD.Puts("Check Ecu");
    GLCD.CursorTo(5, 4); 
    GLCD.Puts("Connection");
   while (millis() <= 5000) {
    GLCD.Update();
 }
 GlcdClear();
 GLCD.Update();
}

void GoodEcu() {
 GlcdClear();
 GLCD.Update();
    GLCD.CursorTo(6, 3); 
    GLCD.Puts("ECU test");
    GLCD.CursorTo(5, 4); 
    GLCD.Puts("Successful");
   while (millis() <= 5000) {
    GLCD.Update();
 }
GlcdClear();
GLCD.Update();
}

void BlinkBar(int interval) {
       if (millis() - previousMillis[1] > interval) {
     previousMillis[1] = millis();   

     if (Bar == false)
       Bar = true;
     else
       Bar = false;
   }
 }

void Wave(int x, int y) { //TODO
  
  }
    
void RaceDash (float minimum, float maximum, float value) { //TODO
  
// short angle[2][66] = {    1,   1,   1,  1,  1,  1,   1,   1,  1,  1,   1,  2,  2,  2,   2,  3,   3,  3,  4,  4,   4,  5,  5,  6,  6,   7,  7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 16, 16, 17, 18, 19, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
//                           29,28,27,26,25,24,23,22,21,20,19,19,18,17,16,16,15,14,14,13,12,12,11,11,10,10, 9, 9, 8, 8, 7 , 7,   6,    6,  5,    5,    4,   4,   3,    4,   3,   3,   3,    2,   2,    2,   2,   1,    1,   1 ,   1,   1,   1,   1,   1,    1,   1,    1,   1,    1,    1,  1,   1,    1,    1,   1};

short angle[2][30] = {   1,    1,     1,     1,    1,    1,    2,    2,    3,     4,    5,    6,    8,    9,  10,  12,  14,  16,  17,  19, 20, 22, 24, 26, 28, 30, 32 , 34, 36, 37,
                                       29,  27,  25,  23,  21,  19,  18,  16,  15,  14,  12,  11,  10,  8,    6,    5,     4,    3,   2,     2,    1,   1,   1,   1,    1,     1,    1,   1,   1,   1  };
                                       
                                      
 
  GLCD.DrawBitmap(racedash, 0, 0, BLACK);
 
  if (value < maximum/3) {
        unsigned int mask1 = map(value/2, minimum, (maximum/3), 0, 30);
        mask1 = constrain(mask1, 0, 30);
        GLCD.FillRect(1, 30-mask1, 36, 30-mask1, WHITE);
        
//        GLCD.FillRect(1, 1, 36, 28, WHITE);
        GLCD.FillRect(1, 1, 125, 28, WHITE);
  }
  
   if ( value > maximum/3 && value < (maximum/3)*2 ) {
     
 /*
        unsigned int mask2x = map(value, (maximum/3), (maximum/3)*2, 0, 35);
        mask2x = constrain(mask2x, 0, 35);
         unsigned int mask2y = map(value, (maximum/3), (maximum/3)*2, 0, 28);
        mask2y = constrain(mask2y, 0, 28);
        GLCD.FillRect(1+mask2x, 1, 35-mask2x, 28-mask2y, WHITE);
*/
      // WORKS BUT CRASHES
        unsigned int mask2 = map(value, (maximum/3), (maximum/3)*2, 0, 30);
        mask2 = constrain(mask2, 0, 30);
        
        for (short i = 29; i >= mask2; i--) {
              GLCD.DrawLine(angle[0][i], angle[1][i], 37, 29, WHITE);
        }
        
        GLCD.FillRect(37, 1, 88, 28, WHITE); 
  }
  
  if (value > (maximum/3)*2) {
        unsigned int mask3 = map(value, (maximum/3)*2, maximum, 37, 125);
        mask3 = constrain(mask3, 37, 125);
        GLCD.FillRect(mask3, 1, 125-mask3, 28, WHITE);
  }
  
  
  
}

void HBarGraphFrame(int x, int y) {
  
  GLCD.FillRect(x, y-1, 127, 8, WHITE); //clear the bar area
  GLCD.DrawRect(x, y, 127, 5, BLACK); //make the bar holder

  GLCD.SetDot(x, y-1, BLACK); //rulers
  GLCD.SetDot(x+31, y-1, BLACK); 
  GLCD.SetDot(x+63, y-1, BLACK);
  GLCD.SetDot(x+95, y-1, BLACK);
  GLCD.SetDot(x+127, y-1, BLACK);
}

void VBarGraphFrame(int x, int y) {
  
  short tx=x;
  for (tx=x; tx-x <= 10; tx++) {
  GLCD.DrawLine(tx-1, y, tx-1, y-63, WHITE);
  }
  GLCD.DrawLine(x, y, x, y-63, BLACK);
  GLCD.DrawLine(x+8, y, x+8, y-63, BLACK);
  
  GLCD.DrawLine(x-1, y-63, x+7, y-63, BLACK);
  GLCD.DrawLine(x-1, y, x+7, y, BLACK);
  
  //GLCD.SetDot(x-1, y, BLACK); //rulers
  GLCD.SetDot(x-1, y-15, BLACK); 
  GLCD.SetDot(x-1, y-31, BLACK);
  GLCD.SetDot(x-1, y-47, BLACK);
  //GLCD.SetDot(x-1, y-63, BLACK);
}

void BigGraphFrame(int y) {
  
  GLCD.FillRect(0, y, 127, 31, WHITE); //clear the bar area
  GLCD.DrawRect(0, y, 127, 31, BLACK); //make the bar holder
}

void HBarGraphFill(float minimum, float maximum, float value, int x, int y) {
  
  constrain(value, minimum, maximum);
  
  GLCD.FillRect(x+2, y+2, 123, 1, WHITE); //clear the bar
  
  long fill = map(value, minimum, maximum, 1, 123);
  fill = constrain(fill, 2, 123);

  GLCD.FillRect(x+2, y+2, fill, 1, BLACK); //fill the bar with the value  

}

void VBarGraphFill(float minimum, float maximum, float value, int x, int y) {
  
  constrain(value, minimum, maximum);
  
  short tx=x;
  for (tx=x; tx-x <= 5; tx++) {
  GLCD.DrawLine(tx+2, y-2, tx+2, y-62, WHITE);
  }
  //GLCD.FillRect(x+2, y+2, -59, 1, WHITE); //clear the bar
  
  long fill = map(value, minimum, maximum, 1, 61);
  fill = constrain(fill, 3, 61);

  
  for (tx=x; tx-x <= 4; tx++) {
  GLCD.DrawLine(tx+2, y-2, tx+2, y-fill, BLACK);
  }

  //GLCD.FillRect(x+2, y+2, -fill, 1, BLACK); //fill the bar with the value  
}


void BigGraphFill(float minimum, float maximum, float value, int y) {
    
  constrain(value, minimum, maximum);
  
  //GLCD.FillRect(2, y+31, 123, -28, WHITE); //clears the bar
  GLCD.FillRect(2 , y+25, 12, 4, BLACK);
  GLCD.FillRect(16, y+22, 14, 7, BLACK);
  GLCD.FillRect(32, y+19, 14, 10, BLACK);
  GLCD.FillRect(48, y+15, 14, 14, BLACK);
  GLCD.FillRect(64, y+12, 14, 17, BLACK);
  GLCD.FillRect(80, y+9, 14, 20, BLACK);
  GLCD.FillRect(96, y+5, 14, 24, BLACK);
  GLCD.FillRect(112, y+2, 13, 27, BLACK);
  
  long fill = map(value, minimum, maximum, 2, 126);
  fill = constrain(fill, 2, 122);

  GLCD.FillRect(fill, y+2, 126-fill, 26, WHITE); //fill the bar with the value (inverted)
//  GLCD.FillRect(2, y+2, 123, 27, WHITE);
//  GLCD.FillRect(2, y+2, fill, 27, BLACK); 
}

void fFuelc(int x, int y) { 
  getVss();
  getRpm();
  getInj();
    GLCD.CursorTo(x+6, y); 
    GLCD.Puts("               ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Fuel: ");
  if (vssk >= MinimumSpeed) {
    GLCD.Puts(FUELC);
    GLCD.Puts("L/100");
  }
  else {
    GLCD.Puts(FUELSC);
    GLCD.Puts("L/H");
  }
}

void fKph(int x, int y) {
    getVss();
    GLCD.CursorTo(x+6, y); 
    GLCD.Puts("               ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Speed: ");
    GLCD.Puts(VSSK);
    GLCD.Puts("KM/H");
}

void fMph(int x, int y) {
    getVss();
    GLCD.CursorTo(x+6, y); 
    GLCD.Puts("               ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Speed: ");
    GLCD.Puts(VSSM);
    GLCD.Puts("MPH");
}

void fTps(int x, int y) {
    getTps();
    GLCD.CursorTo(x+4, y); 
    GLCD.Puts("                 ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("TPS: ");
    GLCD.Puts(TPS);
    GLCD.Puts("%");    
}

void fRpm(int x, int y) {
    getRpm();
    GLCD.CursorTo(x+7, y); 
    GLCD.Puts("              ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Engine: ");
    GLCD.Puts(RPM);
    GLCD.Puts("RPM");    
}

void fDuty(int x, int y) {
    getRpm();
    getInj();
    GLCD.CursorTo(x+5, y); 
    GLCD.Puts("                 ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Duty: ");
    GLCD.Puts(DUTY);
    GLCD.Puts("%");    
}

void fEct(int x, int y) {
    getEct();
    GLCD.CursorTo(x+4, y); 
    GLCD.Puts("                  ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Water: ");
    GLCD.Puts(ECTC);
    GLCD.Puts("C");    
}

void fIat(int x, int y) {
    getIat();
    GLCD.CursorTo(x+4, y); 
    GLCD.Puts("                  ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("IAT: ");
    GLCD.Puts(IATC);
    GLCD.Puts("Â°C");    
}

void fMap(int x, int y) {
    getMap();
    GLCD.CursorTo(x+4, y); 
    GLCD.Puts("                  ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("MAP: ");
    GLCD.Puts(MAPMB);
    GLCD.Puts("mBar");    
}

void fInj(int x, int y) {
    getInj();
    GLCD.CursorTo(x+4, y); 
    GLCD.Puts("                 ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Inj: ");
    GLCD.Puts(INJ);
    GLCD.Puts("ms");    
}

void fIgn(int x, int y) {
    getIgn();
    GLCD.CursorTo(x+4, y); 
    GLCD.Puts("                  ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Ign: ");
    GLCD.Puts(IGN);
    GLCD.Puts("Deg");    
}

void fOilPressure(int x, int y) {
    floatToString(OilPressure, GetVDOPressure(analogRead(0)*4), 2, 0);
    GLCD.CursorTo(x+11, y); 
    GLCD.Puts("          ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Oil Press: ");
    GLCD.Puts(OilPressure);
    GLCD.Puts("BAR");    
}

void fOilTemperature(int x, int y) {
    floatToString(OilTemperature, GetShhTemp(analogRead(1)), 2, 0);
    //sprintf(OilTemperature,"%d",GetShhTemp(analogRead(1), 1));
    GLCD.CursorTo(x+9, y); 
    GLCD.Puts("            ");
    GLCD.CursorTo(x, y); 
    GLCD.Puts("Oil Temp: ");
    GLCD.Puts(OilTemperature);
    GLCD.Puts("C");    
}

void GlcdSplash() {
  GLCD.DrawBitmap(rzdash_splash, 0, 0, BLACK); //draw the bitmap at the given x,y position 
  GLCD.CursorTo(15, 0); 
  GLCD.Puts("V:");
  GLCD.CursorTo(17, 0); 
  GLCD.Puts(VERSION);
}

