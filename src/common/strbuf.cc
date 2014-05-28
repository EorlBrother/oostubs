/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S T R I N G B U F F E R                                       *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/strbuf.h"

Stringbuffer::Stringbuffer(){
	buffer = (char*) "";
	bufferLength = 0;
}

Stringbuffer::~Stringbuffer(){
}

void Stringbuffer::put (char c) {
	buffer[bufferLength] = c;
	bufferLength++;
	if(bufferLength>128 || c == '\n') {
		flush();
	}
}
