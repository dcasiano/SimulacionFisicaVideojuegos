#pragma once
#include "NormalParticleGenerator.h"
#include "Firework.h"
class CircleGenerator :public NormalParticleGenerator
{
public:
	CircleGenerator();
	~CircleGenerator();
	list<Firework*>generateParticles(int idPart, int numExplosions, double lifetime);
	void setParams(Vector3 pos, Vector3 vel, Vector3 posDesv, Vector3 velDesv, Vector4 color);
};

