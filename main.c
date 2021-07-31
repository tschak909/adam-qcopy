/**
 * ADAM quick-copy main
 *
 * @author Thomas Cherryhomes
 * @email <thom.cherryhomes@gmail.com>
 */

#include <msx.h>
#include <conio.h>
#include <graphics.h>
#include "smartkeys.h"

void main(void)
{
  char test[32];
  
  msx_color(1,7,7);
  msx_set_mode(2);

  cprintf("          QUICK COPY          \n");

  smartkeys_display("",
		    "TAPE1",
		    "TAPE2",
		    "DISK1",
		    "DISK2",
		    "");

  msx_color(1,7,7);
  gotoxy(0,2);
  cprintf("     SOURCE DEVICE: ");
  cgets(test);
  cprintf("DESTINATION DEVICE: ");
  cgets(test);
}
