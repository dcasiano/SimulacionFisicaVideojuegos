#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Particle.h"
#include "Floor.h"


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

Particle* particle;
Floor* floor1;
std::vector<Particle*>projectiles;

enum ShootType { Pistol, Artillery, Fireball, Laser };
ShootType sType = Pistol;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//particle = new Particle({ -50.0,0.0,0.0 }, { 10.0,0.0,0.0 }, { 0.0,2.0,0.0 },0.988);
	//floor1 = new Floor(20.0, { 0.0,-20.0,0.0 });
	}

void shoot(ShootType type) {
	Particle* projectile;
	Vector3 vel, acc;
	float damp = 0.99f, mass;
	switch (type)
	{
	case Pistol:
		vel = 35.0f * GetCamera()->getDir();
		acc = { 0.0,-1.0,0.0 };
		mass = 2.0f;
		break;
	case Artillery:
		vel = { GetCamera()->getDir().x,GetCamera()->getDir().y + 0.5f ,GetCamera()->getDir().z };
		vel *= 30.0f;
		acc = { 0.0,-20.0,0.0 };
		mass = 200.0f;
		break;
	case Fireball:
		vel = 10.0f * GetCamera()->getDir();
		acc = { 0.0,0.6,0.0 };
		mass = 1.0f;
		damp = 0.9f;
		break;
	case Laser:
		vel = 100.0f * GetCamera()->getDir();
		acc = { 0.0,0.0,0.0 };
		mass = 0.1f;
		break;
	default:
		break;
	}
	projectile = new Particle(GetCamera()->getTransform().p, vel, acc, damp);
	projectile->setMass(mass);
	projectile->setSpawnTime(GetLastTime());
	projectiles.push_back(projectile);
}
void updateProjectiles(double t) {
	int num = 0;
	for (std::vector<Particle*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it) {
		projectiles.at(num)->integrate(t);
		
		if (projectiles.at(num)->getSpawnTime() + 1.000 < GetLastTime() || projectiles.at(num)->getPosition().y < 0.0f) {
			projectiles.erase(it);
		}
		num++;
	}
}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	//particle->integrate(t);
	
	updateProjectiles(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	delete particle;
	delete floor1;
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'F':
		shoot(sType);
		break;
	case '1':
		sType = Pistol;
		break;
	case '2':
		sType = Artillery;
	case '3':
		sType = Fireball;
	case '4':
		sType = Laser;
	default:
		break;
	}
}






void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}