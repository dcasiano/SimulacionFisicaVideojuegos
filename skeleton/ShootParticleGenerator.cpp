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

list<PxRigidDynamic*> ShootParticleGenerator::generateRigidDynamicParticles(PxPhysics* gPhysics, vector<RenderItem*>& renderItems)
{
	list<PxRigidDynamic*>particles;
	PxTransform pos = GetCamera()->getTransform();
	PxVec3 dir = GetCamera()->getDir();
	pos.p += dir; // offset so projectile doesnt connect with CameraRDB
	Vector3 vel = 60.0f * dir;

	PxRigidDynamic* rdb = gPhysics->createRigidDynamic(pos);

	rdb->setLinearVelocity(vel);
	//rdb->setAngularVelocity({ 1.0,1.0,1.0 });
	float size = 0.5f;
	PxShape* shape = CreateShape(PxSphereGeometry(size));
	//float staticFriction = (float)d(generator) * 1.0f;
	PxMaterial* const mat = gPhysics->createMaterial(1, 0, -100);
	shape->setMaterials(&mat, 1);
	rdb->attachShape(*shape);
	rdb->setMass(mass);
	//rdb->setMassSpaceInertiaTensor({ sizeV.y * sizeV.z,sizeV.x * sizeV.z,sizeV.x * sizeV.y });
	Vector4 color = { 1,0,0,1.0 };
	RenderItem* rendIt = new RenderItem(shape, rdb, color);
	renderItems.push_back(rendIt);
	particles.push_back(rdb);
	lastShotTime = GetLastTime();

	return particles;
}
