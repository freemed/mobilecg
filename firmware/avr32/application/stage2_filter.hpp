#ifndef STAGE2FILTER_H_
#define STAGE2FILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 3000 Hz

fixed point precision: 32 bits

* 0 Hz - 150 Hz
  gain = 1
  desired ripple = 0.4 dB
  actual ripple = n/a

* 500 Hz - 1500 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/

#define STAGE2FILTER_TAP_NUM 32

typedef struct {
  int history[STAGE2FILTER_TAP_NUM];
  unsigned int last_index;
} Stage2Filter;

void Stage2Filter_init(Stage2Filter* f);
void Stage2Filter_put(Stage2Filter* f, int input);
int Stage2Filter_get(Stage2Filter* f);

#endif
