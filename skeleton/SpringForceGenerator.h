#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator: public ForceGenerator
{
public:
	SpringForceGenerator(Particle* other, double k, double restLength);
	~SpringForceGenerator() {}
	virtual void updateForce(Particle* p, double duration);
	void setK(double k) { this->k = k; }
	void increaseK(double amount) { k += amount; if (k < 1)k = 1; } // also used to decrease
protected:
	Particle* other;
	double k, restLength;
};

