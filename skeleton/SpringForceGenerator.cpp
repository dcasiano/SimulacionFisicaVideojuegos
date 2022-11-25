#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(Particle* other, double k, double restLength)
{
	this->other = other;
	this->restLength = restLength;
	setK(k);
}

void SpringForceGenerator::updateForce(Particle* p, double duration)
{
	Vector3 force = p->getPosition() - other->getPosition();
	const float length = force.normalize();
	const float deltaX = length - restLength;
	force *= -deltaX * k;
	p->addForce(force);
}
