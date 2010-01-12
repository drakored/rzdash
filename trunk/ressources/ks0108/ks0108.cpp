/*
  ks0108.cpp - Arduino library support for ks0108 and compatable graphic LCDs
  Copyright (c)2008 Michael Margolis All right reserved
  mailto:memargolis@hotmail.com?subject=KS0108_Library 

  The high level functions of this library are based on version 1.1 of ks0108 graphics routines
  written and copyright by Fabian Maximilian Thiele. His sitelink is dead but
  you can obtain a copy of his original work here:
  http://www.scienceprog.com/wp-content/uploads/2007/07/glcd_ks0108.zip

  Code changes include conversion to an Arduino C++ library, rewriting the low level routines 
  to read busy status flag and support a wider range of displays, adding more flexibility
  in port addressing and improvements in I/O speed. The interface has been made more Arduino friendly
  and some convenience functions added. 

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Version:   1.0 - May 8  2008  - first release
  Version:   1.1 - Nov 7  2008  - restructured low level code to adapt to panel speed
                                 - moved chip and panel configuration into seperate header files    
								 - added fixed width system font
  Version:   1.2 - May 26 2009   - added support Mega and Sanguino
     
*/

extern "C" {
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <wiring.h> // added 18 Sept 2008 for Arduino release 0012
}

#define ksSOURCE
#include "ks0108.h"


#define EN_DELAY() asm volatile( "ldi r24, %0 \n\t" "subi r24, 0x1 \n\t" "and r24, r24 \n\t" "brne .-6 \n\t" ::"M" (EN_DELAY_VALUE) : "r24" )
// the (EN_DELAY_VALUE) argument for the above delay is in ks-0108_panel.h

// the following macros are for performance testing and will be removed in the release code
#ifdef DEBUG_LOGGING
#define DEBUG_PIN_HIGH(_pin)  //fastWriteHigh(_pin);
#define DEBUG_PIN_LOW(_pin)   //fastWriteLow(_pin);
#include <hardwareserial.h>

void showHex(char *fun, byte val){
return;
  Serial.print(fun);
  Serial.print(">");
  Serial.print(val,HEX);
  Serial.print('|');
}


void showXY(char *fun, byte x, byte y){
  uint8_t pos = x % 64;
  if( (pos <= 1) || (pos >=63) ){
    Serial.print(fun);
    Serial.print(":x=");
    Serial.print(x,DEC);
    Serial.print(",y=");
    Serial.print(y,DEC);
    Serial.print("| ");
  }
}
#endif
//#define GLCD_DEBUG  // uncomment this if you want to slow down drawing to see how pixels are set

void ks0108::ClearPage(uint8_t page, uint8_t color){
	for(uint8_t x=0; x < DISPLAY_WIDTH; x++){	
	   GotoXY(x, page * 8);
       this->WriteData(color);
   }	
}

void ks0108::ClearScreenX(uint8_t color){
 uint8_t page;
  //for( page=0; page < DISPLAY_HEIGHT / 8; page++)
   for( page = 0; page < 8; page++){
	  GotoXY(0, page * 8);
	  ClearPage(page, color);
 }
}

