#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(double forceFactor, const Vector3& pos, double r):WindForceGenerator({ 0,0,0 }, pos, r)
{
	K = forceFactor;
}

void WhirlwindForceGenerator::updateForce(Particle* p, double duration)
{
	// check the particle has finite mass
	if (fabs(p->getInvMass() < 1e-10))return;
	if (isActive && isAffectedByWind(p->getPosition())) {
		p->addForce(p->getK1Wind() * (getWindVel(p->getPosition()) - p->getVelocity()));
	}
}

Vector3 WhirlwindForceGenerator::getWindVel(const Vector3& partPos)
{
	Vector3 vel = { -(partPos.z - pos.z),50 - (partPos.y - pos.y),(partPos.x - pos.x) };
	//Vector3 vel = { -(partPos.z - pos.z),0,(partPos.x - pos.x) };
	vel *= K;
	return vel;
}

void WhirlwindForceGenerator::updateForceRDBody(PxRigidDynamic* rdb)
{
	if (isActive && isAffectedByWind(rdb->getGlobalPose().p)) {
		rdb->addForce(0.47 * (getWindVel(rdb->getGlobalPose().p) - rdb->getLinearVelocity()));
	}
}