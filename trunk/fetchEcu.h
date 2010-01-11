#ifndef FETCHECU
#define FETCHECU

    boolean bWaitingForAnswer = false;
    int *iCmdArray = &CROME14_ARRAY[0];
    int CurReq;
    long LastCommand = 0;
    float X = 0;
    unsigned char buffer = '\0';
    float fBuffer = 0;
    int TempInt = 0;
    float TempF = 0;
    int FastPollInterval = 25;
    int SlowPollInterval = 500;
    
 
void DataMode(int Mode) {
if (Mode == CROME12)
    {
	iCmdArray = &CROME12_ARRAY[0];
    }
else if (Mode == CROME14)
    {
	iCmdArray = &CROME14_ARRAY[0];
    }
else if (Mode == NG60)
    {
        iCmdArray = &NG60_ARRAY[0];
    }
}

void getEct() {
// Process ECT //
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > SlowPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(iCmdArray[ECT_IDX]);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = ECT_IDX;
          }
        }
        else
        {
	if ( Serial1.available() > 0 && CurReq == ECT_IDX )
	{
		fBuffer = Serial1.read();
		X = fBuffer * 5 / 256; // 5v / 255 bits = sensor range
		TempF = ( (0.1423 * X * X * X * X * X * X ) - (2.4938 * X * X * X * X * X) +
		          (17.837 * X * X * X * X) - (68.698 * X * X * X) +
		          (154.69 * X * X) - (232.75 * X) + 291.24);
		TempInt = TempF;
                ectf = TempInt;
		sprintf(ECTF,"%d",TempInt);

		//Display the result in Celsius
		TempInt = (TempF - 32) * 5 / 9;
                ectc = TempInt;
		sprintf(ECTC,"%d",TempInt);

		bWaitingForAnswer = false;
                Serial1.flush();
                LastPoll = millis();   
           }
        }
  }

void getIat() {
// Process IAT //
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > SlowPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(iCmdArray[IAT_IDX]);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = IAT_IDX;
          }
	}
	else
	{
        if ( Serial1.available() > 0 && CurReq == IAT_IDX )
        {
		fBuffer = Serial1.read();
		X = fBuffer * 5 / 256; // 5v / 255 bits = sensor range
                TempF = ( (0.1423 * X * X * X * X * X * X ) - (2.4938 * X * X * X * X * X) +
                          (17.837 * X * X * X * X) - (68.698 * X * X * X) +
                          (154.69 * X * X) - (232.75 * X) + 291.24);
                TempInt = TempF;
                sprintf(IATF,"%5d",TempInt);
                iatf = TempInt;

                //Display the result in Celsius
                TempInt = (TempF - 32) * 5 / 9;
                sprintf(IATC,"%d",TempInt);
                iatc = TempInt;
                bWaitingForAnswer = false;
                Serial1.flush();
                LastPoll = millis();   
            }
	    }
} 


void get02() {
// Process O2 //
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(iCmdArray[O2_IDX]);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = O2_IDX;
          }
        }
        else
        {
        if ( Serial1.available() > 0 && CurReq == O2_IDX )
        {
                fBuffer = Serial1.read();
                X = fBuffer;
                sprintf(O2,"%d",X);
                iatc = X;
                bWaitingForAnswer = false;
                Serial1.flush();
                LastPoll = millis();   
            }
        }
     }

void getBaro() {
// Process BARO //
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(iCmdArray[BARO_IDX]);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = BARO_IDX;
          }
	    }
	    else
	    {
            if ( Serial1.available() > 0 && CurReq == BARO_IDX )
            {
		// Display the Baro in HG
		fBuffer = Serial1.read();
		X = fBuffer * 5 / 256; // 5v / 255 bits = sensor range
                TempF = (3.6527 * X * X) + (20.349 * X) + 11.236;
                TempInt = TempF;
                sprintf(BAROP,"%d",TempInt);
                barop = TempInt;

                // Display the Baro in kPa
                TempInt = TempF/ 3.386389;
                sprintf(BAROK,"%d",TempInt);
                barok = TempInt;

                bWaitingForAnswer = false;
                Serial1.flush();
                LastPoll = millis();   
            }
	    }
    }

