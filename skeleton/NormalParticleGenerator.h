#pragma once
#include "ParticleGenerator.h"
class NormalParticleGenerator :public ParticleGenerator
{
public:
	NormalParticleGenerator(Vector3 pos, Vector3 vel, Vector3 posDesv, Vector3 velDesv, Vector3 acc);
	~NormalParticleGenerator();
	virtual list<Particle*>generateParticles();
	virtual list<RigidDynamicParticle*>generateRigidDynamicParticles(PxPhysics* gPhysics, vector<RenderItem*>& renderItems);
protected:
	Vector3 velDesv, posDesv;
	default_random_engine generator;
	normal_distribution<double>d{ 0.0,1.0 };
};