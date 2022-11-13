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
	//particlesGenerators.push_back(new NormalParticleGenerator(pos, vel, posWidth, velWidth, acc));
	fireworkGenerator = new CircleGenerator();
	forceReg = new ForceRegistry();
	gravityFG = new GravityForceGenerator({ 0.0,-10.0,0.0 });
	windFG = new WindForceGenerator({ 80,0,0 }, { 0,30,0 }, 15);
	whirlwindFG = new WhirlwindForceGenerator(5, { 0,30,0 }, 100);
	explosionFG = new ExplosionForceGenerator(10000, { 0,30,0 }, 20, 343);
}

ParticleSystem::~ParticleSystem()
{
	delete fireworkGenerator;
	delete forceReg;
	delete gravityFG;
	delete windFG;
	delete whirlwindFG;
}

void ParticleSystem::update(double t)
{
	forceReg->updateForces(t);
	//if (GetLastTime() > 3.0)forceReg->deleteForceGenerator(gravityFG);

	for (auto e : particlesGenerators) {
		list<Particle*> part = e->generateParticles();
		for (auto p : part) {
			forceReg->addRegistry(gravityFG, p);
			//forceReg->addRegistry(windFG, p);
			//forceReg->addRegistry(whirlwindFG, p);
			particles.push_back(p);
		}
	}
	
	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->integrate(t);
		if (!particles.at(i)->isAlive() /*|| particles.at(i)->getPosition().y < 0.0f*/) {
			forceReg->deleteParticle(particles.at(i));
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
			forceReg->deleteParticle(fireworks.at(i));
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

void ParticleSystem::generateTestParticles(int num, const Vector3& pos, double r)
{
	default_random_engine generator;
	normal_distribution<double>d{ -1.0,1.0 };
	for (int i = 0; i < num; i++) {
		float theta = (float)d(generator) * 2 * 3.141592564;
		float phi = acosf(2 * (float)d(generator) - 1);
		float rad = cbrt((float)d(generator) * r*50);
		float sinTheta = sinf(theta);
		float cosTheta = cosf(theta);
		float sinPhi = sinf(phi);
		float cosPhi = cosf(phi);
		Vector3 partPos = { pos.x + rad * sinPhi * cosTheta ,pos.y + rad * sinPhi * sinTheta ,pos.z + rad * cosPhi };

		Particle* part = new Particle(partPos, { 0,0,0 }, { 0,0,0 }, 0.99, { 0,1,0,1 });
		part->setSpawnTime(GetLastTime());
		part->setLifeTime(5.0);
		//forceReg->addRegistry(whirlwindFG, part);
		particles.push_back(part);
	}
}

void ParticleSystem::generateExplosion()
{
	for (auto p : particles) {
		explosionFG->setInitialTime(GetLastTime());
		forceReg->addRegistry(explosionFG, p);
	}
}
