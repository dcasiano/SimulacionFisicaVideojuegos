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
	void setLifeTime(double value) { lifeTime = value; isImmortal = false; }
	double getLifeTime() { return lifeTime; }
	void addForce(Vector3& const f) { force += f; }
	void setK1Wind(double k1) { k1Wind = k1; }
	void setK2Wind(double k2) { k2Wind = k2; }
	double getK1Wind() { return k1Wind; }
	double getK2Wind() { return k2Wind; }
	Vector3 getVelocity() { return vel; }
	void setAsCube() { DeregisterRenderItem(renderItem); renderItem = new RenderItem(CreateShape(PxBoxGeometry(1.0, 1.0, 1.0)), &pos, color); }
	void setAsLiquidSurface(){ DeregisterRenderItem(renderItem); renderItem = new RenderItem(CreateShape(PxBoxGeometry(20.0, 0.02, 20.0)), &pos, color); }
	void setDamp(float value) { damp = value; }
	void resetDamp() { damp = damp0; }
protected:
	void clearForce() { force = { 0.0,0.0,0.0 }; }
	PxTransform pos;
	Vector3 vel, const acc;
	Vector3 force; // accumulated force
	float damp; // damping
	float damp0; // initial damping
	Vector3 g; // gravity (m/s^2)
	float mass; // (kg)
	float invMass;
	double k1Wind, k2Wind;
	double spawnTime, lifeTime;
	RenderItem* renderItem;
	Vector4 color;
	bool alive = true, isImmortal = true;
};

