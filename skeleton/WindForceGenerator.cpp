#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(const Vector3& windVel, const Vector3& pos, double r)
{
	setWindVelocity(windVel);
	setAreaOfEffect(pos, r);
	
}


void WindForceGenerator::updateForce(Particle* p, double duration)
{
	// check the particle has finite mass
	if (fabs(p->getInvMass() < 1e-10))return;
	if (isAffectedByWind(p->getPosition())) {
		p->addForce(p->getK1Wind() * (windVel - p->getVelocity())+p->getK2Wind()* (windVel - p->getVelocity())* (windVel - p->getVelocity()).magnitude());
	}
}

// Checks if the particle is inside the area of effect
bool WindForceGenerator::isAffectedByWind(const Vector3& partPos)
{
	return (partPos - pos).magnitude() < r;
}
