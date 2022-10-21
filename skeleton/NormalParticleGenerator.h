#pragma once
#include "ParticleGenerator.h"
class NormalParticleGenerator :public ParticleGenerator
{
public:
	NormalParticleGenerator(Vector3 pos, Vector3 vel, Vector3 posWidth_, Vector3 velWidth_, Vector3 acc_);
	~NormalParticleGenerator();
	virtual list<Particle*>generateParticles();
protected:
	Vector3 velWidth, posWidth;
	default_random_engine generator;
	normal_distribution<double>d{ 0.0,0.5 };
};