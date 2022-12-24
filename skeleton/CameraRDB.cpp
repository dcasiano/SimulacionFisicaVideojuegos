#include "CameraRDB.h"

CameraRDB::CameraRDB(PxPhysics* gPhysics, PxScene* gScene)
{
	rdbCam = gPhysics->createRigidDynamic(GetCamera()->getTransform());
	Vector3 sizeV = { 1,1,1 };
	//PxShape* shape = CreateShape(PxBoxGeometry(sizeV));
	PxShape* shape = CreateShape(PxSphereGeometry(1.0));
	PxMaterial* const mat = gPhysics->createMaterial(1, 0, -100);
	shape->setMaterials(&mat, 1);
	rdbCam->attachShape(*shape);
	rdbCam->setMass(100.0);
	rdbCam->setMassSpaceInertiaTensor({ sizeV.y * sizeV.z,sizeV.x * sizeV.z,sizeV.x * sizeV.y });
	gScene->addActor(*rdbCam);
}

CameraRDB::~CameraRDB()
{

}

void CameraRDB::update(double t)
{
	PxVec3 pos = rdbCam->getGlobalPose().p;
	GetCamera()->setPosition(pos);
	if (isOnFloor())rdbCam->setLinearDamping(10);
	else rdbCam->setLinearDamping(0);
	//PxVec3 v(0, 1, 0);
	//GetCamera()->setPosition(GetCamera()->getEye() - v);
}

void CameraRDB::jump()
{
	if (isOnFloor()) {
		PxVec3 f(0, 60, 0);
		rdbCam->addForce(f, PxForceMode::eVELOCITY_CHANGE);
	}
}

void CameraRDB::moveForward()
{
	PxVec3 v(0, 1, 0);
	PxVec3 viewY = GetCamera()->getDir().cross(v).getNormalized();
	PxVec3 viewX = v.cross(viewY).getNormalized();
	rdbCam->setLinearVelocity(speed * viewX);
}

void CameraRDB::moveBackward()
{
	PxVec3 v(0, 1, 0);
	PxVec3 viewY = GetCamera()->getDir().cross(v).getNormalized();
	PxVec3 viewX = v.cross(viewY).getNormalized();
	rdbCam->setLinearVelocity(-speed * viewX);
}

void CameraRDB::moveRight()
{
	PxVec3 v(0, 1, 0);
	PxVec3 viewY = GetCamera()->getDir().cross(v).getNormalized();
	rdbCam->setLinearVelocity(speed * viewY);
}

void CameraRDB::moveLeft()
{
	PxVec3 v(0, 1, 0);
	PxVec3 viewY = GetCamera()->getDir().cross(v).getNormalized();
	rdbCam->setLinearVelocity(-speed * viewY);
}
