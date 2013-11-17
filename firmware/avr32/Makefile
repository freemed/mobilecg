include config.mk

main.hex: main
	avr32-strip main
	avr32-size main
	avr32-objcopy -O ihex main main.hex

main: drivers/drivers.a application/application.a drivers application
	cd application; make
	cd drivers; make
	avr32-gcc $(CFLAGS) application/application.a drivers/drivers.a -o main

program:

application/application.a:
	cd application; make

drivers/drivers.a:
	cd drivers; make

clean:
	rm -f *.o main *.hex
	cd application; make clean
	cd drivers; make clean

burn: main.hex
	my-dfu-programmer at$(PART) erase; my-dfu-programmer at$(PART) flash main.hex; my-dfu-programmer at$(PART) start

flash: main.hex
	my-dfu-programmer at$(PART) erase; my-dfu-programmer at$(PART) flash main.hex --debug 300

start:
	my-dfu-programmer at$(PART) start


rebuild: clean main.hex
