#include <iostream>
#include <limits.h>
#include <math.h>

#include "omp.h"

#include "ChronoOMPs.h"

#include "Perlin.hpp"
#include "PerlinSequential.hpp"
#include "PerlinOMP.hpp"
#include "PerlinNoise.hpp"

#define DIM 800

int launchClouds();
int launchCloudsOMP();

int bench();

int main(void){
    //return launchClouds();
    return  launchCloudsOMP();
    //return bench();
}

void display(PerlinImage* image);

int launchClouds(){
    std::cout << "Launch the Perlin Clouds Sequential Application" << std::endl;

    DomaineMaths domain(0, 0, DIM, DIM);
    display(new PerlinImageSequential(DIM, DIM, domain));

    return 0;
}

int launchCloudsOMP(){
    omp_set_num_threads(THREADS);

    std::cout << "Launch the Perlin Clouds OMP Application with THREADS=" << THREADS << std::endl;

    DomaineMaths domain(0, 0, DIM, DIM);
    display(new PerlinImageOMP(DIM, DIM, domain));

    return 0;
}

void display(PerlinImage* image){
    char** argv = NULL;
    GLUTWindowManagers::init(0, argv);

    PerlinGLImage* glImage = new PerlinGLImage(image);

    GLUTWindowManagers* windowManager = GLUTWindowManagers::getInstance();
    windowManager->createWindow(glImage);
    windowManager->runALL(); //This call is blocking

    delete image;
    delete glImage;
}

#define DIM_H 1000
#define DIM_W 1000
#define TIMES 20

#define THREADS 24

struct rgba {
	int r;
	int g;
	int b;
	int a;
};

void setFloatRGBA(rgba* image, int i, int j, int r, int g, int b, int a){
    image[i * (DIM_H) + j].r = r;
    image[i * (DIM_H) + j].g = g;
    image[i * (DIM_H) + j].b = b;
    image[i * (DIM_H) + j].a = a;
}

inline void benchSequential(rgba* image){
    DomaineMaths domain(0, 0, DIM_W, DIM_H);

    float dx = (float) (domain.dx / (float) DIM_W);
    float dy = (float) (domain.dy / (float) DIM_H);
    float y = domain.y0;

    for(int i = 1; i <= DIM_W; ++i){
	float x = domain.x0;

	for(int j = 1; j <= DIM_H; ++j){
	    float c = perlinNoise(x,y, 1);

	    setFloatRGBA(image, i, j, 135, 206, 250, c * 255.0);

	    x += dx;
	}

	y += dy;
    }
}

inline void benchParallel(rgba* image){
    omp_set_num_threads(THREADS);

    DomaineMaths domain(0, 0, DIM_W, DIM_H);

    const float dx = (float) (domain.dx / (float) DIM_W);
    const float dy = (float) (domain.dy / (float) DIM_H);

    float t = 1;

    #pragma omp parallel
    {
	int tid = omp_get_thread_num();
	int i = tid + 1;

	float y = domain.y0 + tid * dy;

	while(i <= DIM_W){
	    float x = domain.x0;

	    for(int j = 1; j <= DIM_H; ++j){
		float c = perlinNoise(x,y, 1);

		setFloatRGBA(image, i, j, 135, 206, 250, c * 255.0);

		x += dx;
	    }

	    y += THREADS * dy;

	    i += THREADS;
	}
    }
}

int bench(){
    std::cout << "Launch the Perlin benchmark" << std::endl;

    rgba* image = (rgba*) calloc(sizeof(rgba),  (DIM_H + 1) * (DIM_W + 1));

    ChronoOMPs chronos;
    chronos.start();

    for(int i = 0; i < TIMES; ++i){
	benchSequential(image);
    }

    double timeSequential = chronos.timeElapse();
    std::cout << "Sequential Total (" << TIMES << " times) " << timeSequential << "s" << std::endl;
    std::cout << "Sequential Mean  (" << TIMES << " times) " << (timeSequential / TIMES) << "s" << std::endl;

    chronos.start();

    for(int i = 0; i < TIMES; ++i){
	benchParallel(image);
    }

    double timeParallel = chronos.timeElapse();
    std::cout << "OMP Total (" << TIMES << " times) " << timeParallel << "s" << std::endl;
    std::cout << "OMP Mean  (" << TIMES << " times) " << (timeParallel / TIMES) << "s" << std::endl;

    std::cout << "Factor=" << (timeSequential / timeParallel) << std::endl;

    free(image);
}
