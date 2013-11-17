#ifndef STAGE3FILTER_H_
#define STAGE3FILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 1000 Hz

fixed point precision: 32 bits

* 0 Hz - 150 Hz
  gain = 1
  desired ripple = 0.4 dB
  actual ripple = n/a

* 250 Hz - 500 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/

#define STAGE3FILTER_TAP_NUM 32

typedef struct {
  int history[STAGE3FILTER_TAP_NUM];
  unsigned int last_index;
} Stage3Filter;

void Stage3Filter_init(Stage3Filter* f);
void Stage3Filter_put(Stage3Filter* f, int input);
int Stage3Filter_get(Stage3Filter* f);

#endif
