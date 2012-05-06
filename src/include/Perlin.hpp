#ifndef RIPPLING
#define RIPPLING

#include "DomaineMaths.h"
#include "GLUTWindowManagers.h"
#include "ImageFonctionelSelectionMOOs.h"
#include "GLImageFonctionelSelections.h"

class PerlinImage : public ImageFonctionelSelectionMOOs {
    public:
	PerlinImage(int m, int n, DomaineMaths domain);

	void setT(float t);

    protected:
	void onDomaineChangePerformed(const DomaineMaths& domainNew);
	virtual void refreshAll(const DomaineMaths& domainNew) = 0;

	float t;
};

class PerlinGLImage : public GLImageFonctionelSelections {
    public:
	PerlinGLImage(PerlinImage* image);

    private:
	float t;
	float dt;

	void idleFunc();

	PerlinImage* image;
};

#endif
