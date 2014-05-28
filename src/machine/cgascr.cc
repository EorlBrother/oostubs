/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"
#include "machine/io_port.h"
static IO_Port index(0x3d4);
static IO_Port data(0x3d5);
short PosX;
short PosY;

CGA_Screen::CGA_Screen(){
  CGA=(char*)0xB8000;
  attribute = 7;
  clear();
}

CGA_Screen::~CGA_Screen(){
}

void CGA_Screen::setpos (unsigned short x, unsigned short y) {
  y = y + x/80;
  x = x%80;
  if(y>39) {
    scrollup();
  }
  index.outw(14);
  data.outw((x+y*80)/256);
  index.outw(15);
  data.outw((x+y*80)%256);
  PosX = x;
  PosY = y;  
}

void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
  x = PosX;
  y = PosY;
}

void CGA_Screen::show (unsigned short x, unsigned short y, char character, unsigned char attribute) {
  if (character == '\n') {
    setpos(0,y+1);
  } else {
    unsigned int pos;
    pos = (y*80+x)*2;
    CGA[pos] = character;
    CGA[pos+1] = attribute;
    setpos(x+1,y); 
  }
}

void CGA_Screen::print (const char* string, unsigned int n) {
  unsigned short x;
  unsigned short y;
  for(unsigned int i=0; i<n; i++) {
    getpos(x,y);
    show(x,y,string[i], attribute);
  }
}

void CGA_Screen::scrollup () {
  for(unsigned int i = 0; i<80*39; i+=2) {
    CGA[i] = CGA[i+80*2];
    CGA[i+1] = CGA[i+80*2+1];
  }
  for(unsigned int i = 80*39; i<80*40; i+=2) {
    CGA[i] = ' ';
    CGA[i+1] = 7;
  }
  unsigned short x;
  unsigned short y;
  getpos(x,y);
  setpos(x,y-1);
}

void CGA_Screen::clear () {
  for(unsigned int i=0; i<80*40;i+=2){
    CGA[i] = ' ';
    CGA[i+1] = 7;
  }
  setpos(0,0);
}

void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  attribute = fgColor + (bgColor << 4) + (blink << 7);
}
