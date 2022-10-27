#include "NormalParticleGenerator.h"

NormalParticleGenerator::NormalParticleGenerator(Vector3 pos, Vector3 vel, Vector3 posDesv, Vector3 velDesv, Vector3 acc)
{
	meanPos = pos;
	meanVel = vel;
	this->posDesv = posDesv;
	this->velDesv = velDesv;
	numParticles = 1;
	generationProb = 1;
	this->acc = acc;
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
			Vector3 desvPos = { (float)d(generator) * posDesv.x,(float)d(generator) * posDesv.y ,(float)d(generator) * posDesv.z };
			Vector3 desvVel = { (float)d(generator) * velDesv.x,(float)d(generator) * velDesv.y ,(float)d(generator) * velDesv.z };
			Particle* part = new Particle(meanPos + desvPos, meanVel + desvVel, acc, damp, color);
			part->setMass(mass);
			part->setSpawnTime(GetLastTime());
			part->setLifeTime(5.0);
			particles.push_back(part);
		}

	}

	return particles;
}

