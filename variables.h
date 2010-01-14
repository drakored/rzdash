#ifndef RZVAR
#define RZVAR

#define eepromSize 2048

/*==============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/
 
 // Hardware stuff
 #define ButtonA 56 //analog 2
 #define ButtonB 57 //analog 3
 #define LcdReset 40
 #define BackLightPin 2 //pwm
 #define SoundPin 11 //pwm
 const int ledCount = 9;  // the number of LEDs in the bar graph
 const int BarGraphPins[] = {44, 45, 46, 47, 48, 49, 50, 51, 52};   // an array of pin numbers to which LEDs are attached
 //
 
 // Settings
 short ButtonAbyte = 0;
 short ButtonBbyte = 0;
 short BackLight = 35;
 int ShifterRpm = 7500;
 long previousMillis[4] = {0,0,0,0};
 long beepTime = 0;
 int beepDuration = 0;
 boolean beepIsOn = false;
 boolean beep = false;
 boolean shiftlight = true;
 const int ShifterPin =  13;
 const int VtecPin =  12;
 static int BarId = 0;
 boolean splash = true;
 boolean Bar = false;
 boolean BarCreated = false;
 int CurMenu = 4; //startup menu
 short SerialRelayStep = 0;
 //


 //Lookup Table for the Oil pressure: (11 Values) 
//from 0-10Bar in steps of 1Bar, the list is in 12Bit Digital Reading when supplyed with 5V and a 200Ohm Resistor in series  
//(measuring the Voltage on the Sensor) 
//it has a increasing Resistance with the Pressure.
//const unsigned int tempVDOPressure[] =  { 195,  549,  845,  1073,  1271,  1427,  1567,  1686,  1794,  1881,  1962};
const unsigned int tempVDOPressure[] =  { 1962, 1881, 1794, 1686, 1567, 1427, 1271, 1073, 845, 549, 195 };

//Lookup Table for the Oil temperature (22 Values) Its Calibration curve 92-027-006 
//from -30Â°C-180Â°C in steps of 10Â°C, the list is in 12Bit Digital Reading when supplyed with 5V and a 200Ohm Resistor in series  
//(measuring the Voltage on the Sensor) 
//it has a decreasing Resistance with the Temperature
//const unsigned int tempVDOTemp[] =  { 4053,  4019,  3957,  3857,  3706,  3497,  3224,  2893,  2527,  2150,  1790,  1471,  1200,  968,  782,  632,  515,  422,  348,  287,  238,  199};
const unsigned int tempVDOTemp[] =  { 199, 238, 287, 348, 422, 515, 632, 782, 968, 1200, 1471, 1790, 2150, 2527, 2893, 3224, 3497, 3706, 3857, 3957, 4019, 4053 };

const unsigned int tempFuelLevel[] =  { 2527, 3497, 4053 };

float duty = 0;     //injectors duty cycle
float kph = 0;     //speed in kph
float hundredkm = 0; //= ((60 / (kph / 60)) * 100) / 60;     //minutes needed to travel 100km
float injsize = 230 * 4;     //injectors size x 4 (one per cylinder)
float fuelc = 0; //fuel consumption

int ectc = 0;
int ectf = 0;
int iatc = 0;
int iatf = 0;
int o2 = 0;
int barop = 0;
int barok = 0;
int mapk = 0;
int maphg = 0;
int mapmb = 0;
int tps = 0;
int rpm = 0;
int vtec = 0;
int locam = 0;
int hicam = 0;
int col = 0;
int vssk = 0;
int vssm = 0;
int tcs = 0;
int gear = 0;
int boosttgt = 0;
float ign = 0;
float inj = 0;
float batt = 0;


char msg[]="";

char ECTC[]="000";
char ECTF[]="000";
char IATC[]="000";
char IATF[]="000";
char O2[]="000";
char BAROP[]="000";
char BAROK[]="000";
char MAPHG[]="000";
char MAPMB[]="0000";
char TPS[]="000";
char RPM[]="00000";
char VTEC[]="00000";
char LOCAM[]="00000";
char HICAM[]="00000";
char COL[]="00000";
char VSSK[]="000";
char VSSM[]="000";
char IGN[]="00000";
char INJ[]="0000000";
char FUELC[]="000.00";
char DUTY[]="00.00";

char OilTemperature[]="000.00";
char OilPressure[]="00.00";

#endif

