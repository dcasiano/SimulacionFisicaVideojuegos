#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator :public ParticleGenerator
{
public:
	UniformParticleGenerator(Vector3 pos, Vector3 vel, Vector3 posWidth_, Vector3 velWidth_, Vector3 acc_);
	~UniformParticleGenerator();
	virtual list<Particle*>generateParticles();
protected:
	Vector3 velWidth, posWidth;
	default_random_engine generator;
	uniform_real_distribution<double>d{ -1.0,1.0 };
};

