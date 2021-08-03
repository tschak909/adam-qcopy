/**
 * ADAM quick-copy main
 *
 * @author Thomas Cherryhomes
 * @email <thom.cherryhomes@gmail.com>
 */

#include <msx.h>
#include <conio.h>
#include <graphics.h>
#include <stdbool.h>
#include "smartkeys.h"
#include "eoslib.h"

#define DEV_DISK1 4
#define DEV_TAPE1 8

unsigned char buf[32][1024];

const char retrymsg="ANY KEY TO RETRY";

bool check_device(unsigned char dev)
{
  int e = eos_requeststatus(dev) & 0x7F;

  if (e!=0)
    cprintf("DEV %d - %s\n",dev,eos_statusmsg(eos_getrequestedstatus(e)));

  return e;
}

void blockstatus(int block)
{
  gotoxy(28,23); cprintf("%02X",block);
}

const char *readwrite(bool write)
{
  switch(write)
    {
    case false:
      return "READING";
    case true:
      return "WRITING";
    }
}

void dotapeop(int pass, unsigned char dev, bool write)
{
  int block, c, e;
  gotoxy(0,2); cprintf("%s %02X-%02X\n",readwrite(write),pass*32,pass*32+31);
  for (block=0;block<32;block++)
    {
      c = (pass*32) + block;
      while ((e = ((write == true) ? eos_writeblock(&buf[block],dev,c) : eos_readblock(&buf[block],dev,c))) > 0x80)
	{
	  // Error happened.
	  e &= 0x7F; // Strip off acknowledgement bit.
	  cprintf("ERROR %02x READING FROM DEV %d ",e,dev);
	  cprintf(retrymsg);
	  cgetc();
	  block--; // retry block
	} 
    }
}

void main(void)
{
  int pass;
  
  memset(buf,0,sizeof(buf));
  
  msx_color(15,5,5);
  msx_set_mode(2);

  // banner
  cprintf("COPY FROM DEVICE 4 TO 8\n\nINSERT TAPES\nAND PRESS ANY KEY\n");
  cgetc();

  // ask user to retry until tape ready.
  while (check_device(DEV_DISK1) > 0) { cprintf(retrymsg); cgetc(); };
  while (check_device(DEV_TAPE1) > 0) { cprintf(retrymsg); cgetc(); };

  clrscr();

  cprintf("COPYING FROM DEVICE 4 TO 8\n");

  for (pass=0;pass<8;pass++)
    {      
      dotapeop(pass,DEV_DISK1,false);
      dotapeop(pass,DEV_TAPE1,true);
    }

  cprintf("Done\n");
  
  for (;;) { }
  
}
