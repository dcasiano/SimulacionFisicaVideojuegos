#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(const Vector3& windVel, const Vector3& pos, double r)
{
	setWindVelocity(windVel);
	setAreaOfEffect(pos, r);
	PxTransform posRI = PxTransform(pos.x, pos.y, pos.z);
	activeColor = { 0,1,0,1.0 };
	inactiveColor = { 1,0,0,1.0 };
	//activeIndicator = new RenderItem(CreateShape(PxBoxGeometry( 1.0,1.0,1.0 )), &posRI, inactiveColor);
}


void WindForceGenerator::updateForce(Particle* p, double duration)
{
	// check the particle has finite mass
	if (fabs(p->getInvMass() < 1e-10))return;
	if (isActive && isAffectedByWind(p->getPosition())) {
		p->addForce(p->getK1Wind() * (windVel - p->getVelocity()) + p->getK2Wind() * (windVel - p->getVelocity()) * (windVel - p->getVelocity()).magnitude());
	}
}

// Checks if the particle is inside the area of effect
bool WindForceGenerator::isAffectedByWind(const Vector3& partPos)
{
	return (partPos - pos).magnitude() < r;
}

void WindForceGenerator::updateForceRDBody(PxRigidDynamic* rdb)
{
	if (isActive && isAffectedByWind(rdb->getGlobalPose().p)) {
		//rdb->addForce(0.47 * (getWindVel(rdb->getGlobalPose().p) - rdb->getLinearVelocity()));
		rdb->addForce(0.47 * (windVel - rdb->getLinearVelocity()) /*+ p->getK2Wind() * (windVel - p->getVelocity()) * (windVel - p->getVelocity()).magnitude()*/);
	}
}

void WindForceGenerator::changeActive()
{
	isActive = !isActive;
	/*if (isActive)activeIndicator->color = activeColor;
	else activeIndicator->color = inactiveColor;*/
}
