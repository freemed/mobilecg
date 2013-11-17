include ../config.mk

OPT = -Os
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC)) exception.o

drivers.a: $(OBJ)
	ar rcs drivers.a $(OBJ)

clean:
	rm -f *.o *.a

