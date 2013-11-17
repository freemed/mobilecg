#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#ifndef PCTEST
#include <interrupt_avr32.h>
#endif

template<int buffer_size>
class CircularBuffer
{
public:
	CircularBuffer():
		in_index(0),
		out_index(0)
	{
	}
	
	bool pushBytes(const char* data, int size)
	{
		#ifndef PCTEST
		Disable_global_interrupt();
		#endif
		if(freeBytes() < size)
		{
			#ifndef PCTEST
			Enable_global_interrupt();
			#endif
			return false;
		}
		for(int i = 0; i < size; i++)
		{
			buffer_[in_index] = data[i];
			in_index++;
			if(in_index == buffer_size)
				in_index = 0;
		}
		#ifndef PCTEST
		Enable_global_interrupt();
		#endif
		return true;
	}
	
	bool popBytes(char* data, int size)
	{
		if(bytesInBuffer() < size)
			return false;
		for(int i = 0; i < size; i++)
		{
			data[i] = buffer_[out_index];
			out_index++;
			if(out_index == buffer_size)
				out_index = 0;
		}
		return true;
	}

	int freeBytes() const
	{
		return buffer_size - bytesInBuffer() - 1;
	}

private:
	char buffer_[buffer_size];
	int in_index;
	int out_index;

	int bytesInBuffer() const
	{
		return (in_index-out_index+buffer_size) % buffer_size;
	}
};

#endif
