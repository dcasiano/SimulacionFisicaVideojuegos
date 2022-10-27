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
	void setGravity(Vector3 g_) { g = g_; }
	void setMass(float mass_) { mass = mass_; }
	void setPosition(Vector3 pos_) { pos = PxTransform(pos_.x, pos_.y, pos_.z); }
	void setSpawnTime(double currentTime) { spawnTime = currentTime; }
	Vector3 getPosition() { return pos.p; }
	double getSpawnTime() { return spawnTime; }
	void kill() { alive = false; }
	bool isAlive() { return alive; }
	void setLifeTime(double value) { lifeTime = value; }
	double getLifeTime() { return lifeTime; }
protected:
	PxTransform pos;
	Vector3 vel, const acc;
	float damp; // damping
	Vector3 g; // gravity (m/s^2)
	float mass; // (kg)
	double spawnTime, lifeTime;
	RenderItem* renderItem;
	bool alive = true;
};

