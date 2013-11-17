#include "stage1_filter.hpp"

static volatile int filter_taps[STAGE1FILTER_TAP_NUM] = {
  1161859,
  3958452,
  8271341,
  11706547,
  9506031,
  -3694568,
  -29961744,
  -63515426,
  -88355557,
  -80810086,
  -17759765,
  111922474,
  297875833,
  506192823,
  687519156,
  793229255,
  793229255,
  687519156,
  506192823,
  297875833,
  111922474,
  -17759765,
  -80810086,
  -88355557,
  -63515426,
  -29961744,
  -3694568,
  9506031,
  11706547,
  8271341,
  3958452,
  1161859
};

void Stage1Filter_init(Stage1Filter* f) {
  int i;
  for(i = 0; i < STAGE1FILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void Stage1Filter_put(Stage1Filter* f, int input) {
  f->history[(f->last_index++) & 31] = input;
}

int Stage1Filter_get(Stage1Filter* f) {
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
