#include "common.h"

float random(float from, const float to){
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = to - from;
    float r = random * diff;
    return from + r;
}

