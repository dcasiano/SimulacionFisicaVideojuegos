#include "Firework.h"

Firework::Firework(Vector3 pos, Vector3 vel, Vector3 acc, float damp, Vector4 color, int id, int numExplosions) :Particle(pos, vel, acc, damp, color)
{
	this->id = id;
	this->numExplosions = numExplosions;
}

Firework::~Firework()
{
}
