#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, float damp, Vector4 color);
	~Particle();

	void integrate(double t);
	void setGravity(Vector3& const g_) { g = g_; }
	void setMass(float mass_) { mass = mass_; }
	void setInverseMass(float invMass) { this->invMass = invMass; }
	void setPosition(Vector3 pos_) { pos = PxTransform(pos_.x, pos_.y, pos_.z); }
	void setSpawnTime(double currentTime) { spawnTime = currentTime; }
	Vector3 getPosition() { return pos.p; }
	float getMass() { return mass; }
	float getInvMass() { return invMass; }
	double getSpawnTime() { return spawnTime; }
	void kill() { alive = false; }
	bool isAlive() { return alive; }
	void setLifeTime(double value) { lifeTime = value; }
	double getLifeTime() { return lifeTime; }
	void addForce(Vector3& const f) { force += f; }
protected:
	void clearForce() { force = { 0.0,0.0,0.0 }; }
	PxTransform pos;
	Vector3 vel, const acc;
	Vector3 force; // accumulated force
	float damp; // damping
	Vector3 g; // gravity (m/s^2)
	float mass; // (kg)
	float invMass;
	double spawnTime, lifeTime;
	RenderItem* renderItem;
	bool alive = true;
};

