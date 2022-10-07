#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator :public ParticleGenerator
{
public:
	UniformParticleGenerator();
	~UniformParticleGenerator();
	list<Particle*>generateParticles();
private:
	Vector3 velWidth, posWidth;
};

