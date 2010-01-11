
void CheckEcu() {
  
}


void Menu1(int interval) {
if (BarCreated == false) {
//HBarGraphFrame(0, 9);
//HBarGraphFrame(0, 25);
HBarGraphFrame(0, 41);
HBarGraphFrame(0, 57);
BarCreated = true; 
}


if (millis() - previousMillis[3] > interval) {
previousMillis[3] = millis();
//fRpm(0, 0);
//rpm = 5600;
//HBarGraphFill(0, 9500, rpm, 0, 9);
//fDuty(0, 2);
//duty = 34;
//HBarGraphFill(0, 100, duty, 0, 25);

GLCD.CursorTo(0, 0); 
GLCD.Puts("       ");
GLCD.CursorTo(0, 0); 
GLCD.PrintNumber(analogRead(1));
GLCD.CursorTo(0, 2); 
GLCD.Puts("       ");
GLCD.CursorTo(0, 2); 
GLCD.PrintNumber(analogRead(0)*4);
fOilTemperature(0, 4);
HBarGraphFill(0, 180, int(GetShhTemp(analogRead(1))+30), 0, 41);
fOilPressure(0, 6);
HBarGraphFill(0, 100, GetVDOPressure(analogRead(0)*4)*10, 0, 57);
   }
}

void Menu2(int interval) {
if (millis() - previousMillis[3] > interval) {
previousMillis[3] = millis();   
fRpm(0, 0);
fIgn(0, 1);
fKph(0, 2);
fInj(0, 3);
fDuty(0, 4);
fFuelc(0, 5);
fEct(0, 6);
//fTps(0, 7);
}
}

void Menu3(int interval) {
if (BarCreated == false) {
HBarGraphFrame(0, 9);
HBarGraphFrame(0, 25);
HBarGraphFrame(0, 41);
HBarGraphFrame(0, 57);
BarCreated = true;
}
if (millis() - previousMillis[3] > interval) {
previousMillis[3] = millis();
fRpm(0, 0);
HBarGraphFill(0, 8500, rpm, 0, 9);
fTps(0, 2);
HBarGraphFill(0, 100, tps, 0, 25);
fIat(0, 4);
HBarGraphFill(0, 80, iatc, 0, 41);
fMap(0, 6);
HBarGraphFill(0, 1100, mapmb, 0, 57);
}
}

void Menu4(int interval) {
if (BarCreated == false) {
GLCD.CursorTo(0, 5); 
GLCD.Puts("K");
GLCD.CursorTo(0, 6); 
GLCD.Puts("P");
GLCD.CursorTo(0, 7); 
GLCD.Puts("H");
VBarGraphFrame(7, 63);
GLCD.CursorTo(3, 5); 
GLCD.Puts("T");
GLCD.CursorTo(3, 6); 
GLCD.Puts("P");
GLCD.CursorTo(3, 7); 
GLCD.Puts("S");
VBarGraphFrame(25, 63);
GLCD.CursorTo(6, 4); 
GLCD.Puts("O");
GLCD.CursorTo(6, 5); 
GLCD.Puts("I");
GLCD.CursorTo(6, 6); 
GLCD.Puts("L");
GLCD.CursorTo(6, 7); 
GLCD.Puts("T");
VBarGraphFrame(43, 63);
GLCD.CursorTo(9, 5); 
GLCD.Puts("E");
GLCD.CursorTo(9, 6); 
GLCD.Puts("C");
GLCD.CursorTo(9, 7); 
GLCD.Puts("T");
VBarGraphFrame(61, 63);
GLCD.CursorTo(12, 5); 
GLCD.Puts("I");
GLCD.CursorTo(12, 6); 
GLCD.Puts("A");
GLCD.CursorTo(12, 7); 
GLCD.Puts("T");
VBarGraphFrame(79, 63);
GLCD.CursorTo(15, 5); 
GLCD.Puts("M");
GLCD.CursorTo(15, 6); 
GLCD.Puts("A");
GLCD.CursorTo(15, 7); 
GLCD.Puts("P");
VBarGraphFrame(97, 63);
GLCD.CursorTo(18, 5); 
GLCD.Puts("R");
GLCD.CursorTo(18, 6); 
GLCD.Puts("P");
GLCD.CursorTo(18, 7); 
GLCD.Puts("M");
VBarGraphFrame(115, 63);
BarCreated = true;
}
if (millis() - previousMillis[3] > interval) {
previousMillis[3] = millis();   
getVss();
VBarGraphFill(0, 255, vssk, 7, 63);
getTps();
VBarGraphFill(0, 100, tps, 25, 63);
//
VBarGraphFill(0, 180, int(GetShhTemp(analogRead(1))+30), 43, 63);
getEct();
VBarGraphFill(0, 120, ectc, 61, 63);
getIat();
VBarGraphFill(0, 85, iatc, 79, 63);
getMap();
VBarGraphFill(0, 1100, mapmb, 97, 63);
getRpm();
VBarGraphFill(0, 8500, rpm, 115, 63);
}
}


void Menu5(int interval) {
if (BarCreated == false) {
BigGraphFrame(0);
BigGraphFrame(32);
BarCreated = true;
}
if (millis() - previousMillis[3] > interval) {
previousMillis[3] = millis();

getRpm();
getVss();
getInj();

BigGraphFill(0, 8500, rpm, 0);
GLCD.CursorTo(1, 1); 
GLCD.Puts(RPM);

BigGraphFill(0, 23, fuelc, 32);
GLCD.CursorTo(1, 5); 
GLCD.Puts(FUELC);
}
}


void ShowMenu(int interval) {
  switch(CurMenu){
  case 0:
//      Menu0(1);
      break;
   case 1:
      Menu1(interval);
      break;
   case 2:
      Menu2(interval);
      break;
   case 3:
      Menu3(interval);
      break;
   case 4:
      Menu4(interval);
      break;
   case 5:
      Menu5(interval);
      break;
   default:
//      Menu1(interval);
      break;  
  }
}

void NextMenu() {
  if ( CurMenu >= 5) {
  CurMenu = 1; 
  GlcdClear();
}
  
  else {
  CurMenu++; 
  GlcdClear();}
}

