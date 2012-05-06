#include <iostream>
#include <cmath> //for sin
#include "omp.h"

#include "Perlin.hpp"

PerlinImage::PerlinImage(int m, int n, DomaineMaths domain) : ImageFonctionelSelectionMOOs(m,n,domain), t(1) {
    //Nothing to init
}

void PerlinImage::setT(float newT){
    t = newT;

    refreshAll(getCurrentDomaine());
}

void PerlinImage::onDomaineChangePerformed(const DomaineMaths& domainNew){
    refreshAll(domainNew);
}

PerlinGLImage::PerlinGLImage(PerlinImage* image) : GLImageFonctionelSelections(image), image(image) {
    t = 1;

    //Define the speed of the animation
    dt = 2 * (atan(1) * 4) / (float) 36;
}

void PerlinGLImage::idleFunc(){
    t += dt;
    image->setT(t);
    updateView();
}