void ks0108::DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color) {
	uint8_t length, i, y, yAlt, xTmp, yTmp;
	int16_t m;
	//
	// vertical line
	//
	if(x1 == x2) {
		// x1|y1 must be the upper point
		if(y1 > y2) {
			yTmp = y1;
			y1 = y2;
			y2 = yTmp;
		}
		this->DrawVertLine(x1, y1, y2-y1, color);
	
	//
	// horizontal line
	//
	} else if(y1 == y2) {	
		// x1|y1 must be the left point
		if(x1 > x2) {
			xTmp = x1;
			x1 = x2;
			x2 = xTmp;
		}
		this->DrawHoriLine(x1, y1, x2-x1, color);
	
	//
	// angled line :)
	//
	} else {
		// angle >= 45°
		if((y2-y1) >= (x2-x1) || (y1-y2) >= (x2-x1)) {
			// x1 must be smaller than x2
			if(x1 > x2) {
				xTmp = x1;
				yTmp = y1;
				x1 = x2;
				y1 = y2;
				x2 = xTmp;
				y2 = yTmp;
			}
		
			length = x2-x1;		// not really the length :)
			m = ((y2-y1)*200)/length;
			yAlt = y1;
			
			for(i=0; i<=length; i++) {
				y = ((m*i)/200)+y1;
				
				if((m*i)%200 >= 100)
					y++;
				else if((m*i)%200 <= -100)
					y--;
				
				this->DrawLine(x1+i, yAlt, x1+i, y, color);
				
				if(length <= (y2-y1) && y1 < y2)
					yAlt = y+1;
				else if(length <= (y1-y2) && y1 > y2)
					yAlt = y-1;
				else
					yAlt = y;
			}
		
		// angle < 45°
		} else {
			// y1 must be smaller than y2
			if(y1 > y2) {
				xTmp = x1;
				yTmp = y1;
				x1 = x2;
				y1 = y2;
				x2 = xTmp;
				y2 = yTmp;
			}
			
			length = y2-y1;
			m = ((x2-x1)*200)/length;
			yAlt = x1;
			
			for(i=0; i<=length; i++) {
				y = ((m*i)/200)+x1;
				
				if((m*i)%200 >= 100)
					y++;
				else if((m*i)%200 <= -100)
					y--;
				
				this->DrawLine(yAlt, y1+i, y, y1+i, color);
				if(length <= (x2-x1) && x1 < x2)
					yAlt = y+1;
				else if(length <= (x1-x2) && x1 > x2)
					yAlt = y-1;
				else
					yAlt = y;
			}
		}
	}
}

void ks0108::DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
	DrawHoriLine(x, y, width, color);				// top
	DrawHoriLine(x, y+height, width, color);		// bottom
	DrawVertLine(x, y, height, color);			// left
	DrawVertLine(x+width, y, height, color);		// right
}

void ks0108::DrawRoundRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t radius, uint8_t color) {
  	int16_t tSwitch, x1 = 0, y1 = radius;
  	tSwitch = 3 - 2 * radius;
	
	while (x1 <= y1) {
	    this->SetDot(x+radius - x1, y+radius - y1, color);
	    this->SetDot(x+radius - y1, y+radius - x1, color);

	    this->SetDot(x+width-radius + x1, y+radius - y1, color);
	    this->SetDot(x+width-radius + y1, y+radius - x1, color);
	    
	    this->SetDot(x+width-radius + x1, y+height-radius + y1, color);
	    this->SetDot(x+width-radius + y1, y+height-radius + x1, color);

	    this->SetDot(x+radius - x1, y+height-radius + y1, color);
	    this->SetDot(x+radius - y1, y+height-radius + x1, color);

	    if (tSwitch < 0) {
	    	tSwitch += (4 * x1 + 6);
	    } else {
	    	tSwitch += (4 * (x1 - y1) + 10);
	    	y1--;
	    }
	    x1++;
	}
	  	
	this->DrawHoriLine(x+radius, y, width-(2*radius), color);			// top
	this->DrawHoriLine(x+radius, y+height, width-(2*radius), color);	// bottom
	this->DrawVertLine(x, y+radius, height-(2*radius), color);			// left
	this->DrawVertLine(x+width, y+radius, height-(2*radius), color);	// right
}

/*
 * Hardware-Functions 
 */
void ks0108::FillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
	uint8_t mask, pageOffset, h, i, data;
	height++;
	
	pageOffset = y%8;
	y -= pageOffset;
	mask = 0xFF;
	if(height < 8-pageOffset) {
		mask >>= (8-height);
		h = height;
	} else {
		h = 8-pageOffset;
	}
	mask <<= pageOffset;
	
	this->GotoXY(x, y);
	for(i=0; i<=width; i++) {
		data = this->ReadData();
		
		if(color == BLACK) {
			data |= mask;
		} else {
			data &= ~mask;
		}

		this->WriteData(data);
	}
	
	while(h+8 <= height) {
		h += 8;
		y += 8;
		this->GotoXY(x, y);
		
		for(i=0; i<=width; i++) {
			this->WriteData(color);
		}
	}
	
	if(h < height) {
		mask = ~(0xFF << (height-h));
		this->GotoXY(x, y+8);
		
		for(i=0; i<=width; i++) {
			data = this->ReadData();
		
			if(color == BLACK) {
				data |= mask;
			} else {
				data &= ~mask;
			}
	
			this->WriteData(data);
		}
	}
}

