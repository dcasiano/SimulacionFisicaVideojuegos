#pragma once
#include "ParticleGenerator.h"
class ShootParticleGenerator :public ParticleGenerator
{
public:
	ShootParticleGenerator();
	~ShootParticleGenerator();
	virtual list<Particle*>generateParticles(){ return list<Particle*>(); }
	virtual list<RigidDynamicParticle*>generateRigidDynamicParticles(PxPhysics* gPhysics, vector<RenderItem*>& renderItems);
	bool canShoot() { return lastShotTime + shootCooldown < GetLastTime(); }
protected:
	double shootCooldown, lastShotTime;
};

