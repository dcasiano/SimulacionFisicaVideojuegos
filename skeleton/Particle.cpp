#include "Particle.h"

Particle::Particle(Vector3 pos_, Vector3 vel_)
{
	//pos.p = pos_;
	pos = PxTransform(pos_.x, pos_.y, pos_.z);
	vel = vel_;
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0)), &pos, { 0,0,0.5,1.0 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pos = PxTransform(pos.p + vel * t);
}
