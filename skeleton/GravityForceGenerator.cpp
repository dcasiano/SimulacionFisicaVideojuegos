#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g)
{
	setGravity(g);
}

void GravityForceGenerator::updateForce(Particle* p, double duration)
{
	// check the particle has finite mass
	if (fabs(p->getInvMass() < 1e-10))return;
	p->addForce(gravity * p->getMass());
}