void getMap() {
// Process MAP //
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(iCmdArray[MAP_IDX]);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = MAP_IDX;
          }
	    }
	    else
	    {
            if ( Serial1.available() > 0 && CurReq == MAP_IDX )
              {
		fBuffer = Serial1.read();

                // Display the MAP in mBar
                TempInt = ((1764 / 255) * fBuffer);
                sprintf(MAPMB,"%d",TempInt);
                mapmb = TempInt;

                // Display the MAP in HG
		if( fBuffer <= 176 )
		{
		    TempF = (0.3469 * fBuffer) + 16.651;
	        }
	            else
	            {
		    TempF = (0.6938 * fBuffer) - 44.404;
	            }

                TempInt = TempF;
                sprintf(MAPHG,"%5d",TempInt);
                maphg = TempInt;
                
                bWaitingForAnswer = false;
                Serial1.flush();
                LastPoll = millis();   
              }
	    }
    }

void getTps() {
// process TPS //
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(iCmdArray[TPS_IDX]);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = TPS_IDX;
          }
	    }
	    else
	    {
            if ( Serial1.available() > 0 && CurReq == TPS_IDX )
            {
		TempF = Serial1.read();
/*		if( TempF > 250 ) //'250 = 4.49v, 4.49v = WOT
		{
			TempF = 250;
		}
		else if( TempF < 47 ) //47 = Closed Throttle
		{
			TempF = 47;
		}*/
//		TempInt = (0.4926 * TempF) - 23.153;
                TempInt = (0.5 * TempF) - 12;
                TempInt = constrain(TempInt, 0, 100);
                
		// Display the TPS
		sprintf(TPS,"%d",TempInt);
                tps = TempInt;

	        bWaitingForAnswer = false;
                Serial1.flush();
                LastPoll = millis();   
            }
	    }
        }
    
void getRpm() {
// Process RPM //
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(iCmdArray[RPMLOW_IDX]);
            Serial1.write(iCmdArray[RPMHIGH_IDX]);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = RPMLOW_IDX;
            }
	    }
	    else
	    {
            if ( Serial1.available() >= 2 && CurReq == RPMLOW_IDX )
            {
                unsigned int RpmLow = 0;
                unsigned int RpmHigh = 0;
	        RpmLow = Serial1.read();
                RpmHigh = Serial1.read();
		TempF = 1875000 / ((RpmHigh * 256) + RpmLow);

                     static short i = 0;
                     static int RPMlist[3] = {0,0,0};
                     int RPMsmoothed = 0; 
                     int RPMtotal = 0; 
                     TempInt = TempF;
                    
                     RPMlist[i] = TempInt ; //filling the list
                     i++;
                     if (i > 2)
                       i = 0;
                       
                     for (short n=0;n<=2;n++) { //making sum
                     RPMtotal +=  RPMlist[n];
                     }
                     
//                     RPMsmoothed = ((RPMtotal / 3) / 100);
                     RPMsmoothed = (TempF / 50);
                     RPMsmoothed = RPMsmoothed * 50;

                //Display the result in the field
                
                rpm = TempInt;
                sprintf(RPM,"%d",RPMsmoothed);

                bWaitingForAnswer = false;
                Serial1.flush();
                LastPoll = millis();   
            }
	    }
    }
    
void getVtec() {
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
                        Serial1.flush();
                	Serial1.write(iCmdArray[VTEC_IDX]);
                	bWaitingForAnswer = true;
                        LastCommand = millis();
                        CurReq = VTEC_IDX;
                    }
                }
		else
		{
            if ( Serial1.available() > 0 && CurReq == VTEC_IDX )
                 {
                	fBuffer = Serial1.read();
                        TempInt = fBuffer;
                        sprintf(VTEC,"%d",TempInt);
                        vtec = TempInt;
			bWaitingForAnswer = false;
                        Serial1.flush();
                        LastPoll = millis();   
		 }
		}
	
	}
void getLocam() {
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
                Serial1.flush();
            	Serial1.write(iCmdArray[LOCAM_IDX]);
            	bWaitingForAnswer = true;
                LastCommand = millis();
                CurReq = LOCAM_IDX;
          }
        	}
        	else
		{
                if ( Serial1.available() > 0 && CurReq == LOCAM_IDX )
        	{
	 	fBuffer = Serial1.read();
                X = fBuffer * 5 / 256; // 5v / 255 bits = sensor range
		//Display the result in the field
                TempInt = X;
                sprintf(LOCAM,"%d",TempInt);
                locam = TempInt;

		bWaitingForAnswer = false;
                Serial1.flush();
                LastPoll = millis();   
		}
	}
        }
        
