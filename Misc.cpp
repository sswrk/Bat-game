//
// Created by szmnw on 26.04.2020.
//
#include "Misc.h"

float random(float from, const float to){
    unsigned int seed = static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count());
    static default_random_engine engine(seed);
    uniform_real_distribution<float> dist(from, to);
    return dist(engine);
}
