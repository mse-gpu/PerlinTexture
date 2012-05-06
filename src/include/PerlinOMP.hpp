#include "Perlin.hpp"

#define THREADS 12

class PerlinImageOMP : public PerlinImage {
    public:
	PerlinImageOMP(int m, int n, DomaineMaths domain);

    protected:
	virtual void refreshAll(const DomaineMaths& domainNew);

    private:
	float color(float x, float y);
	float d(float x, float y);
};
