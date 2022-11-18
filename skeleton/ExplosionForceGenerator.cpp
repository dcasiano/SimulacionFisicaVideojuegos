#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(double intensity, const Vector3& pos, double r, double expansionVelocity)
{
	K = intensity;
	this->pos = pos;
	R = r;
	tau = 2;
	ve = expansionVelocity;
	R0 = R;
}

void ExplosionForceGenerator::updateForce(Particle* p, double duration)
{
	// check the particle has finite mass
	if (fabs(p->getInvMass() < 1e-10))return;
	if (isInsideAreaOfEffect(p->getPosition())) {
		double t = GetLastTime() - t0;
		Vector3 partPos = p->getPosition();
		float r = sqrt(pow(partPos.x - pos.x, 2) + pow(partPos.y - pos.y, 2) + pow(partPos.z - pos.z, 2));
		Vector3 force = { partPos.x - pos.x, partPos.y - pos.y, partPos.z - pos.z };
		force *= K / pow(r, 2) * exp(-t / tau);
		p->addForce(force);
		R = R0 + ve * t;
	}
}

bool ExplosionForceGenerator::isInsideAreaOfEffect(const Vector3& partPos)
{
	return (partPos - pos).magnitude() < R;
}
