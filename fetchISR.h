short ISRSizeMain = 38;
short ISRSizeSec = 15;
short ISRCacheMain[38] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
short ISRCacheSec[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned short ISRChecksum = 0;

void fetchISRMain {
  
  	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > SlowPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(0x20);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = 0x20;
          }
        }
  
        if ( Serial1.available() >= ISRSizeMain && CurReq == 0x20)
        {  
            for ( short i = 0; i < ISRSizeMain-2; i++) {
            ISRCacheMain[i]  = Serial1.read();
            }
              
        ISRChecksum = Serial1.read();
	bWaitingForAnswer = false;
        Serial1.flush();
              
        }
}

void fetchISRSec {
  
  	if ( !bWaitingForAnswer )
	{
          if (millis() - LastPoll > SlowPollInterval) {
            LastPoll = millis();   
  
            Serial1.flush();
            Serial1.write(0x30);
            bWaitingForAnswer = true;
            LastCommand = millis();
            CurReq = 0x30;
          }
        }
  
        if ( Serial1.available() >= ISRSizeSec && CurReq == 0x30)
        {  
            for ( short i = 0; i < ISRSizeSec-2; i++) {
            ISRCacheSec[i]  = Serial1.read();
            }
              
        ISRChecksum = Serial1.read();
	bWaitingForAnswer = false;
        Serial1.flush();
              
        }
  
}


void processISRMain {
  
}


void processISRSec {
  
}

