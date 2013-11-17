
#OS = LINUX
OS = MACOSX
#OS = WINDOWS

PROG = testapp

# To set up Ubuntu Linux to cross compile for Windows:
#
#    apt-get install mingw32 mingw32-binutils mingw32-runtime
#
# Just edit the variable above for WINDOWS, then use "make" to build rawhid.exe

ifeq ($(OS), LINUX)
TARGET = $(PROG)
CC = gcc
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS)
LIBS = -lusb
else ifeq ($(OS), MACOSX)
TARGET = driver.a
CC = gcc
CXX = g++
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS)
LIBS = -framework IOKit -framework CoreFoundation
else ifeq ($(OS), WINDOWS)
TARGET = $(PROG).exe
CC = i586-mingw32msvc-gcc
STRIP = i586-mingw32msvc-strip
CFLAGS = -Wall -O2 -DOS_$(OS)
LIBS = -lhid -lsetupapi
endif

OBJS = $(PROG).o hid.o ecg_driver.o usb_packets.o

CFLAGS += -lpthread
CXXFLAGS = $(CFLAGS)

all: $(TARGET)

driver.a: $(OBJS) $(PROG)
	ar rcs driver.a $(OBJS)

$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $(CXXFLAGS) $(OBJS) $(LIBS)
	$(STRIP) $(PROG)

$(PROG).exe: $(PROG)
	cp $(PROG) $(PROG).exe

$(PROG).dmg: $(PROG)
	mkdir tmp
	cp $(PROG) tmp
	hdiutil create -ov -volname "Raw HID Test" -srcfolder tmp $(PROG).dmg

hid.o: hid_$(OS).c hid.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(PROG) $(PROG).exe $(PROG).dmg *.a
	rm -rf tmp

