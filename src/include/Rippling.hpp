#ifndef RIPPLING
#define RIPPLING

#include "DomaineMaths.h"
#include "GLUTWindowManagers.h"
#include "ImageFonctionelSelectionMOOs.h"
#include "GLImageFonctionelSelections.h"

class RipplingImage : public ImageFonctionelSelectionMOOs {
    public:
	RipplingImage(int m, int n, DomaineMaths domain);

	void setT(float t);

    protected:
	void onDomaineChangePerformed(const DomaineMaths& domainNew);
	virtual void refreshAll(const DomaineMaths& domainNew) = 0;

	float t;
};

class RipplingGLImage : public GLImageFonctionelSelections {
    public:
	RipplingGLImage(RipplingImage* image);

    private:
	float t;
	float dt;

	void idleFunc();

	RipplingImage* image;
};

#endif
