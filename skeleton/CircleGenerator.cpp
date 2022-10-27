#include "CircleGenerator.h"

CircleGenerator::CircleGenerator() :NormalParticleGenerator({ 0,0,0 }, {0,0,0}, { 0,0,0 }, { 0,0,0 }, { 0,-10,0 })
{
	numParticles = 50;
}

CircleGenerator::~CircleGenerator()
{
}

list<Firework*> CircleGenerator::generateParticles(int idPart, int numExplosions, double lifetime)
{
	list<Firework*>fireworks;
	for (int i = 0; i < numParticles; i++) {
		if (abs(d(generator)) < generationProb) {
			Vector3 desvPos = { (float)d(generator) * posDesv.x,(float)d(generator) * posDesv.y ,(float)d(generator) * posDesv.z };
			Vector3 desvVel = { (float)d(generator) * velDesv.x,(float)d(generator) * velDesv.y ,(float)d(generator) * velDesv.z };
			Firework* fw = new Firework(meanPos + desvPos, meanVel + desvVel, acc, damp, color, idPart, numExplosions);
			fw->setSpawnTime(GetLastTime());
			if (idPart == numExplosions)fw->setLifeTime(2 * lifetime);
			else fw->setLifeTime(lifetime);
			fireworks.push_back(fw);
		}

	}
	return fireworks;
}

void CircleGenerator::setParams(Vector3 pos, Vector3 vel, Vector3 posDesv, Vector3 velDesv, Vector4 color)
{
	meanPos = pos;
	meanVel = vel;
	this->posDesv = posDesv;
	this->velDesv = velDesv;
	this->color = color;
}
