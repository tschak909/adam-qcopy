/**
 * A simple EOS binding library
 * 
 * @author Thomas Cherryhomes
 * @email <thom.cherryhomes@gmail.com>
 */

#include <conio.h>
#include <arch/z80.h>
#include "eoslib.h"

unsigned char eos_readblock(void* buf, unsigned char dev, unsigned long blockno)
{
  Z80_registers r;
  
  r.Bytes.A = dev;
  
  r.UWords.BC = blockno >> 16;
  r.UWords.DE = blockno & 0x0000FFFF;

  r.UWords.HL = buf;
  
  AsmCall(0xFCF3,&r,REGS_ALL,REGS_ALL);
  
  return r.Bytes.A;
}

unsigned char eos_writeblock(void* buf, unsigned char dev, unsigned long blockno)
{
  Z80_registers r;
  
  r.Bytes.A = dev;
  
  r.UWords.BC = blockno >> 16;
  r.UWords.DE = blockno & 0x0000FFFF;

  r.UWords.HL = buf;
  
  AsmCall(0xFCF6,&r,REGS_ALL,REGS_ALL);
  
  return r.Bytes.A;
}

unsigned char eos_requeststatus(unsigned char dev)
{
  Z80_registers r;
  
  r.Bytes.A = dev;

  AsmCall(0xFC7E,&r,REGS_AF,REGS_AF);

  return r.Bytes.A;
}

unsigned char eos_getrequestedstatus(unsigned char dev)
{
  Z80_registers r;
  
  r.Bytes.A = dev;

  AsmCall(0xFCE4,&r,REGS_AF,REGS_AF);

  return r.Bytes.A;
}

const char *eos_statusmsg(unsigned char error)
{
  switch(error)
    {
    case 1: return "CRC ERROR";
    case 2: return "MISSING BLOCK";
    case 3: return "MISSING MEDIA";
    case 4: return "MISSING DRIVE";
    case 5: return "WRITE PROTECTED";
    case 6: return "DRIVE ERROR";
    }
}
