#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "NormalParticleGenerator.h"
#include "CircleGenerator.h"
#include <string>
#include <list>

using namespace physx;
using namespace std;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void shootFirework();
private:
	//list<Particle*>particles;
	vector<Particle*>particles;
	list<ParticleGenerator*>particlesGenerators;
	vector<Firework*>fireworks;
	CircleGenerator* fireworkGenerator;
};

