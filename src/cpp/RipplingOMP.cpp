#include <iostream>
#include <cmath>
#include "omp.h"

#include "RipplingOMP.hpp"

RipplingImageOMP::RipplingImageOMP(int m, int n, DomaineMaths domain) : RipplingImage(m,n,domain){
    //Nothing to init
}

void RipplingImageOMP::refreshAll(const DomaineMaths& domainNew){
    const int w = getW();
    const int h = getH();

    const float dx = (float) (domainNew.dx / (float) w);
    const float dy = (float) (domainNew.dy / (float) h);

    #pragma omp parallel
    {
	int tid = omp_get_thread_num();
	int i = tid + 1;

	float y = domainNew.y0 + tid * dy;

	while(i <= h){
	    float x = domainNew.x0;

	    for(int j = 1; j <= w; ++j){
		float c = color(x,y);

		setRGBA(i, j, c, c, c, 255);

		x += dx;
	    }

	    y += THREADS * dy;

	    i += THREADS;
	}
    }
}

float RipplingImageOMP::color(float x, float y){
    return 128 + 127 * ((cos(d(x,y) / (float)10 -(t / (float)7))) / (d(x,y) / 10 + 1));
}

float RipplingImageOMP::d(float x, float y){
    float fx = x - (getW() / 2);
    float fy = y - (getH() / 2);

    return sqrt(fx * fx + fy * fy);
}
