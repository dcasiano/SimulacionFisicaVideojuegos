#include "RDWallGenerator.h"

RDWallGenerator::RDWallGenerator()
{
	numFil = 4;
	numCol = 7;
	size = { 2.0,2.0,2.0 };
	pos0 = { 2, -13, 160 };
	mass = 100;
	offset = { 5,5,0 };
}

RDWallGenerator::~RDWallGenerator()
{
}

list<RigidDynamicParticle*> RDWallGenerator::generateRigidDynamicParticles(PxPhysics* gPhysics, vector<RenderItem*>& renderItems)
{
	list<RigidDynamicParticle*>particles;
	for (int i = 0; i < numFil; i++) {
		for (int j = 0; j < numCol; j++) {
			Vector3 posV = pos0 + 2 * j * size.x * Vector3(1, 0, 0) + 2 * i * size.y * Vector3(0, 1, 0) ;
			PxTransform pos = PxTransform(posV);
			Vector4 color = { 1,0,0,1.0 };
			
			PxShape* shape = CreateShape(PxBoxGeometry(size));
			PxMaterial* const mat = gPhysics->createMaterial(0, 0, -1000);
			shape->setMaterials(&mat, 1);
			RigidDynamicParticle* rdp = new RigidDynamicParticle(pos, shape, color, gPhysics);
			rdp->setMass(mass);
			rdp->setMassSpaceInertiaTensor({ size.y * size.z,size.x * size.z,size.x * size.y });
			renderItems.push_back(rdp->getRenderItem());
			particles.push_back(rdp);
		}
	}

	return particles;
}
