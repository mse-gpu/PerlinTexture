#include "Rippling.hpp"

#define THREADS 12

class RipplingImageOMP : public RipplingImage {
    public:
	RipplingImageOMP(int m, int n, DomaineMaths domain);

    protected:
	virtual void refreshAll(const DomaineMaths& domainNew);

    private:
	float color(float x, float y);
	float d(float x, float y);
};
