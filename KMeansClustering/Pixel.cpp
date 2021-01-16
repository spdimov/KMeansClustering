#pragma once

#include <math.h>
#include <cstdint>

using namespace std;

struct Pixel {
    short r, g, b; // Red, Green, Blue pixel colors
    int cluster;
    double minDist;

    Pixel(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
        cluster = -1;
        minDist = INT16_MAX;
    }

    double distanceTo(Pixel p) {
        return sqrt(pow(this->r - p.r, 2)
                  + pow(this->g - p.g, 2)
                  + pow(this->b - p.b, 2));
    }
};