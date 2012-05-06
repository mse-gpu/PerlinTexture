#ifndef RIPPLING
#define RIPPLING

#include "DomaineMaths.h"
#include "GLUTWindowManagers.h"
#include "ImageFonctionelSelectionMOOs.h"
#include "GLImageFonctionelSelections.h"

class PerlinImage : public ImageFonctionelSelectionMOOs {
    public:
	PerlinImage(int m, int n, DomaineMaths domain);

	void setT(int t);

    protected:
	void onDomaineChangePerformed(const DomaineMaths& domainNew);
	virtual void refreshAll(const DomaineMaths& domainNew) = 0;

	float t;
};

class PerlinGLImage : public GLImageFonctionelSelections {
    public:
	PerlinGLImage(PerlinImage* image);

    private:
	int t;

	void idleFunc();

	PerlinImage* image;
};

#endif
