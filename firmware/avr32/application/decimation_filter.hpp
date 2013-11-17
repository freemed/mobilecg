#ifndef DECIMATION_FILTER_H
#define DECIMATION_FILTER_H

#include "stage1_filter.hpp"
#include "stage2_filter.hpp"
#include "stage3_filter.hpp"

class DecimationFilter
{
public:

	DecimationFilter()
	{
		Stage1Filter_init(&stage1);
		Stage2Filter_init(&stage2);
		Stage3Filter_init(&stage3);
		cnt1 = cnt2 = cnt3 = 0;
	}
	
	void put(int input)
	{
		Stage1Filter_put(&stage1, input);
		if(++cnt1 == 3)
		{
			cnt1 = 0;
			input = Stage1Filter_get(&stage1);
		}
		else return;

		Stage2Filter_put(&stage2, input);
		if(++cnt2 == 3)
		{
			cnt2 = 0;
			input = Stage2Filter_get(&stage2);
		}
		else return;

		Stage3Filter_put(&stage3, input);
		if(++cnt3 == 2)
			cnt3 = 0;
	}
	
	bool available()
	{
		return cnt1 == 0 && cnt2 == 0 && cnt3 == 0;
	}
	
	int get()
	{
		return Stage3Filter_get(&stage3);
	}

private:
	Stage1Filter stage1;
	Stage2Filter stage2;
	Stage3Filter stage3;
	int cnt1, cnt2, cnt3;
};

#endif
