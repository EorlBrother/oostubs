/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/o_stream.h"

O_Stream::O_Stream() : Stringbuffer(), fgColor(WHITE), bgColor(BLACK), blink(false), base(dec){
  fgColor = 7;
  bgColor = 0;
  blink = false;
  base = dec;
}

O_Stream::~O_Stream(){
}

O_Stream& O_Stream::operator << (char value) {
  put(value);
  return *this;
}

O_Stream& O_Stream::operator << (unsigned char value) {
  return *this << (char)value;
}

O_Stream& O_Stream::operator << (char* value) {
  return *this << (const char*)value;
}

O_Stream& O_Stream::operator << (const char* value) {
  for (unsigned int i=0; value[i]!=0;i++) {
    put(value[i]);
  }
  return *this;
}

O_Stream& O_Stream::operator << (short value) {
  return *this << (long)value;
}

O_Stream& O_Stream::operator << (unsigned short value) {
  return *this << (unsigned long)value;
}


O_Stream& O_Stream::operator << (int value) {
  return *this << (long)value;
}

O_Stream& O_Stream::operator << (unsigned int value) {
  return *this << (unsigned long)value;

}

O_Stream& O_Stream::operator << (long value) {
  char* tmp;
  int i=0;
  while (value>=base) {
    int x = value%base;
    if (x>=10) {
      tmp[i] = x+55;
    } else {
      tmp[i] = x+'0';
    }
    value = value/base;
    i++;
  }
  int x = value%base;
  if (x>=10) {
    tmp[i] = x+55;
  } else {
    tmp[i] = x+'0';
  }
  value = value/base;
  while(i>=0) {
    put(tmp[i]);
    i--;
  }

  return *this;;
}

O_Stream& O_Stream::operator << (unsigned long value) {
  return *this << (long)value;
}

O_Stream& O_Stream::operator << (void* value) {
  *this << hex << (unsigned long) value;
  return *this;
}

O_Stream& O_Stream::operator << (FGColor color){
  flush();
  fgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}

O_Stream& O_Stream::operator << (BGColor color){
  flush();
  bgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}

O_Stream& O_Stream::operator << (Blink blink){
  flush();
  this->blink = blink.blink;
  setAttributes(fgColor, bgColor, this->blink);
  return *this;
}

O_Stream& endl (O_Stream& os) {
  return os << '\n';
}


O_Stream& bin (O_Stream& os) {
  os.base = O_Stream::bin;
  return os;
}


O_Stream& oct (O_Stream& os) {
  os.base = O_Stream::oct;
  return os;
}


O_Stream& dec (O_Stream& os) {
  os.base = O_Stream::dec;
  return os;
}


O_Stream& hex (O_Stream& os) {
  os.base = O_Stream::hex;
  return os;
}

O_Stream& O_Stream::operator << (O_Stream& (*f) (O_Stream&)) {
  return f(*this);
}
