#include "gtest/gtest.h"
#include "../application/decimation_filter.hpp"
#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int squareWave(float Hz, int k, int amp)
{
	float p = 9000.0/Hz;
	return fmod(k, p) > p/2.0 ? amp : -amp;
}

int sineWave(float Hz, int k, int amp)
{
	float p = 9000.0/Hz;
	return (int)(sin(k*2*M_PI/p)*(double)amp);
}


TEST(DecimationFilterTest, SizeCheck)
{
	DecimationFilter f;
	int i = 0;
	int outcnt = 0;
	for(; i < 18*100; i++)
	{
		f.put(0);
		if(f.available())
			outcnt++;
	}
	EXPECT_EQ(outcnt, 100);
}

TEST(DecimationFilterTest, DCTest)
{
	DecimationFilter f;
	int i = 0;
	int initial = 18*1000;
	for(; i < initial; i++)
	{
		int input = 100000000;
		f.put(input);
	}
	for(; i < initial + 18*4; i++)
	{
		int input = 100000000;
		f.put(input);
		if(f.available())
		{
			EXPECT_LT(fabs(100000000-f.get())/100000000.0, 0.002);
		}
	}
}

float getFilteredAmplitude(float Hz)
{
	DecimationFilter f;
	int i = 0;
	int p = 9000/Hz;
	int initial = 18*p*10;
	for(; i < initial; i++)
	{
		int input = sineWave(Hz, i, 100000000);
		f.put(input);
	}
	int amp = 0;
	for(; i < initial + initial; i++)
	{
		int input = sineWave(Hz, i, 100000000);
		f.put(input);
		//if(f.available())
		{
			int a = (int)fabs(f.get());
			if(a > amp)
				amp = a;
		}
	}
	return amp / 100000000.0;
}

TEST(DecimationFilterTest, FreqTest)
{
	FILE *f = fopen("freq.txt", "w");
	for(float i = 1; i < 4500; i += 5)
	{
		double dB = 20*log10(getFilteredAmplitude(i));
		if(i < 150)
			EXPECT_LT(fabs(dB), 0.1);
		if(i > 250)
			EXPECT_LT(dB, -55);
		fprintf(f, "%lf %lf\n", i, dB);
	}
	fclose(f);
}

