#include "Perlin.hpp"

class PerlinImageSequential : public PerlinImage {
    public:
	PerlinImageSequential(int m, int n, DomaineMaths domain);

    protected:
	virtual void refreshAll(const DomaineMaths& domainNew);

    private:
	float color(float x, float y);
	float d(float x, float y);
};
