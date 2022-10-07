#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <string>
#include <list>

using namespace physx;
using namespace std;
class ParticleGenerator
{
public:
	ParticleGenerator();
	~ParticleGenerator();
	virtual list<Particle*>generateParticles() = 0;
	void setParticle(Particle* model_) { model = model_; }
private:
	Particle* model;
	int numParticles;
	double generationProb;
	Vector3 meanPos, meanVel;
	string name;
};

