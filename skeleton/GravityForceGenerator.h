#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator:public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g);
	~GravityForceGenerator(){}
	virtual void updateForce(Particle* p, double duration);
	void setGravity(const Vector3& g) { gravity = g; }
protected:
	Vector3 gravity;
};

