#include <iostream>
#include <limits.h>
#include <math.h>

#include "omp.h"

#include "ChronoOMPs.h"

#include "Rippling.hpp"
#include "RipplingSequential.hpp"
#include "RipplingOMP.hpp"

#define DIM 600

int launchApplication();
int launchApplicationOMP();
int bench();

int main(void){
    return launchApplication();
    //return  launchApplicationOMP();
    //return bench();
}

void display(RipplingImage* image);

int launchApplicationOMP(){
    omp_set_num_threads(THREADS);

    std::cout << "Launch the OMP Rippling application" << std::endl;

    DomaineMaths domain(0, 0, DIM, DIM);
    display(new RipplingImageOMP(DIM, DIM, domain));

    return 0;
}

int launchApplication(){
    std::cout << "Launch the sequential Rippling application" << std::endl;

    DomaineMaths domain(0, 0, DIM, DIM);
    display(new RipplingImageSequential(DIM, DIM, domain));

    return 0;
}

void display(RipplingImage* image){
    char** argv = NULL;
    GLUTWindowManagers::init(0, argv);

    RipplingGLImage* glImage = new RipplingGLImage(image);

    GLUTWindowManagers* windowManager = GLUTWindowManagers::getInstance();
    windowManager->createWindow(glImage);
    windowManager->runALL(); //This call is blocking

    delete image;
    delete glImage;
}

#define DIM_BENCH 500000
#define THREADS 24

float d(float x, float y){
    float fx = x - (DIM_BENCH / 2);
    float fy = y - (DIM_BENCH / 2);

    return sqrt(fx * fx + fy * fy);
}

float color(float x, float y, float t){
    return 128 + 127 * ((cos(d(x,y) / (float)10 -(t / (float)7))) / (d(x,y) / 10 + 1));
}

inline void benchSequential(){
    DomaineMaths domain(0, 0, DIM_BENCH, DIM_BENCH);

    float dx = (float) (domain.dx / (float) DIM_BENCH);
    float dy = (float) (domain.dy / (float) DIM_BENCH);
    float y = domain.y0;

    float t = 1;

    for(int i = 1; i <= DIM_BENCH; ++i){
	float x = domain.x0;

	for(int j = 1; j <= DIM_BENCH; ++j){
	    float c = color(x,y,t);

	    x += dx;
	}

	y += dy;
    }
}

inline void benchParallel(){
    DomaineMaths domain(0, 0, DIM_BENCH, DIM_BENCH);

    const float dx = (float) (domain.dx / (float) DIM_BENCH);
    const float dy = (float) (domain.dy / (float) DIM_BENCH);

    float t = 1;

    #pragma omp parallel
    {
	int tid = omp_get_thread_num();
	int i = tid + 1;

	float y = domain.y0 + tid * dy;

	while(i <= DIM_BENCH){
	    float x = domain.x0;

	    for(int j = 1; j <= DIM_BENCH; ++j){
		float c = color(x,y,t);

		x += dx;
	    }

	    y += THREADS * dy;

	    i += THREADS;
	}
    }
}

int bench(){
    std::cout << "Launch a benchmark" << std::endl;

    ChronoOMPs chronos;
    chronos.start();

    //benchSequential();

    double timeSequential = chronos.timeElapse();
    std::cout << "Sequential version took " << timeSequential << "s" << std::endl;

    chronos.start();

    benchParallel();

    double timeParallel = chronos.timeElapse();
    std::cout << "OMP version took " << timeParallel << "s" << std::endl;

    std::cout << "Factor=" << (timeSequential / timeParallel) << std::endl;

    return 0;
}
