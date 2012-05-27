#include <iostream>
#include <cmath>
#include "omp.h"

#include "PerlinOMP.hpp"
#include "PerlinNoise.hpp"

PerlinImageOMP::PerlinImageOMP(int m, int n, DomaineMaths domain) : PerlinImage(m,n,domain){
    //Nothing to init
}

void PerlinImageOMP::refreshAll(const DomaineMaths& domainNew){
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
		float c = perlinNoise(x,y,t);

		setRGBA(i, j, 135, 206, 250, c * 255.0);

		x += dx;
	    }

	    y += THREADS * dy;

	    i += THREADS;
	}
    }
}
