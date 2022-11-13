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
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"

using namespace physx;
using namespace std;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void shootFirework();
	void generateTestParticles(int num, const Vector3& pos, double r);
	void generateExplosion();
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
	WindForceGenerator* windFG;
	WhirlwindForceGenerator* whirlwindFG;
	ExplosionForceGenerator* explosionFG;
};

