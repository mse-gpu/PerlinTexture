#include <iostream>
#include <cmath> //for sin
#include "omp.h"

#include "Rippling.hpp"

RipplingImage::RipplingImage(int m, int n, DomaineMaths domain) : ImageFonctionelSelectionMOOs(m,n,domain), t(1) {
    //Nothing to init
}

void RipplingImage::setT(float newT){
    t = newT;

    refreshAll(getCurrentDomaine());
}

void RipplingImage::onDomaineChangePerformed(const DomaineMaths& domainNew){
    refreshAll(domainNew);
}

RipplingGLImage::RipplingGLImage(RipplingImage* image) : GLImageFonctionelSelections(image), image(image) {
    t = 1;

    //Define the speed of the animation
    dt = 2 * (atan(1) * 4) / (float) 36;
}

void RipplingGLImage::idleFunc(){
    t += dt;
    image->setT(t);
    updateView();
}
