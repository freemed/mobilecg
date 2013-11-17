PART = uc64d4

INCLUDE = -I /usr/local/avr32/include
INCLUDE += -I .
INCLUDE += -I ../drivers

OPT = -O1
BASEFLAGS = -Wall $(OPT) -fomit-frame-pointer $(INCLUDE) -mpart=$(PART) -T $(PART).ld -DBOARD=USER_BOARD
BASEFLAGS += -fmessage-length=0 -ffunction-sections -Wl,--gc-sections -Wl,--strip-all
CXXFLAGS = $(BASEFLAGS) -fno-rtti -fno-exceptions
CFLAGS = $(BASEFLAGS) -std=gnu99
ASFLAGS = $(CFLAGS)
LDFLAGS = -T $(PART).ld -Wl,--gc-sections -Wl,--strip-all
#LDFLAGS = -Wl,-e,_trampoline

CC = avr32-gcc
CXX = avr32-gcc
