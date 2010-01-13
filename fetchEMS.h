short StreamSize = 17;
short StreamCache[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned short StreamHeader = 0x55;
unsigned short StreamChecksum = 0;

void getStream() {

                        while (Serial1.read() != StreamHeader ) {
                          
                        }

            		if ( Serial1.available() >= StreamSize)
			{
  
                         for ( short i = 0; i < StreamSize-3; i++) {
                	StreamCache[i]  = Serial1.read();
                         }
                         
                        StreamChecksum = Serial1.read();
                        
			}

}

void processStream() {
  
  
  rpm =  StreamCache[0];
  rpm = map(rpm, 0, 255, 0, 26000);
  //
  mapk = StreamCache[1];
  mapk = map(mapk, 0, 255, 0, 176.67)+5.48;
  //
  tps = StreamCache[2];
  tps = map(tps, 0, 255, 0, 100);
  //
  iatf = StreamCache[3];
  iatf = map(iatf, 0, 255, -198, 260)+32;
  iatc = (iatf - 32) * (5/9) ;
  //
  ectf = StreamCache[4];
  ectf = map(ectf, 0, 255, -198, 260)+32;
  ectc = (ectf - 32) * (5/9);
  //
  ign = StreamCache[5];
  ign = map(ign, 0, 255, 0, 72.64)-17;
  //
  batt = StreamCache[6];
  batt = map(batt, 0, 255, 0, 16);
  //
  vssm = StreamCache[7];
  vssk = vssm * 1.6;
  //
  duty = StreamCache[8];
  duty = map(duty, 0, 255, 0, 250);
  //
  barok = StreamCache[9];
  barok = map(barok, 0, 255, 0, 127);
  //
  tcs = StreamCache[10];
  //
  gear = StreamCache[11];
  //
  boosttgt = StreamCache[12];
  boosttgt = map(boosttgt, 0, 255, 0, 176.67)+5.48;
  //
  o2 = StreamCache[13];
  o2 = map(o2, 0, 255, 0, 9.6797)+3.235;
  
}
