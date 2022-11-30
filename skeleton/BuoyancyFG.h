#pragma once
#include "ForceGenerator.h"
class BuoyancyFG : public ForceGenerator
{
public:
	BuoyancyFG(float height, float volume, float liquidDensity);
	~BuoyancyFG();
	virtual void updateForce(Particle* p, double duration);
protected:
	float height, volume, liquidDensity;
	float gravity = 9.8;
	Particle* liquidSurface;
};

