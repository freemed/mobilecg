#include "stage2_filter.hpp"

static volatile int filter_taps[STAGE2FILTER_TAP_NUM] = {
  -2413431,
  -1573434,
  3391716,
  13678669,
  24599073,
  25727777,
  5674753,
  -38712006,
  -93564059,
  -126396976,
  -96107110,
  27425054,
  243088444,
  509408810,
  754184538,
  901007981,
  901007981,
  754184538,
  509408810,
  243088444,
  27425054,
  -96107110,
  -126396976,
  -93564059,
  -38712006,
  5674753,
  25727777,
  24599073,
  13678669,
  3391716,
  -1573434,
  -2413431
};

void Stage2Filter_init(Stage2Filter* f) {
  int i;
  for(i = 0; i < STAGE2FILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void Stage2Filter_put(Stage2Filter* f, int input) {
  f->history[(f->last_index++) & 31] = input;
}

int Stage2Filter_get(Stage2Filter* f) {
  long long acc = 0;
  int index = f->last_index;
    acc += (long long)f->history[(index--) & 31] * filter_taps[0];
    acc += (long long)f->history[(index--) & 31] * filter_taps[1];
    acc += (long long)f->history[(index--) & 31] * filter_taps[2];
    acc += (long long)f->history[(index--) & 31] * filter_taps[3];
    acc += (long long)f->history[(index--) & 31] * filter_taps[4];
    acc += (long long)f->history[(index--) & 31] * filter_taps[5];
    acc += (long long)f->history[(index--) & 31] * filter_taps[6];
    acc += (long long)f->history[(index--) & 31] * filter_taps[7];
    acc += (long long)f->history[(index--) & 31] * filter_taps[8];
    acc += (long long)f->history[(index--) & 31] * filter_taps[9];
    acc += (long long)f->history[(index--) & 31] * filter_taps[10];
    acc += (long long)f->history[(index--) & 31] * filter_taps[11];
    acc += (long long)f->history[(index--) & 31] * filter_taps[12];
    acc += (long long)f->history[(index--) & 31] * filter_taps[13];
    acc += (long long)f->history[(index--) & 31] * filter_taps[14];
    acc += (long long)f->history[(index--) & 31] * filter_taps[15];
    acc += (long long)f->history[(index--) & 31] * filter_taps[16];
    acc += (long long)f->history[(index--) & 31] * filter_taps[17];
    acc += (long long)f->history[(index--) & 31] * filter_taps[18];
    acc += (long long)f->history[(index--) & 31] * filter_taps[19];
    acc += (long long)f->history[(index--) & 31] * filter_taps[20];
    acc += (long long)f->history[(index--) & 31] * filter_taps[21];
    acc += (long long)f->history[(index--) & 31] * filter_taps[22];
    acc += (long long)f->history[(index--) & 31] * filter_taps[23];
    acc += (long long)f->history[(index--) & 31] * filter_taps[24];
    acc += (long long)f->history[(index--) & 31] * filter_taps[25];
    acc += (long long)f->history[(index--) & 31] * filter_taps[26];
    acc += (long long)f->history[(index--) & 31] * filter_taps[27];
    acc += (long long)f->history[(index--) & 31] * filter_taps[28];
    acc += (long long)f->history[(index--) & 31] * filter_taps[29];
    acc += (long long)f->history[(index--) & 31] * filter_taps[30];
    acc += (long long)f->history[(index--) & 31] * filter_taps[31];
  return acc >> 32;
}
