#include "Rippling.hpp"

class RipplingImageSequential : public RipplingImage {
    public:
	RipplingImageSequential(int m, int n, DomaineMaths domain);

    protected:
	virtual void refreshAll(const DomaineMaths& domainNew);

    private:
	float color(float x, float y);
	float d(float x, float y);
};