void ks0108::InvertRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	uint8_t mask, pageOffset, h, i, data, tmpData;
	height++;
	
	pageOffset = y%8;
	y -= pageOffset;
	mask = 0xFF;
	if(height < 8-pageOffset) {
		mask >>= (8-height);
		h = height;
	} else {
		h = 8-pageOffset;
	}
	mask <<= pageOffset;
	
	this->GotoXY(x, y);
	for(i=0; i<=width; i++) {
		data = this->ReadData();
		tmpData = ~data;
		data = (tmpData & mask) | (data & ~mask);
		this->WriteData(data);
	}
	
	while(h+8 <= height) {
		h += 8;
		y += 8;
		this->GotoXY(x, y);
		
		for(i=0; i<=width; i++) {
			data = this->ReadData();
			this->WriteData(~data);
		}
	}
	
	if(h < height) {
		mask = ~(0xFF << (height-h));
		this->GotoXY(x, y+8);
		
		for(i=0; i<=width; i++) {
			data = this->ReadData();
			tmpData = ~data;
			data = (tmpData & mask) | (data & ~mask);
			this->WriteData(data);
		}
	}
}

void ks0108::SetInverted(boolean invert) {  // changed type to boolean
	if(this->Inverted != invert) {
		this->InvertRect(0,0,DISPLAY_WIDTH-1,DISPLAY_HEIGHT-1);
		this->Inverted = invert;
	}
}

void ks0108::SetDot(uint8_t x, uint8_t y, uint8_t color) {
	uint8_t data;
	
	this->GotoXY(x, y-y%8);					// read data from display memory
  	
	data = this->ReadData();
	if(color == BLACK) {
		data |= 0x01 << (y%8);				// set dot
	} else {
		data &= ~(0x01 << (y%8));			// clear dot
	}	
	this->WriteData(data);					// write data back to display
}

//
// Font Functions
//

uint8_t ReadPgmData(const uint8_t* ptr) {  // note this is a static function
	return pgm_read_byte(ptr);
}

void ks0108::SelectFont(const uint8_t* font,uint8_t color, FontCallback callback) {
	this->Font = font;
	this->FontRead = callback;
	this->FontColor = color;
}

void ks0108::PrintNumber(long n){
   byte buf[10];  // prints up to 10 digits  
   byte i=0;
   if(n==0)
	   PutChar('0');
   else{
	 if(n < 0){
        PutChar('-');
		n = -n;
	 }
     while(n>0 && i <= 10){
	   buf[i++] = n % 10;  // n % base
	   n /= 10;   // n/= base
	 }
	 for(; i >0; i--)
		 this->PutChar((char) (buf[i-1] < 10 ? '0' + buf[i-1] : 'A' + buf[i-1] - 10));	  
   }
}

int ks0108::PutChar(char c) {
	uint8_t width = 0;
	uint8_t height = this->FontRead(this->Font+FONT_HEIGHT);
	uint8_t bytes = (height+7)/8;
	
	uint8_t firstChar = this->FontRead(this->Font+FONT_FIRST_CHAR);
	uint8_t charCount = this->FontRead(this->Font+FONT_CHAR_COUNT);
	
	uint16_t index = 0;
	uint8_t x = this->Coord.x, y = this->Coord.y;
	
	if(c < firstChar || c >= (firstChar+charCount)) {
		return 1;
	}
	c-= firstChar;

	if( this->FontRead(this->Font+FONT_LENGTH) == 0 && this->FontRead(this->Font+FONT_LENGTH+1) == 0) {
    // zero length is flag indicating fixed width font (array does not contain width data entries)
	   width = this->FontRead(this->Font+FONT_FIXED_WIDTH); 
	   index = c*bytes*width+FONT_WIDTH_TABLE;
	}
	else{
	// variable width font, read width data, to get the index
	   for(uint8_t i=0; i<c; i++) {  
		 index += this->FontRead(this->Font+FONT_WIDTH_TABLE+i);
	   }
	   index = index*bytes+charCount+FONT_WIDTH_TABLE;
	   width = this->FontRead(this->Font+FONT_WIDTH_TABLE+c);
    }

	// last but not least, draw the character
	for(uint8_t i=0; i<bytes; i++) {
		uint8_t page = i*width;
		for(uint8_t j=0; j<width; j++) {
			uint8_t data = this->FontRead(this->Font+index+page+j);
		
			if(height > 8 && height < (i+1)*8) {
				data >>= (i+1)*8-height;
			}
			
			if(this->FontColor == BLACK) {
				this->WriteData(data);
			} else {
				this->WriteData(~data);
			}
		}
		// 1px gap between chars
		if(this->FontColor == BLACK) {
			this->WriteData(0x00);
		} else {
			this->WriteData(0xFF);
		}
		this->GotoXY(x, this->Coord.y+8);
	}
	this->GotoXY(x+width+1, y);

	return 0;
}

