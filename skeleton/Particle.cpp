#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, float damp, Vector4 color)
{
	//pos.p = pos_;
	this->pos = PxTransform(pos.x, pos.y, pos.z);
	this->vel = vel;
	this->acc = acc;
	this->damp = damp;
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0)), &this->pos, color);
	g = { 0.0,0.0,0.0 };
	mass = 1.0;
	invMass = 1.0;
	k1Wind = 0.47;
	//k2Wind = 1.29 * 0.5;
	//k2Wind = 0.02;
	k2Wind = 0;
	clearForce();
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	acc = force * invMass;
	vel += (acc + g) * t;
	vel *= pow(damp, t);
	pos = PxTransform(pos.p + vel * t);
	if (spawnTime + lifeTime < GetLastTime())alive = false;
	clearForce();
}
