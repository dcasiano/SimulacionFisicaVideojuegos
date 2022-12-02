#include "BuoyancyFG.h"

BuoyancyFG::BuoyancyFG(float height, float volume, float liquidDensity)
{
	this->height = height;
	this->volume = volume;
	this->liquidDensity = liquidDensity;
	liquidSurface = new Particle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, 0.0f, { 0,1,0.5,0.2 });
	liquidSurface->setInverseMass(0);
	liquidSurface->setAsLiquidSurface();
}

BuoyancyFG::~BuoyancyFG()
{
	delete liquidSurface;
}

void BuoyancyFG::updateForce(Particle* p, double duration)
{
	float h = p->getPosition().y;
	float h0 = liquidSurface->getPosition().y;
	Vector3 force(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > height * 0.5)immersed = 0.0;
	else if (h0 - h > height * 0.5)immersed = 1.0; // totally immersed
	else immersed = (h0 - h) / height + 0.5;
	force.y = liquidDensity * volume * immersed * gravity;
	if (immersed > 0)p->setDamp(0.02);
	else p->resetDamp();
	p->addForce(force);
}
