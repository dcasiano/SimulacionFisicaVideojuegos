#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	Vector3 pos, vel, posWidth, velWidth, acc;
	pos = { 0.0,0.0,0.0 };
	posWidth = { 2.0,2.0,2.0 };
	vel = { 0.0,30.0,0.0 };
	velWidth = { 10.0,0.0,10.0 };
	acc = { 0.0,0.0,0.0 };
	particlesGenerators.push_back(new UniformParticleGenerator(pos, vel, posWidth, velWidth, acc));
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(double t)
{
	for (auto e : particlesGenerators) {
		list<Particle*> part = e->generateParticles();
		for (auto p : part)particles.push_back(p);
	}

	for (auto e : particles) {
		e->integrate(t);
	}
}
