CC=zcc +coleco -pragma-redirect:CRT_FONT=_font_8x8_msx_system -subtype=adam
AS=z88dk-z80asm

all: qcopy

clean:
	$(RM) -f qcopy *.o *.ddp *bin

smartkeys.o: smartkeys.c
	$(CC) -o smartkeys.o -c smartkeys.c

main.o: main.c
	$(CC) -o main.o -c main.c


qcopy: smartkeys.o main.o
	$(CC) -oqcopy -create-app smartkeys.o main.o