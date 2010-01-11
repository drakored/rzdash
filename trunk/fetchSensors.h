#ifndef FETCHSENSORS
#define FETCHSENSORS

int AnalogPollInterval = 100;

//Converts the ADW Reading into 0.1Bar (must be divided by 10 for Bar)
float GetVDOPressure(int ADWreading) {
 static long LastPoll = 0;  
 static short i = 0;
 static short ADlist[10] = {0,0,0,0,0,0,0,0,0,0};
 static short ADsmoothed = 0; 
 static int ADtotal = 0; 

if (millis() - LastPoll > AnalogPollInterval) {
    LastPoll = millis();
    
 ADlist[i] = ADWreading; //filling the list
 i++;
 if (i > 9)
   i = 0;
}

 short n;
 ADtotal = 0; 
 for (n=0;n<=9;n++) { //making sum
 ADtotal +=  ADlist[n];
 }
 
 ADsmoothed = ADtotal / 10;
 
{  
  float LookedupValue;
  float L1;
  float L2;
  //This searches the 2 surrounding values, and then linear interpolates between them.  
  for(int i = 0; i<=10; i++)
  {   
    if(ADsmoothed <= tempVDOPressure[i] && ADsmoothed >= tempVDOPressure[i+1])  
  {    
    L1 = (tempVDOPressure[i] - ADsmoothed);  
    L2 = (tempVDOPressure[i] - tempVDOPressure[i+1]);  
    LookedupValue = i + (L1 / L2); 
    break;   
    }
    
    
    if(ADsmoothed <= tempVDOPressure[11])  
  {    
    LookedupValue = 10;    
    break;   
    }
    if(ADsmoothed >= tempVDOPressure[0])  
  {    
    LookedupValue = 0;   
    break;   
    }
    
  }     
  
    return LookedupValue; 
 }
}


float GetVDOTemp(int ADWreading) {
  
 static long LastPoll = 0;  
 static short i = 0;
 static short ADlist[10] = {0,0,0,0,0,0,0,0,0,0};
 static short ADsmoothed = 0; 
 static int ADtotal = 0; 

if (millis() - LastPoll > AnalogPollInterval) {
    LastPoll = millis();
    
 ADlist[i] = ADWreading; //filling the list
 i++;
 if (i > 9)
   i = 0;
}
   
 short n;
 ADtotal = 0; 
 for (n=0;n<=9;n++) { //making sum
 ADtotal +=  ADlist[n];
 }
 
 ADsmoothed = ADtotal / 10;
{   
  float LookedupValue;  
  //This searches the 2 surrounding values, and then linear interpolates between them.  
  for(int i = 0; i<=21;i++)  
  {   
    if(ADsmoothed >= tempVDOTemp[i] && ADsmoothed <= tempVDOTemp[i+1])   
    {    
    LookedupValue = (i*10) + ((10L *(ADsmoothed - tempVDOTemp[i])) / (tempVDOTemp[i+1] - tempVDOTemp[i]));    
    break;   
    }  
     
    if(ADsmoothed <= tempVDOTemp[0])  
  {    
    LookedupValue = 180;    
    break;   
    }
    if(ADsmoothed >= tempVDOTemp[21])  
  {    
    LookedupValue = 0;   
    break;   
    }
  }
  LookedupValue = LookedupValue - 30;   //must be reduced as the lookup table starts at -30Â°C.   

    return LookedupValue;
  }
}



float GetShhTemp(int ADWreading) {
  
 static long LastPoll = 0;  
 static short i = 0;
 static short ADlist[10] = {0,0,0,0,0,0,0,0,0,0};
 static short ADsmoothed = 0; 
 static int ADtotal = 0; 

if (millis() - LastPoll > AnalogPollInterval) {
    LastPoll = millis();
    
 ADlist[i] = ADWreading; //filling the list
 i++;
 if (i > 9)
   i = 0;
}
   
 short n;
 ADtotal = 0; 
 for (n=0;n<=9;n++) { //making sum
 ADtotal +=  ADlist[n];
 }
 
 ADsmoothed = ADtotal / 10;
 
 // Inputs ADC Value from Thermistor and outputs Temperature in Celsius
 // Utilizes the Steinhart-Hart Thermistor Equation:
 //    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
 //    where A = 0.001290270270476, B = 0.000272311205607 and C = 0.000000114541874 
 //    values for the AutoGauge temperature sensor. Precise to 0.1Â°C. http://www.thermistor.com/calculators.php?r=sheccr
 //    LowerTemp C	MidrangeTemp C	UpperTemp C	Resistance@ 25Â° C	ThermistorCurve
 //    -30	          60	            150	            1,666	        Y (-3.9%/C @ 25C)
 //
 // Schematic:
 // [Ground] ---- [10k-Resister] -------|------- [Thermistor] ---- [+5v]
 //                                     |
 //                                Analog Pin 1
 //
 long Resistance;  float Temp;  // Dual-Purpose variable to save space.
 Resistance=((10240000/ADsmoothed) - 10000);  // Assuming a 10k Thermistor.  Calculation is actually: Resistance = (1024/ADC) 
 Temp = log(Resistance); // Saving the Log(resistance) so not to calculate it 4 times later. // "Temp" means "Temporary" on this line.
 Temp = 1 / (0.001290270270476 + (0.000272311205607 * Temp) + (0.000000114541874 * Temp * Temp * Temp));   // Now it means both "Temporary" and "Temperature"
 Temp = Temp - 273.15;  // Convert Kelvin to Celsius                                         // Now it only means "Temperature"

 // Uncomment this line for the function to return Fahrenheit instead.
 //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert to Fahrenheit
 
 if (Temp <= -30)
   Temp = -30;
   
 if (Temp >= 150)
   Temp = 150;
 
 return Temp;  // Return the Temperature 
}

float GetFuelLevel(int ADWreading) {
  
 static long LastPoll = 0;    
 static short i = 0;
 static short ADlist[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 static short ADsmoothed = 0; 
 static short ADtotal = 0; 

if (millis() - LastPoll > AnalogPollInterval) {
    LastPoll = millis();
    
 ADlist[i] = ADWreading; //filling the list
 i++;
 if (i > 99)
   i = 0;
}
   
 short n;
 ADtotal = 0;
 for (n=0;n<=99;n++) {
 ADtotal +=  ADlist[n];
 }
 
 ADsmoothed = ADtotal / 100;
 ADtotal = 0; 
{   
  float LookedupValue;  
  //This searches the 2 surrounding values, and then linear interpolates between them.  
  for(int i = 0; i<2;i++)  
  {   
    if(ADsmoothed >= tempFuelLevel[i] && ADsmoothed <= tempFuelLevel[i+1])   
    {    
    LookedupValue = (i*33) + ((10L *(ADsmoothed - tempFuelLevel[i])) / (tempFuelLevel[i+1] - tempFuelLevel[i]));    
    break;   
    }  
     
    if(ADsmoothed <= tempVDOTemp[0])  
  {    
    LookedupValue = 100;    
    break;   
    }
    if(ADsmoothed >= tempVDOTemp[21])  
  {    
    LookedupValue = 0;   
    break;   
    }
  }
    return LookedupValue;
  }
}

#endif

