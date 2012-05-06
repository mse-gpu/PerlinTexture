#include <iostream>
#include <cmath>

#include "PerlinSequential.hpp"
#include "PerlinNoise.hpp"

PerlinImageSequential::PerlinImageSequential(int m, int n, DomaineMaths domain) : PerlinImage(m,n,domain) {
    //Nothing to do
    srand(time(NULL));
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
	    float c = perlinNoise(x+t,y);

	    setRGBA(i, j, 135, 206, 250, c * 255.0);

	    x += dx;
	}

	y += dy;
    }
}
