#pragma once
#include "ParticleGenerator.h"
class RDWallGenerator :public ParticleGenerator
{
public:
	RDWallGenerator();
	~RDWallGenerator();
	virtual list<Particle*>generateParticles() { return list<Particle*>(); }
	virtual list<RigidDynamicParticle*>generateRigidDynamicParticles(PxPhysics* gPhysics, vector<RenderItem*>& renderItems);
protected:
	int numFil, numCol;
	Vector3 size;
	Vector3 pos0, offset;
};

