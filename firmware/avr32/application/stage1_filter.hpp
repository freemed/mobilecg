#ifndef STAGE1FILTER_H_
#define STAGE1FILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 9000 Hz

fixed point precision: 32 bits

* 0 Hz - 220 Hz
  gain = 1
  desired ripple = 0.4 dB
  actual ripple = n/a

* 1500 Hz - 4500 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/

#define STAGE1FILTER_TAP_NUM 32

typedef struct {
  int history[STAGE1FILTER_TAP_NUM];
  unsigned int last_index;
} Stage1Filter;

void Stage1Filter_init(Stage1Filter* f);
void Stage1Filter_put(Stage1Filter* f, int input);
int Stage1Filter_get(Stage1Filter* f);

#endif
