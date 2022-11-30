#include "ElasticBandFG.h"

ElasticBandFG::ElasticBandFG(Particle* other, double k, double restLength) :SpringForceGenerator(other, k, restLength)
{
}

ElasticBandFG::~ElasticBandFG()
{
}

void ElasticBandFG::updateForce(Particle* p, double duration)
{
	Vector3 force = p->getPosition() - other->getPosition();
	const float length = force.normalize();
	const float deltaX = length - restLength;
	if (deltaX < 0.0f) return;
	force *= -deltaX * k;
	p->addForce(force);
}
