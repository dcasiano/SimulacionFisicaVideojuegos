#include "Particle.h"

Particle::Particle(Vector3 pos_, Vector3 vel_, Vector3 acc_, float damp_, Vector4 color)
{
	//pos.p = pos_;
	pos = PxTransform(pos_.x, pos_.y, pos_.z);
	vel = vel_;
	acc = acc_;
	damp = damp_;
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(1.0)), &pos, color);
	g = { 0.0,0.0,0.0 };
	mass = 1.0;
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	vel += (acc + g) * t;
	vel *= pow(damp, t);
	pos = PxTransform(pos.p + vel * t);
}
