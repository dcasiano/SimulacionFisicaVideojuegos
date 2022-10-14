#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 pos, Vector3 vel, Vector3 posWidth_, Vector3 velWidth_, Vector3 acc_)
{
	meanPos = pos;
	meanVel = vel;
	posWidth = posWidth_;
	velWidth = velWidth_;
	numParticles = 1;
	generationProb = 1;
	acc = acc_;
	damp = 0.99f;
	mass = 1.0f;
	color = { 0,1,0,1.0 };
}

UniformParticleGenerator::~UniformParticleGenerator()
{
}

list<Particle*> UniformParticleGenerator::generateParticles()
{
	list<Particle*>particles;
	for (int i = 0; i < numParticles; i++) {
		if (abs(d(generator)) < generationProb) {
			Vector3 desvPos = { d(generator) * posWidth.x,d(generator) * posWidth.y ,d(generator) * posWidth.z };
			Vector3 desvVel = { d(generator) * velWidth.x,d(generator) * velWidth.y ,d(generator) * velWidth.z };
			Particle* part = new Particle(meanPos + desvPos, meanVel + desvVel, acc, damp, color);
			part->setMass(mass);
			part->setSpawnTime(GetLastTime());
			part->setLifeTime(5.0);
			particles.push_back(part);
		}
		
	}

	return particles;
}