void getHicam() {
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
                Serial1.flush();
            	Serial1.write(iCmdArray[HICAM_IDX]);
            	bWaitingForAnswer = true;
                LastCommand = millis();
                CurReq = HICAM_IDX;
                }
        	}
        	else
        	{
            		if ( Serial1.available() > 0 && CurReq == HICAM_IDX )
        		{
	 		//Display the result in the field
                	fBuffer = Serial1.read();
                	X = fBuffer * 5 / 256; // 5v / 255 bits = sensor range
                	TempInt = X;
                	sprintf(HICAM,"%d",TempInt);
                        hicam = TempInt;

			bWaitingForAnswer = false;
                        Serial1.flush();
                        LastPoll = millis();   
			}
		}
	}

void getCol() {
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
                Serial1.flush();
            	Serial1.write(iCmdArray[COL_IDX]);
            	bWaitingForAnswer = true;
                LastCommand = millis();
                CurReq = COL_IDX;
          }
        	}
        	else
        	{
            		if ( Serial1.available() > 0 && CurReq == COL_IDX )
        	{
                	fBuffer = Serial1.read();
	                X = fBuffer * 5 / 256; // 5v / 255 bits = sensor range
			//Display the result in the field
                	TempInt = X;
                	sprintf(COL,"%d",TempInt);
                        col = TempInt;

               	 	bWaitingForAnswer = false;
                        Serial1.flush();
                        LastPoll = millis();   
			}
		}
	}

void getVss() {
// process VSS //
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > SlowPollInterval) {
            LastPoll = millis();   
  
                        Serial1.flush();
			Serial1.write(iCmdArray[VSS_IDX]);
			bWaitingForAnswer = true;
                        LastCommand = millis();
                        CurReq = VSS_IDX;
                      }
		}
		else
		{
            		if ( Serial1.available() > 0 && CurReq == VSS_IDX )
			{
                	TempInt = Serial1.read();
                        
			//Display the result in Km/H
			sprintf(VSSK,"%d",TempInt);
                        vssk = TempInt;

			//Display the result in MpH
			TempInt = TempF * 0.62137;
			sprintf(VSSM,"%d",TempInt);
                        vssm = TempInt;

                        hundredkm = ((60 / (vssk / 60)) * 100) / 60;     //minutes needed to travel 100km

			bWaitingForAnswer = false;
                        Serial1.flush();
                        LastPoll = millis();   
			}
		}
    }

void getIgn() { //TODO//
// process IGN //
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
                        Serial1.flush();
			Serial1.write(iCmdArray[IGN_IDX]);
			bWaitingForAnswer = true;
                        LastCommand = millis();
                        CurReq = IGN_IDX;
                    }
		}
		else
		{
            		if ( Serial1.available() > 0 && CurReq == IGN_IDX )
			{
                	fBuffer = Serial1.read();
                        TempF = (0.25 * fBuffer) - 6;
                        
			//Display the result in Km/H
                        floatToString(IGN, TempF, 2, 0);
                        ign = TempF;
//                        sprintf(IGN,"%d",ign);

			bWaitingForAnswer = false;
                        Serial1.flush();
                        LastPoll = millis();   
			}
		}
    }
    

void getInj() {
  
static long LastPoll = 0;

	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > FastPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(iCmdArray[INJLOW_IDX]);
            Serial1.write(iCmdArray[INJHIGH_IDX]);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = INJLOW_IDX;
          }
	    }
	    else
	    {
            if ( Serial1.available() >= 2 && CurReq == INJLOW_IDX )
            {
	        unsigned int InjLow = Serial1.read();
                unsigned int InjHigh = Serial1.read();
                
//		TempF = 1920000 / ((InjHigh * 256) + InjLow);
		TempF = (InjHigh * 256) + InjLow;

//                inj = (TempF * 0.0017345794392523365 + 0.08354205607476633); //formula found on pgmfi.org
//                inj = TempF / 176; //formula by dip
                
                inj = TempF / 512;

                //Display the result in the field
                floatToString(INJ, inj, 4, 0);
                
                //Duty cycle
                duty = (rpm * inj) / 1200;          
                fuelc = (hundredkm * ((injsize / 100) * duty)) / 1000;     //fuel consumption in Liters per 100km
                fuelc = constrain(fuelc, 0, 50);
                floatToString(FUELC, fuelc, 2, 0);

                bWaitingForAnswer = false;
                Serial1.flush();
                LastPoll = millis();   
            }
       }

    }

#endif

