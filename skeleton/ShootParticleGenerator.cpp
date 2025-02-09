#include "ShootParticleGenerator.h"

ShootParticleGenerator::ShootParticleGenerator()
{
	shootCooldown = 0.5;
	lastShotTime = -shootCooldown;
	mass = 1.0f;
}

ShootParticleGenerator::~ShootParticleGenerator()
{
}

list<RigidDynamicParticle*> ShootParticleGenerator::generateRigidDynamicParticles(PxPhysics* gPhysics, vector<RenderItem*>& renderItems)
{
	list<RigidDynamicParticle*>particles;
	PxTransform pos = GetCamera()->getTransform();
	PxVec3 dir = GetCamera()->getDir();
	pos.p += dir; // offset so projectile doesnt connect with CameraRDB
	Vector3 vel = 120.0f * dir;

	float size = 0.5f;
	PxShape* shape = CreateShape(PxSphereGeometry(size));
	PxMaterial* const mat = gPhysics->createMaterial(1, 0, -100);
	shape->setMaterials(&mat, 1);
	Vector4 color = { 0,1,0,1.0 };
	RigidDynamicParticle* rdp = new RigidDynamicParticle(pos, shape, color, gPhysics);

	rdp->setLinearVelocity(vel);
	rdp->setMass(mass);
	renderItems.push_back(rdp->getRenderItem());
	particles.push_back(rdp);
	lastShotTime = GetLastTime();
	rdp->setLifeTime(2.0);

	return particles;
}
