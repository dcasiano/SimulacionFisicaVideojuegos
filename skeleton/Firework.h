#pragma once
#include "Particle.h"
class Firework :public Particle
{
public:
	Firework(Vector3 pos, Vector3 vel, Vector3 acc, float damp, Vector4 color, int id, int numExplosions);
	~Firework();
	bool hasToExplode() { return id < numExplosions; }
	int getId() { return id; }
	int getNumExplosions() { return numExplosions; }
protected:
	int id, numExplosions;
};

