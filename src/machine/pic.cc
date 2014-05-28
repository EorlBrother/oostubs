/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/pic.h"
#include "machine/io_port.h"
#include "object/cpu.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */


PIC::PIC() {
  IO_Port ctrl_1(0x20), ctrl_2(0xa0), mask_1(0x21), mask_2(0xa1);

  //stößt initialisierung mit 3 zusätzlichen Kontrollwörtern an
  ctrl_1.outb(0x11);
  ctrl_2.outb(0x11);
  
  //Verschobener Bereich (bis 32 sind alle Adressen reserviert)
  mask_1.outb(32);
  mask_2.outb(40);
  
  //Master-Slave lokalisieren den jeweils anderen
  mask_1.outb(4);
  mask_2.outb(2);
  
  //Setzt Auto-EOI Modus
  mask_1.outb(2);
  mask_2.outb(2);
  
  //Setzt die Standardmaskierung
  mask_1.outb(0xFB);
  mask_2.outb(0xFF);

  //Interrupts müssen in der cpu erlaubt sein
  cpu.enable_int();  
}

PIC::~PIC(){
  cpu.disable_int();
}

void PIC::allow(Interrupts interrupt){
   IO_Port mask_1(0x21), mask_2(0xa1);
  IO_Port& mask = mask_1;
  unsigned char help;
  unsigned short i = interrupt-32;
  if(i<8) {
    //master
    mask = mask_1;
  } else {
    //slave
    mask = mask_2;
    i-=8;
  }
  help = mask.inb();
  help = (help & (~(1 << 1)));
  mask.outb(help);
}

void PIC::forbid(Interrupts interrupt){
  IO_Port mask_1(0x21), mask_2(0xa1);
  IO_Port& mask = mask_1;
  unsigned char help;
  unsigned short i = interrupt-32;
  if(i<8) {
    //master
    mask = mask_1;
  } else {
    //slave
    mask = mask_2;
    i-=8;
  }
  help = mask.inb();
  help = (help | (1 << i));
  mask.outb(help);
}

void PIC::ack(Interrupts interrupt){
  IO_Port ctrl_1(0x20), ctrl_2(0xa0);
  ctrl_1.outb(0x20);  
  if (interrupt>=40) {
    ctrl_2.outb(0x20);
  }
}
