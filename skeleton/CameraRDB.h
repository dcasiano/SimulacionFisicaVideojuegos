#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <PxForceMode.h>
class CameraRDB
{
public:
	CameraRDB(PxPhysics* gPhysics, PxScene* gScene);
	~CameraRDB();
	void update(double t);
	void jump();
	void moveForward();
	void moveBackward();
	void moveRight();
	void moveLeft();
	bool isOnFloor() { return abs(rdbCam->getLinearVelocity().y) < 0.1; }
protected:
	PxRigidDynamic* rdbCam;
	const float speed = 20.0f;
};

