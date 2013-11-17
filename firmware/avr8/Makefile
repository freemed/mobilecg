CC=avr-gcc
CFLAGS=-mmcu=attiny24 -Os -Wall -std=c99

main.hex: main main.asm
	avr-objcopy -O ihex main main.hex
	avr32-size main.hex

main:

main.asm: main.c
	$(CC) $(CFLAGS) -S main.c -o main.asm

burn: main.hex
	avrdude -p attiny24 -c usbtiny -U flash:w:main.hex

fuse: 
	avrdude -p attiny24 -c usbtiny -U lfuse:w:0x3f:m

clean:
	rm main main.hex
