#pragma once
#include "SpringForceGenerator.h"
class ElasticBandFG:public SpringForceGenerator
{
public:
	ElasticBandFG(Particle* other, double k, double restLength);
	~ElasticBandFG();
	virtual void updateForce(Particle* p, double duration);
};

