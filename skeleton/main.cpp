#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Particle.h"
#include "Dartboard.h"
#include "ParticleSystem.h"


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

//Particle* particle;
Dartboard* dartboard;
std::vector<Particle*>projectiles;

enum ShootType { Pistol, Artillery, Fireball, Laser };
ShootType sType;

double shootCooldown, lastShotTime;

int score;

//P2
ParticleSystem* partSyst;

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
	//dartboard = new Dartboard(15.0, { 50.0,50.0,-30.0 });
	sType = Pistol;
	shootCooldown = 0.5;
	lastShotTime = -shootCooldown;
	score = 0;

	//P2
	partSyst = new ParticleSystem();
	}

void shoot(ShootType type) {
	if (lastShotTime + shootCooldown < GetLastTime()) {
		Particle* projectile;
		Vector3 vel, acc;
		float damp = 0.99f, mass;
		Vector4 color;
		switch (type)
		{
		case Pistol:
			vel = 35.0f * GetCamera()->getDir();
			acc = { 0.0,-1.0,0.0 };
			mass = 2.0f;
			color = { 0.5,0.5,0.5,1.0 };
			break;
		case Artillery:
			vel = { GetCamera()->getDir().x,GetCamera()->getDir().y + 0.5f ,GetCamera()->getDir().z };
			vel *= 30.0f;
			acc = { 0.0,-20.0,0.0 };
			mass = 200.0f;
			color = { 205 / 255.0, 127 / 255.0, 50 / 255.0,1.0 };
			break;
		case Fireball:
			vel = 10.0f * GetCamera()->getDir();
			acc = { 0.0,0.6,0.0 };
			mass = 1.0f;
			damp = 0.9f;
			color = { 1.0,0,0,1.0 };
			break;
		case Laser:
			vel = 100.0f * GetCamera()->getDir();
			acc = { 0.0,0.0,0.0 };
			mass = 0.1f;
			color = { 0,1,0,1.0 };
			break;
		default:
			break;
		}
		projectile = new Particle(GetCamera()->getTransform().p, vel, acc, damp, color);
		projectile->setMass(mass);
		projectile->setSpawnTime(GetLastTime());
		projectiles.push_back(projectile);
		lastShotTime = GetLastTime();
	}
	
}
void updateProjectiles(double t) {

	for (int i = 0; i < projectiles.size(); i++) {
		projectiles.at(i)->integrate(t);
		int projScore = dartboard->score(projectiles.at(i)->getPosition());
		if (projScore > 0) {
			score += projScore;
			std::cout << "Score: " << score << "\n";
			projectiles.at(i)->kill();
		}
		if (!projectiles.at(i)->isAlive() || projectiles.at(i)->getSpawnTime() + 10.000 < GetLastTime() || projectiles.at(i)->getPosition().y < 0.0f) {
			delete projectiles.at(i);
			projectiles.erase(projectiles.begin() + i);
		}
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
	
	//updateProjectiles(t);


	//P2
	partSyst->update(t);
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

	//delete particle;
	delete dartboard;
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'F':
		shoot(sType);
		break;
	case '1':
		sType = Pistol;
		break;
	case '2':
		sType = Artillery;
		break;
	case '3':
		sType = Fireball;
		break;
	case '4':
		sType = Laser;
		break;
	case 'R':
		if (lastShotTime + shootCooldown < GetLastTime()) {
			partSyst->shootFirework();
			lastShotTime = GetLastTime();
		}
		break;
	case 'T':
		partSyst->generateTestParticles(2000, { 0,30,0 }, 500);
		break;
	case 'E':
		partSyst->generateExplosion();
		break;
	case 'P':
		partSyst->increaseSpringK(100);
		break;
	case 'O':
		partSyst->increaseSpringK(-100);
		break;
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