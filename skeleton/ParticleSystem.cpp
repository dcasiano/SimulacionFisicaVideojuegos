#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	Vector3 pos, vel, posWidth, velWidth, acc;
	pos = { 0.0,0.0,0.0 };
	posWidth = { 2.0,2.0,2.0 };
	vel = { 0.0,30.0,0.0 };
	velWidth = { 10.0,0.0,10.0 };
	acc = { 0.0,-10.0,0.0 };
	//particlesGenerators.push_back(new UniformParticleGenerator(pos, vel, posWidth, velWidth, acc));
	//particlesGenerators.push_back(new NormalParticleGenerator(pos, vel, posWidth, velWidth, acc));
	fireworkGenerator = new CircleGenerator();
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
	
	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->integrate(t);
		if (!particles.at(i)->isAlive() || particles.at(i)->getPosition().y < 0.0f) {
			delete particles.at(i);
			particles.erase(particles.begin() + i);
		}
		
	}

	// Fireworks
	for (int i = 0; i < fireworks.size(); i++) {
		fireworks.at(i)->integrate(t);
		if (!fireworks.at(i)->isAlive()) {
			if (fireworks.at(i)->hasToExplode()) {
				int newId = fireworks.at(i)->getId() + 1;
				int numExplosions = fireworks.at(i)->getNumExplosions();
				Vector4 color = { 1,newId / (float)numExplosions,0,1 };
				fireworkGenerator->setParams(fireworks.at(i)->getPosition(), { 0,0,0 }, { 2,2,2 }, { 30,30,30 }, color);
				list<Firework*> fw = fireworkGenerator->generateParticles(newId, numExplosions, fireworks.at(i)->getLifeTime());
				for (auto e : fw)fireworks.push_back(e);
			}
			delete fireworks.at(i);
			fireworks.erase(fireworks.begin() + i);
		}

	}

}

void ParticleSystem::shootFirework()
{
	Firework* fw = new Firework({ -100,-100,-100 }, { 0,80,0 }, { 0,-10,0 }, 0.99f, { 1,0,0,1 }, 0, 2);
	fw->setSpawnTime(GetLastTime());
	fw->setLifeTime(2.0);
	fireworks.push_back(fw);
}
