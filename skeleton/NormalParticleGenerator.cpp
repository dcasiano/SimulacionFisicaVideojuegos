#include "NormalParticleGenerator.h"

NormalParticleGenerator::NormalParticleGenerator(Vector3 pos, Vector3 vel, Vector3 posWidth_, Vector3 velWidth_, Vector3 acc_)
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

NormalParticleGenerator::~NormalParticleGenerator()
{
}

list<Particle*> NormalParticleGenerator::generateParticles()
{
	list<Particle*>particles;
	for (int i = 0; i < numParticles; i++) {
		if (abs(d(generator)) < generationProb) {
			Vector3 desvPos = { (float)d(generator) * posWidth.x,(float)d(generator) * posWidth.y ,(float)d(generator) * posWidth.z };
			Vector3 desvVel = { (float)d(generator) * velWidth.x,(float)d(generator) * velWidth.y ,(float)d(generator) * velWidth.z };
			Particle* part = new Particle(meanPos + desvPos, meanVel + desvVel, acc, damp, color);
			part->setMass(mass);
			part->setSpawnTime(GetLastTime());
			part->setLifeTime(5.0);
			particles.push_back(part);
		}

	}

	return particles;
}