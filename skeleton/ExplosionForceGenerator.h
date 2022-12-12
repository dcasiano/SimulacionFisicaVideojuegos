#pragma once
#include "ForceGenerator.h"

class ExplosionForceGenerator:public ForceGenerator
{
public:
	ExplosionForceGenerator(double intensity, const Vector3& pos, double r, double expansionVelocity);
	~ExplosionForceGenerator(){}
	virtual void updateForce(Particle* p, double duration);
	void setInitialTime(double t) { this->t0 = t; }
	void generateExplotionForRDBody(PxRigidDynamic* rdb);
protected:
	bool isInsideAreaOfEffect(const Vector3& partPos);
	Vector3 pos;
	double K, R, tau, t0, ve, R0;
};

