include ../config.mk

OPT = -O2
SRC = $(wildcard *.cpp)
CSRC = $(wildcard *.c)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
COBJ = $(patsubst %.c,%.o,$(CSRC))

application.a: $(OBJ) $(COBJ) stage1_filter.S
	ar rcs application.a $(OBJ) $(COBJ)

stage1_filter.S: stage1_filter.cpp
	$(CXX) $(CXXFLAGS) stage1_filter.cpp -S -c

clean:
	rm -f *.o *.a
