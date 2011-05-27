/*==============================================================================
 * FUNCTIONS                                                                
 *============================================================================*/


//sets stock ECU's serial speed to 38400
void serialSetEcu38400() {
const uint8_t setspeed[] = {0x82, 0x0F};
  Serial1.begin(9600);
  Serial1.write(setspeed, 2);
  
  Serial1.begin(38400);
}
 
// checks if ECU has custom eeprom
boolean serialCheckEcu() {
int buffer;  
            Serial1.write(0x4B);
            delay(500);
               
            buffer = Serial1.read();    

            if (buffer == 0x02) {
              return true;
            }
//            if (fBuffer == 0x00)
            else {
              return false;
            }
            Serial1.flush();
            delay(200);
}


// avoid locking for longer than value
void serialTimeout(int value) {
  if (millis() - LastCommand > value) {  
  Serial.flush();
  Serial1.flush();  
  bWaitingForAnswer = false; }
}

void serialFastRelay() {
// step 1: Read command from laptop & copy command to ECU.
// step 2: Read result from ECU & copy result to laptop.
// This mode is faster, it sends/receives more than one byte at a time, limited to 4 bytes per cycle. (more bytes add delay)
short i;

	if ( !bWaitingForAnswer && SerialRelayStep == 0 && Serial.available() > 0 )
	{
	for (i=4; Serial.available() && i; i--) {
	Serial1.write(Serial.read()); }
	bWaitingForAnswer = true; //locking
        LastCommand = millis();
        SerialRelayStep = 1;
        CurReq = 100;
        }

        
        if ( bWaitingForAnswer && SerialRelayStep == 1 && CurReq == 100 && Serial1.available() > 0 )
	{
	for (i=4; Serial1.available() && i; i--) {
            Serial.write(Serial1.read()); }

        SerialRelayStep = 0; //2, done
	bWaitingForAnswer = false; //releasing lock
        }
}

void serialRelay() {
// step 1: Read command from laptop.
// step 2: Copy command to ECU.
// step 3: Read result from ECU.
// step 4: Copy result to laptop.
// This mode is slow but 100% reliable

	if ( !bWaitingForAnswer && SerialRelayStep == 0 && Serial.available() > 0 )
	{
	    fBuffer = Serial.read();
	    bWaitingForAnswer = true; //locking
            LastCommand = millis();
            Serial.flush();
            SerialRelayStep = 1;
            CurReq = 100;
        }
           
        if ( bWaitingForAnswer && SerialRelayStep == 1 && CurReq == 100 )
	{
            Serial1.write(fBuffer);
            //Serial1.flush();
            SerialRelayStep++; //2
        }
        
        if ( bWaitingForAnswer && SerialRelayStep == 2 && CurReq == 100 && Serial1.available() > 0 )
	{
            fBuffer = Serial1.read();
            Serial1.flush();
            SerialRelayStep++; //3
        }
        if ( bWaitingForAnswer && SerialRelayStep == 3 && CurReq == 100 )
	{
            Serial.write(fBuffer);
            //Serial.flush();
            SerialRelayStep = 0; //4, done
            bWaitingForAnswer = false; //releasing lock
        }
}