void ks0108::Puts(char* str) {
	int x = this->Coord.x;
	while(*str != 0) {
		if(*str == '\n') {
			this->GotoXY(x, this->Coord.y+this->FontRead(this->Font+FONT_HEIGHT));
		} else {
			this->PutChar(*str);
		}
		str++;
	}
}

void ks0108::Puts_P(PGM_P str) {
	int x = this->Coord.x;
	while(pgm_read_byte(str) != 0) {
		if(pgm_read_byte(str) == '\n') {
			this->GotoXY(x, this->Coord.y+this->FontRead(this->Font+FONT_HEIGHT));
		} else {
			this->PutChar(pgm_read_byte(str));
		}
		str++;
	}
}

uint8_t ks0108::CharWidth(char c) {
	uint8_t width = 0;
	uint8_t firstChar = this->FontRead(this->Font+FONT_FIRST_CHAR);
	uint8_t charCount = this->FontRead(this->Font+FONT_CHAR_COUNT);
	
	// read width data
	if(c >= firstChar && c < (firstChar+charCount)) {
		c -= firstChar;
		width = this->FontRead(this->Font+FONT_WIDTH_TABLE+c)+1;
	}
	
	return width;
}

uint16_t ks0108::StringWidth(char* str) {
	uint16_t width = 0;
	
	while(*str != 0) {
		width += this->CharWidth(*str++);
	}
	
	return width;
}

uint16_t ks0108::StringWidth_P(PGM_P str) {
	uint16_t width = 0;
	
	while(pgm_read_byte(str) != 0) {
		width += this->CharWidth(pgm_read_byte(str++));
	}
	
	return width;
}

void ks0108::CursorTo( uint8_t x, uint8_t y){    // 0 based coordinates for fixed width fonts (i.e. systemFont5x7)
   GotoXY( x * (this->FontRead(this->Font+FONT_FIXED_WIDTH)+1),
	       y * (this->FontRead(this->Font+FONT_HEIGHT)+1)
		 ) ; 
}

boolean ks0108::GotoXY(uint8_t x, uint8_t y) {
	//uint8_t chip, cmd;
	
	if( (x > DISPLAY_WIDTH-1) || (y > DISPLAY_HEIGHT-1) )	// exit if coordinates are not legal
	   return false; // in the published version this returns without a value
//	Serial.println();
//	showXY("gtxy:prev", Coord.x,Coord.y);	
	this->Coord.x = x;								// save new coordinates
	this->Coord.y = y;
	this->Coord.page = y/8;

//showXY("gtxy", x,y);

/*
  if(y/8 != this->Coord.page) {
	  	this->Coord.page = y/8;
	cmd = LCD_SET_PAGE | this->Coord.page;			// set y address on all chips	
	for(chip=0; chip < DISPLAY_WIDTH/CHIP_WIDTH; chip++){
	   this->WriteCommand(cmd, chip);	
	}
  }
	chip = this->Coord.x/CHIP_WIDTH;
	x = x % CHIP_WIDTH;
	cmd = LCD_SET_ADD | x;
	this->WriteCommand(cmd, chip);					// set x address on active chip	
*/
   return true;  // add this

}

void ks0108::Init(boolean invert) {  
	pinMode(D_I,OUTPUT); 	
    pinMode(R_W,OUTPUT); 	
    pinMode(EN,OUTPUT); 	
    pinMode(CSEL1,OUTPUT);
    pinMode(CSEL2,OUTPUT);

	delay(10);

	fastWriteLow(D_I);		// I
	fastWriteLow(R_W);		// W
	fastWriteLow(EN);
    lcdDataDir(0xFF);

	this->Coord.x = 0;
	this->Coord.y = 0;
	this->Coord.page = 0;
	
	this->Inverted = invert;
	
	for(uint8_t chip=0; chip < DISPLAY_WIDTH/CHIP_WIDTH; chip++){
       delay(10);  
	   this->WriteCommand(LCD_ON, chip);				// power on
	   this->WriteCommand(LCD_DISP_START, chip);		// display start line = 0
	}

	// -- Addition for Frame Buffer --
	uint8_t i, j;
	for (j = 0; j < DISPLAY_PAGE; j++)
		for (i = 0; i < DISPLAY_WIDTH; i++)
			vram[j][i] = 0;
	page = 0;
	// -- End Addition --

	delay(12);										// Original 10ms -> 12ms
	this->ClearScreen();							// display clear
	this->GotoXY(0,0);
}

