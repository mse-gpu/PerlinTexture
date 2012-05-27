#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

#include "PerlinNoise.hpp"

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

float scale(float from, float to, int scale, int t){
    float direction = t % (scale * 2);

    if(direction < scale){
	return from + (to - from) * (float)(t % scale) / (float)scale;
    } else {
	return to - (to - from) * (float)(t % scale) / (float)scale;
    }
}

float perlinNoise(float x, float y, int t){
    float total = 0.0;

    float frequency = scale(0.010, 0.025, 5000, t);
    float persistence = scale(0.20, 0.65, 5000, t);
    float octaves = scale(2, 33, 5000, t);
    float amplitude = 0.5;

    x = x + t / 10;

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
