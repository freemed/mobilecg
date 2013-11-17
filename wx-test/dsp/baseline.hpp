#ifndef BASELINE_H_
#define BASELINE_H_

class BaselineIIR
{
public:
	BaselineIIR()
	{
		reset();
	}
	void reset()
	{
		for(int i = 0; i < NCoef+1; i++)
			x[i] = y[i] = 0;	
	}
	float filter(float NewSample);
private:
	static const int NCoef = 2;
	float y[NCoef+1]; //output samples
	float x[NCoef+1]; //input samples	
};

#endif
