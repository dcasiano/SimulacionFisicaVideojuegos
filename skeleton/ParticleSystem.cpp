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
	particlesGenerators.push_back(new NormalParticleGenerator(pos, vel, posWidth, velWidth, acc));
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(double t)
{
	/*if (particles.size()<2) {
		for (auto e : particlesGenerators) {
			list<Particle*> part = e->generateParticles();
			for (auto p : part)particles.push_back(p);
		}
	}*/
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

	//list<Particle*>deadList;
	//for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it) {
	//	(*it)->integrate(t);
	//	if (!(*it)->isAlive()) {
	//		/*delete (*it);
	//		particles.erase(it);*/
	//		deadList.push_back(*it);
	//		
	//	}
	//}
	//vector<list<Particle*>::iterator>deadList;
	//int numPart = particles.size();
	//list<Particle*>::iterator it = particles.begin();
	//for (int i = 0; i < numPart; i++) {
	//	(*it)->integrate(t);
	//	//if (!(*it)->isAlive()) {
	//	//	//list<Particle*>::iterator aux = it;
	//	//	//particles.remove(*it);
	//	//	deadList.push_back(it);
	//	//	//particles.erase(it);
	//	//	//delete (*it);
	//	//	//return;
	//	//}
	//	//else ++it;
	//}
	/*for (int i = 0; i < deadList.size(); i++) {
		particles.erase(deadList[i]);
	}*/
	//int aux = 0;
	//while (aux != deadList.size()) {
	//	particles.remove(deadList.front());
	//	delete deadList.front();
	//	//deadList.pop_front();
	//	aux++;
	//}
	/*for (auto e : particles) {
		e->integrate(t);
		if (!e->isAlive()) {
			particles.remove(e);
		}
	}*/
}
