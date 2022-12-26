#include "RigidDynamicParticle.h"

RigidDynamicParticle::RigidDynamicParticle(PxTransform pos, PxShape* shape, Vector4 color, PxPhysics* gPhysics)
{
	rdb = gPhysics->createRigidDynamic(pos);
	rdb->attachShape(*shape);
	rendIt = new RenderItem(shape, rdb, color);
	spawnTime = GetLastTime();
}

RigidDynamicParticle::~RigidDynamicParticle()
{
	DeregisterRenderItem(rendIt);
}
