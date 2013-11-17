#VPATH=../application/

CXXFLAGS = -O2 -Wall -DPCTEST -lgtest_main
CXXFLAGS_O = -O2 -Wall -DPCTEST -c

TESTS = circular_buffer_test decimation_filter_test

all: $(TESTS)
	./circular_buffer_test
	./decimation_filter_test

#circular_buffer_test: circular_buffer_test.cpp ../application/circular_buffer.hpp
#	$(CXX) $(CXXFLAGS) circular_buffer_test.cpp -o circular_buffer_test

stage1_filter.o: ../application/stage1_filter.cpp
	$(CXX) $(CXXFLAGS_O) ../application/stage1_filter.cpp -o stage1_filter.o

stage2_filter.o: ../application/stage2_filter.cpp
	$(CXX) $(CXXFLAGS_O) ../application/stage2_filter.cpp -o stage2_filter.o

stage3_filter.o: ../application/stage3_filter.cpp
	$(CXX) $(CXXFLAGS_O) ../application/stage3_filter.cpp -o stage3_filter.o

decimation_filter_test: ../application/decimation_filter.hpp stage1_filter.o stage2_filter.o stage3_filter.o

#decimation_filter_test: decimation_filter_test.cpp ../application/decimation_filter.hpp
#	$(CXX) $(CXXFLAGS) decimation_filter_test.cpp -o decimation_filter_test
