#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class Particle
{
public:
	Particle(Vector3 pos_, Vector3 vel_);
	~Particle();

	void integrate(double t);
private:
	PxTransform pos;
	Vector3 vel;
	RenderItem* renderItem;
};

