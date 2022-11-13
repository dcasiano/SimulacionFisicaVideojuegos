#pragma once
#include "WindForceGenerator.h"
class WhirlwindForceGenerator:public WindForceGenerator
{
public:
	WhirlwindForceGenerator(double forceFactor, const Vector3& pos, double r);
	~WhirlwindForceGenerator(){}
	virtual void updateForce(Particle* p, double duration);
	Vector3 getWindVel(const Vector3& partPos);
protected:
	double K;
};

