#ifndef NOTCH_H_
#define NOTCH_H_

class NotchIIR
{
public:
	NotchIIR()
	{
		for(int i = 0; i < NCoef+1; i++)
			xv[i] = yv[i] = 0;
	}
	float filter(float NewSample);
private:
	static const int NCoef = 2;
	float yv[NCoef+1]; //output samples
	float xv[NCoef+1]; //input samples	
};

#endif
