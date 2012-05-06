#include <iostream>
#include <cmath>
#include "omp.h"

#include "PerlinSequential.hpp"

PerlinImageSequential::PerlinImageSequential(int m, int n, DomaineMaths domain) : PerlinImage(m,n,domain) {
    //Nothing to do
}

void PerlinImageSequential::refreshAll(const DomaineMaths& domainNew){
    int w = getW();
    int h = getH();

    float dx = (float) (domainNew.dx / (float) w);
    float dy = (float) (domainNew.dy / (float) h);
    float y = domainNew.y0;

    for(int i = 1; i <= h; ++i){
	float x = domainNew.x0;

	for(int j = 1; j <= w; ++j){
	    float c = color(x,y);

	    setRGBA(i, j, c, c, c);

	    x += dx;
	}

	y += dy;
    }
}

float PerlinImageSequential::color(float x, float y){
    return 128 + 127 * ((cos(d(x,y) / (float)10 -(t / (float)7))) / (d(x,y) / 10 + 1));
}

float PerlinImageSequential::d(float x, float y){
    float fx = x - (getW() / 2);
    float fy = y - (getH() / 2);

    return sqrt(fx * fx + fy * fy);
}
