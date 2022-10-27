#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator :public ParticleGenerator
{
public:
	UniformParticleGenerator(Vector3 pos, Vector3 vel, Vector3 posWidth, Vector3 velWidth, Vector3 acc);
	~UniformParticleGenerator();
	virtual list<Particle*>generateParticles();
protected:
	Vector3 velWidth, posWidth;
	default_random_engine generator;
	uniform_real_distribution<double>d{ -1.0,1.0 };
};

