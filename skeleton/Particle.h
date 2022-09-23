#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class Particle
{
public:
	Particle(Vector3 pos_, Vector3 vel_, Vector3 acc_, float damp_);
	~Particle();

	void integrate(double t);
	void setGravity(Vector3 g_) { g = g_; }
	void setMass(float mass_) { mass = mass_; }
private:
	PxTransform pos;
	Vector3 vel, const acc;
	float damp; // damping
	Vector3 g; // gravity (m/s^2)
	float mass; // (kg)
	RenderItem* renderItem;
};