/*
__inline__ void ks0108::SelectChip(uint8_t chip) {  
static uint8_t prevchip; 
	
	if(prevchip == chip)
		return;
	
	if(chipSelect[chip] & 1) {
	   fastWriteHigh(CSEL1);
	   fastWriteLow(CSEL2);
	}
	
	else {
	   fastWriteLow(CSEL1);
	   fastWriteHigh(CSEL2);
	}
	prevchip = chip; 
}
*/

__inline__ void ks0108::SelectChip(uint8_t chip) {  
//static uint8_t prevchip; 
	if(chipSelect[chip] & 1) {
       fastWriteHigh(CSEL1);
       //EN_DELAY(); 
       }
	else {
	   fastWriteLow(CSEL1);
	   //EN_DELAY(); 
	   }

	if(chipSelect[chip] & 2) {
       fastWriteHigh(CSEL2);
       //EN_DELAY(); 
       }
       
	else {
	   fastWriteLow(CSEL2); 
	   //EN_DELAY(); 
	   }
}


void ks0108::WaitReady( uint8_t chip){
	// wait until LCD busy bit goes to zero

    SelectChip(chip);
	lcdDataDir(0x00);
	fastWriteLow(D_I);		// I
	fastWriteHigh(R_W);		// Read
	fastWriteHigh(EN); 	
    //asm volatile("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" ::);
	EN_DELAY();
	while(LCD_DATA_IN_HIGH & LCD_BUSY_FLAG)
		;
	fastWriteLow(EN); 	
	fastWriteLow(R_W);		// Back to W
    lcdDataDir(0xFF);

}

 __inline__ void ks0108::Enable(void) {  
   EN_DELAY();
   fastWriteHigh(EN);					// EN high level width min 450 ns
   EN_DELAY();
   fastWriteLow(EN);
   //EN_DELAY(); // some displays may need this delay at the end of the enable pulse
}


inline uint8_t ks0108::ReadData(void) {  
	if (!Inverted)
		return vram[Coord.page][Coord.x];
	else
		return ~vram[Coord.page][Coord.x];
}

void ks0108::WriteCommand(uint8_t cmd, uint8_t chip) {
// if(this->Coord.x % CHIP_WIDTH == 0 && chip > 0){ 		// todo , ignore address 0???
//    EN_DELAY();
//   }
//	this->WaitReady(chip);
	SelectChip(chip);
  
	fastWriteLow(D_I);					// I
	fastWriteLow(R_W);					// W
//    lcdDataDir(0xFF);
//	EN_DELAY();
    lcdDataOut(cmd);
   this->Enable();						// enable
//  EN_DELAY();
//	lcdDataOut(0x00);
}


void ks0108::WriteData(uint8_t data) {
	uint8_t displayData, yOffset;

	GotoXY(this->Coord.x, this->Coord.y);
//	if(this->Coord.x >= DISPLAY_WIDTH)
//		return;

	yOffset = this->Coord.y%8;

	if(yOffset != 0) {
		// first page
		displayData = this->ReadData();
		displayData |= data << yOffset;
		if(this->Inverted)
			displayData = ~displayData;
		//lcdDataOut( displayData);					// write data
		//this->Enable();								// enable
		
		// second page
    // New code
    if( ! this->GotoXY(this->Coord.x, this->Coord.y+8) )
      {
    this->Coord.x++;
    return;
      }
    // -- end new code

		// -- Addition for Frame Buffer --
		vram[Coord.page][Coord.x] = displayData;  // Write back vram
		
		// second page
		this->GotoXY(this->Coord.x, this->Coord.y+8);
		displayData = this->ReadData();
		displayData |= data >> (8-yOffset);
		if(this->Inverted)
			displayData = ~displayData;
		//lcdDataOut(displayData);		// write data
		//this->Enable();					// enable
		// -- Addition for Frame Buffer --
		vram[Coord.page][Coord.x] = displayData;
		
		//this->GotoXY(this->Coord.x+1, this->Coord.y-8);
		Coord.x++;
		Coord.y -= 8;
	} else {
		// just this code gets executed if the write is on a single page
		if(this->Inverted)
			data = ~data;	  
        //EN_DELAY();
		//lcdDataOut(data);				// write data
		//this->Enable();					// enable
		// -- Addition for Frame Buffer --
		vram[Coord.page][Coord.x] = data;
		this->Coord.x++;
	    //showXY("WrData",this->Coord.x, this->Coord.y); 
	}

}

