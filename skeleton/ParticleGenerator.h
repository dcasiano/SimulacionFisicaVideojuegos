#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <string>
#include <list>
#include <random>

using namespace physx;
using namespace std;
class ParticleGenerator
{
public:
	ParticleGenerator();
	~ParticleGenerator();
	virtual list<Particle*>generateParticles() = 0;
	void setParticle(Particle* model_) { model = model_; }
	void setNumParticles(int n) { numParticles = n; }
	void setGenerationProb(double prob) { generationProb = prob; }
	void setDamp(float value) { damp = value; }
	void setMass(float value) { mass = value; }
	void setColor(Vector4 color_) { color = color_; }
	virtual list<PxRigidDynamic*>generateRigidDynamicParticles(PxPhysics* gPhysics) {}
	
protected:
	Particle* model;
	int numParticles;
	double generationProb;
	Vector3 meanPos, meanVel, acc;
	float damp, mass;
	Vector4 color;
	string name;
};

