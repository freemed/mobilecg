CXXFLAGS = -O2
OBJS = baseline.o notch.o dsp.o

dsp.a: $(OBJS)
	ar rcs dsp.a $(OBJS)

test: baseline.o

clean:
	rm test *.o *.a