void ks0108::Update()
{
	uint8_t colum, x, cmd;
	uint8_t displayData, iter;
	static uint8_t chip = 0;

      for (iter = 0; iter <= 8; iter++)
      {
              cmd = LCD_SET_PAGE | page;
              this->WriteCommand(cmd, chip);
              cmd = LCD_SET_ADD | 0;
              this->WriteCommand(cmd, chip);
              fastWriteHigh(D_I);			// D/I = 1 (Data)
              
                for (colum = 0; colum < CHIP_WIDTH; colum++)
                {
                  if (chip == 0)
                    x = colum;
                  else
                    x = colum + CHIP_WIDTH;
                  displayData = vram[page][x];
                  //EN_DELAY();
                  lcdDataOut(displayData);
                  this->Enable();
                }   
    
        page++;
        
        if (page >= DISPLAY_PAGE) {
          page = 0;
          chip++;
          }
          
        if (chip >= DISPLAY_WIDTH/CHIP_WIDTH) {
          chip = 0; 
          }
    }
}



/*
void ks0108::Update()
{
	uint8_t chip, colum, x, cmd;
	uint8_t displayData, iter;

  for (iter = 0; iter <= 8; iter++)
  {

    for (chip = 0; chip < DISPLAY_WIDTH/CHIP_WIDTH ; chip++)
    {
    
      //delay(1);
      cmd = LCD_SET_PAGE | page;
      this->WriteCommand(cmd, chip);
      cmd = LCD_SET_ADD | 0;
      this->WriteCommand(cmd, chip);
      fastWriteHigh(D_I);			// D/I = 1 (Data)
        for (colum = 0; colum < CHIP_WIDTH; colum++)
        {
          if (chip == 0)
            x = colum;
          else
            x = colum + CHIP_WIDTH;
          displayData = vram[page][x];
          EN_DELAY();
          lcdDataOut(displayData);
          this->Enable();
        }
    }
    
    page++;
    if (page >= DISPLAY_PAGE)
      page = 0;
  }
}
*/

/*
void ks0108::Update()
{
	uint8_t chip, colum, x, cmd;
	uint8_t displayData;

	for (chip = 0; chip < DISPLAY_WIDTH/CHIP_WIDTH ; chip++)
	{
		cmd = LCD_SET_PAGE | page;
		this->WriteCommand(cmd, chip);
		cmd = LCD_SET_ADD | 0;
		this->WriteCommand(cmd, chip);
		fastWriteHigh(D_I);			// D/I = 1 (Data)
		for (colum = 0; colum < CHIP_WIDTH; colum++)
		{
			if (chip == 0)
				x = colum;
			else
				x = colum + CHIP_WIDTH;
			displayData = vram[page][x];
			//EN_DELAY();
			lcdDataOut(displayData);
			this->Enable();
		}
	}
	page++;
	if (page >= DISPLAY_PAGE)
		page = 0;
}
*/

void ks0108::DrawBitmap(const uint8_t * bitmap, uint8_t x, uint8_t y, uint8_t color){
uint8_t width, height;
uint8_t i, j;

  width = ReadPgmData(bitmap++); 
  height = ReadPgmData(bitmap++);
  for(j = 0; j < height / 8; j++) {
     this->GotoXY(x, y + (j*8) );
	 for(i = 0; i < width; i++) {
		 uint8_t data = ReadPgmData(bitmap++);
	   	 if(color == BLACK)
			this->WriteData(data);
		 else
		    this->WriteData(~data);
	 }
  }
}

// class wrapper

ks0108::ks0108(){
  this->Inverted=0;
}

// Make one instance for the user
ks0108 GLCD = ks0108();
 
