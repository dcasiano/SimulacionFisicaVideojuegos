#pragma once
#include "ForceGenerator.h"
#include "RenderUtils.hpp"
class WindForceGenerator :public ForceGenerator
{
public:
	WindForceGenerator(const Vector3& windVel, const Vector3& pos, double r);
	~WindForceGenerator() {}
	virtual void updateForce(Particle* p, double duration);
	void setWindVelocity(const Vector3& windVel) { this->windVel = windVel; }
	void setAreaOfEffect(const Vector3& pos, const double r) { this->pos = pos; this->r = r; }
	Vector3 getWindVel(const Vector3& partPos) { return windVel; }
	void updateForceRDBody(PxRigidDynamic* rdb);
	void changeActive();
protected:
	bool isAffectedByWind(const Vector3& partPos);
	Vector3 windVel, pos;
	double r;
	bool isActive = true;
	//RenderItem* activeIndicator;
	Vector4 activeColor, inactiveColor;
};

