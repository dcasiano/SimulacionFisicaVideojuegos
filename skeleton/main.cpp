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
#include "CameraRDB.h"
#include "GameManager.h"
#include "DetonationButton.h"


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

//P5
vector<RenderItem*>staticBodiesRI;
void createStaticScene();

CameraRDB* camRDB;
GameManager* gameManager;

RenderItem* windActiveIndicator;
Vector4 windActiveColor, windInactiveColor;
PxTransform windIndTranf(20.0, 30.0, -45.0);

DetonationButton* detButton;

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
	sceneDesc.gravity = PxVec3(0.0f, -98.0f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//particle = new Particle({ -50.0,0.0,0.0 }, { 10.0,0.0,0.0 }, { 0.0,2.0,0.0 },0.988);
	dartboard = new Dartboard(15.0, { 20.0,10.0,-40.0 });
	sType = Pistol;
	shootCooldown = 0.5;
	lastShotTime = -shootCooldown;
	score = 0;

	partSyst = new ParticleSystem();
	partSyst->setPxPhysics(gPhysics);
	partSyst->setPxScene(gScene);

	createStaticScene();
	camRDB = new CameraRDB(gPhysics, gScene);
	partSyst->setDartboard(dartboard);
	gameManager = new GameManager();
	gameManager->setPartSyst(partSyst);
	partSyst->createRDWall();

	windActiveColor = { 0,1,0,1.0 };
	windInactiveColor = { 1,0,0,1.0 };
	
	PxShape* windIndShape = CreateShape(PxBoxGeometry(6, 2, 2));
	windActiveIndicator = new RenderItem(windIndShape, &windIndTranf, windActiveColor);
	gameManager->setWindActiveIndicator(windActiveIndicator);
	//cout << windActiveIndicator->transform->p.x << " " << windActiveIndicator->transform->p.y << " " << windActiveIndicator->transform->p.z << "\n";

	detButton = new DetonationButton({ -5, -10, 170 });
	partSyst->setDetonationButton(detButton);
	partSyst->generateDartboardMotion();
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
	camRDB->update(t);
	gameManager->update();
	gameManager->updateScore(partSyst->getScore());
	dartboard->update(t);
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
	for (auto e : staticBodiesRI)DeregisterRenderItem(e);
	staticBodiesRI.clear();
	delete camRDB;
	DeregisterRenderItem(windActiveIndicator);
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'F':
		//shoot(sType);
		partSyst->shootBullet();
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
	case 'L':
		partSyst->WhirlwindActive();
		break;
	case 32:
		camRDB->jump();
		break;
	case 'W':
		camRDB->moveForward();
		break;
	case 'S':
		camRDB->moveBackward();
		break;
	case 'A':
		camRDB->moveLeft();
		break;
	case 'D':
		camRDB->moveRight();
		break;
	default:
		break;
	}
}

// Scene for rigid bodies interactions
void createStaticScene() {
	// Floor
	PxRigidStatic* floor1 = gPhysics->createRigidStatic(PxTransform({ 0, -20, 120 }));
	PxShape* floorShape = CreateShape(PxBoxGeometry(100, 5, 100));
	floor1->attachShape(*floorShape);
	RenderItem* floorRendIt = new RenderItem(floorShape, floor1, { 0,1,0.5,0.2 });//0.8,0.52,0.24,1.0
	staticBodiesRI.push_back(floorRendIt);
	gScene->addActor(*floor1);

	PxRigidStatic* floor2 = gPhysics->createRigidStatic(PxTransform({ 0, -50, -60 }));
	PxShape* floor2Shape = CreateShape(PxBoxGeometry(100, 40, 20));
	floor2->attachShape(*floor2Shape);
	RenderItem* floor2RendIt = new RenderItem(floor2Shape, floor2, { 1,0,0.5,0.2 });//0.8,0.52,0.24,1.0
	staticBodiesRI.push_back(floor2RendIt);
	gScene->addActor(*floor2);

	//Wall
	PxRigidStatic* dartWall = gPhysics->createRigidStatic(PxTransform({ 20, 0, -60 }));
	PxShape* dartWallShape = CreateShape(PxBoxGeometry(40, 40, 5));
	dartWall->attachShape(*dartWallShape);
	RenderItem* dartWallRendIt = new RenderItem(dartWallShape, dartWall, { 0,1,1,0.2 });
	staticBodiesRI.push_back(dartWallRendIt);
	gScene->addActor(*dartWall);

	PxRigidStatic* wall1 = gPhysics->createRigidStatic(PxTransform({ -20, -10, 120 }));
	PxShape* wall1Shape = CreateShape(PxBoxGeometry(20, 10, 50));
	wall1->attachShape(*wall1Shape);
	RenderItem* wall1RendIt = new RenderItem(wall1Shape, wall1, { 0,1,1,0.2 });
	staticBodiesRI.push_back(wall1RendIt);
	gScene->addActor(*wall1);

	PxRigidStatic* wall2 = gPhysics->createRigidStatic(PxTransform({ 50, -10, 120 }));
	PxShape* wall2Shape = CreateShape(PxBoxGeometry(20, 10, 50));
	wall2->attachShape(*wall2Shape);
	RenderItem* wall2RendIt = new RenderItem(wall2Shape, wall2, { 0,1,1,0.2 });
	staticBodiesRI.push_back(wall2RendIt);
	gScene->addActor(*wall2);
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