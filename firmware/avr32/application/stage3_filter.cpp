#include "stage3_filter.hpp"

static volatile int filter_taps[STAGE3FILTER_TAP_NUM] = {
  1881580,
  -7875891,
  -13754683,
  2963661,
  32103874,
  22886953,
  -41013973,
  -76899908,
  7513662,
  139972447,
  104495734,
  -157734278,
  -330825780,
  11083207,
  853754134,
  1594343681,
  1594343681,
  853754134,
  11083207,
  -330825780,
  -157734278,
  104495734,
  139972447,
  7513662,
  -76899908,
  -41013973,
  22886953,
  32103874,
  2963661,
  -13754683,
  -7875891,
  1881580
};

void Stage3Filter_init(Stage3Filter* f) {
  int i;
  for(i = 0; i < STAGE3FILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void Stage3Filter_put(Stage3Filter* f, int input) {
  f->history[(f->last_index++) & 31] = input;
}

int Stage3Filter_get(Stage3Filter* f) {
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
