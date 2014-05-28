/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       K E Y B O A R D                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "device/keyboard.h"

#include "object/imanager.h"
#include "common/panic.h"
#include "object/kout.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

void Keyboard::plugin(){
	// Keyboard keyboard;
	iManager.assign(PIC::keyboard, *this);
}

void Keyboard::trigger(){
	Key k = key_hit();

	if(k.valid()){
		if(k.ctrl() && k.alt() && k.scancode() == Key::scan::del){
			reboot();
		} else{
	 		kout.flush();
	 		unsigned short x,y;
	 		kout.getpos(x,y);
	 		kout.setpos(13,13);
	 		kout << k;
	 		kout.flush();
	 		kout.setpos(x,y);
	 	}
	}
	iManager.ack(PIC::keyboard);
}
