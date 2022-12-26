#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <string>
#include <list>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "NormalParticleGenerator.h"
#include "CircleGenerator.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "ElasticBandFG.h"
#include "BuoyancyFG.h"
#include "ShootParticleGenerator.h"
#include "RigidDynamicParticle.h"

using namespace physx;
using namespace std;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void shootFirework();
	void generateTestParticles(int num, const Vector3& pos, double r);
	void generateExplosion();
	void generateSpringDemo();
	void increaseSpringK(double amount) { if (anchSprFG != nullptr)anchSprFG->increaseK(amount); }
	void generateSlinky();
	void setPxPhysics(PxPhysics* gPhysics) { this->gPhysics = gPhysics; }
	void setPxScene(PxScene* gScene) { this->gScene = gScene; }
	void WhirlwindActive() { if (whirlwindFG != nullptr)whirlwindFG->switchActive(); }
	//void addParticleToRegistry(Particle* p){forceReg->addRegistry}
	//void deleteParticleFromRegistry(Particle* p) { forceReg->deleteParticle(p); }
	void shootBullet();
private:
	//list<Particle*>particles;
	vector<Particle*>particles;
	list<ParticleGenerator*>particlesGenerators;
	vector<Firework*>fireworks;
	CircleGenerator* fireworkGenerator;
	ForceRegistry* forceReg;
	vector<ForceGenerator*>forceGenerators;
	GravityForceGenerator* gravityFG;
	WindForceGenerator* windFG;
	WhirlwindForceGenerator* whirlwindFG;
	ExplosionForceGenerator* explosionFG;
	AnchoredSpringFG* anchSprFG;
	PxPhysics* gPhysics;
	PxScene* gScene;
	const int maxRigidInstances = 100;
	vector<RigidDynamicParticle*>rdParticles;
	vector<RenderItem*>rdBodiesRI;
	ShootParticleGenerator* shootPartGen;
};

