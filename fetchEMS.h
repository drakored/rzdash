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
  
  
  StreamCache[0] = rpm;
  rpm = map(rpm, 0, 255, 0, 26000);
  //
  StreamCache[1] = mapk;
  mapk = map(mapk, 0, 255, 0, 176.67)+5.48;
  //
  StreamCache[2]  = tps;
  tps = map(tps, 0, 255, 0, 100);
  //
  StreamCache[3]  = iatf;
  iatf = map(iatf, 0, 255, -198, 260)+32;
  iatc = (iatf - 32) * (5/9) ;
  //
  StreamCache[4]  = ectf;
  ectf = map(ectf, 0, 255, -198, 260)+32;
  ectc = (ectf - 32) * (5/9);
  //
  StreamCache[5]  = ign;
  ign = map(ign, 0, 255, 0, 72.64)-17;
  //
  StreamCache[6]  = batt;
  batt = map(batt, 0, 255, 0, 16);
  //
  StreamCache[7]  = vssm;
  vssk = vssm * 1.6;
  //
  StreamCache[8]  = duty;
  duty = map(duty, 0, 255, 0, 250);
  //
  StreamCache[9]  = barok;
  barok = map(barok, 0, 255, 0, 127);
  //
  StreamCache[10]  = tcs;
  //
  StreamCache[11]  = gear;
  //
  StreamCache[12]  = boosttgt;
  boosttgt = map(boosttgt, 0, 255, 0, 176.67)+5.48;
  //
  StreamCache[13]  = o2;
  o2 = map(o2, 0, 255, 0, 9.6797)+3.235;
  
}
