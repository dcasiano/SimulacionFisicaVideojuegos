#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <string>
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "NormalParticleGenerator.h"
#include "CircleGenerator.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"

using namespace physx;
using namespace std;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void shootFirework();
	//void addParticleToRegistry(Particle* p){forceReg->addRegistry}
	//void deleteParticleFromRegistry(Particle* p) { forceReg->deleteParticle(p); }
private:
	//list<Particle*>particles;
	vector<Particle*>particles;
	list<ParticleGenerator*>particlesGenerators;
	vector<Firework*>fireworks;
	CircleGenerator* fireworkGenerator;
	ForceRegistry* forceReg;
	GravityForceGenerator* gravityFG;
};

