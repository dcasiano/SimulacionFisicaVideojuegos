#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class RigidDynamicParticle
{
public:
	RigidDynamicParticle(PxTransform pos, PxShape* shape, Vector4 color, PxPhysics* gPhysics);
	~RigidDynamicParticle();
	void setLifeTime(double value) { lifeTime = value; isImmortal = false; }
	bool hasToDie() { return !isImmortal && spawnTime + lifeTime < GetLastTime(); }
	PxRigidDynamic* getRigidDynamicBody() { return rdb; }
	RenderItem* getRenderItem() { return rendIt; }
	void setLinearVelocity(PxVec3 vel) { rdb->setLinearVelocity(vel); }
	void setAngularVelocity(PxVec3 vel) { rdb->setAngularVelocity(vel); }
	void setMassSpaceInertiaTensor(Vector3 v) { rdb->setMassSpaceInertiaTensor(v); }
	void setMass(float mass) { rdb->setMass(mass); }
protected:
	PxRigidDynamic* rdb;
	RenderItem* rendIt;
	double spawnTime, lifeTime;
	bool alive = true, isImmortal = true;
};

