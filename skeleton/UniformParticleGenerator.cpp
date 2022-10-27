#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 pos, Vector3 vel, Vector3 posWidth, Vector3 velWidth, Vector3 acc)
{
	meanPos = pos;
	meanVel = vel;
	this->posWidth = posWidth;
	this->velWidth = velWidth;
	numParticles = 1;
	generationProb = 1;
	this->acc = acc;
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
