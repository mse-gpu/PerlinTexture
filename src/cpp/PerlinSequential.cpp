#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

#include "omp.h"

#include "PerlinSequential.hpp"

PerlinImageSequential::PerlinImageSequential(int m, int n, DomaineMaths domain) : PerlinImage(m,n,domain) {
    //Nothing to do
}

float interpolate(float x, float y, float a){
    float val = (1 - cos(a * M_PI)) * 0.5;
    return x * (1 - val) + y * val;
}

float noise(int x, int y){
    static int r1 = (rand() % 9000) + 1000;
    static int r2 = (rand() % 900000) + 100000;
    static int r3 = (rand() % 1000000000) + 1000000000;

    int n = x + y * 57;
    n = (n << 13) ^ n;

    return (1.0 - ((n * (n * n * r1 + r2) + r3) & 0x7fffffff) / 1073741824.0);
}

float smooth(float x, float y){
    float n1 = noise((int)x, (int)y);
    float n2 = noise((int)x + 1, (int)y);
    float n3 = noise((int)x, (int)y + 1);
    float n4 = noise((int)x + 1, (int)y + 1);

    float i1 = interpolate(n1, n2, x - (int)x);
    float i2 = interpolate(n3, n4, x - (int)x);

    return interpolate(i1, i2, y - (int)y);
}

float perlinNoise(float x, float y){
    float total = 0.0;

    float frequency = 0.015;
    float persistence = 0.65;
    float octaves = 8;
    float amplitude = 1;

    for(int lcv = 0; lcv < octaves; ++lcv){
	total += smooth(x * frequency, y * frequency) * amplitude;
	frequency *= 2;
	amplitude *= persistence;
    }

    const float cloudCoverage = 0;
    const float cloudDensity = 1;

    total = (total + cloudCoverage) * cloudDensity;

    if(total <  0){
	return 0.0;
    } else if(total > 1.0){
	return 1.0;
    } else {
	return total;
    }
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
	    float c = perlinNoise(x,y);

	    setRGBA(i, j, 135, 206, 250, c * 255.0);

	    x += dx;
	}

	y += dy;
    }
}
