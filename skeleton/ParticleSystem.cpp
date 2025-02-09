#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	Vector3 pos, vel, posWidth, velWidth, acc;
	pos = { 0.0,0.0,0.0 };
	posWidth = { 2.0,2.0,2.0 };
	vel = { 0.0,30.0,0.0 };
	velWidth = { 10.0,0.0,10.0 };
	acc = { 0.0,0.0,0.0 };
	//particlesGenerators.push_back(new UniformParticleGenerator(pos, vel, posWidth, velWidth, acc));
	//particlesGenerators.push_back(new NormalParticleGenerator(pos, vel, posWidth, velWidth, acc));
	fireworkGenerator = new CircleGenerator();
	forceReg = new ForceRegistry();
	gravityFG = new GravityForceGenerator({ 0.0,-9.8,0.0 });
	windFG = new WindForceGenerator({ 100,0,0 }, { 20.0,10.0,-40.0 }, 60);
	whirlwindFG = new WhirlwindForceGenerator(5, { 0,30,0 }, 100);
	explosionFG = new ExplosionForceGenerator(1000000, { 9, -13, 170 }, 20, 343);
	anchSprFG = nullptr;
	generateSpringDemo();
	shootPartGen = new ShootParticleGenerator();
	score = 0;
	rdWallGen = new RDWallGenerator();
}

ParticleSystem::~ParticleSystem()
{
	delete fireworkGenerator;
	delete forceReg;
	delete gravityFG;
	delete windFG;
	delete whirlwindFG;
	delete anchSprFG;
	forceGenerators.clear();
	for (auto e : rdBodiesRI)DeregisterRenderItem(e);
	rdBodiesRI.clear();
	rdParticles.clear();
	delete shootPartGen;
	bullets.clear();
	wallParts.clear();
	particles.clear();
	dartboardMotionGuide.clear();
}

void ParticleSystem::update(double t)
{
	forceReg->updateForces(t);
	

	//for (auto e : particlesGenerators) {
	//	list<Particle*> part = e->generateParticles();
	//	for (auto p : part) {
	//		forceReg->addRegistry(gravityFG, p);
	//		//forceReg->addRegistry(windFG, p);
	//		forceReg->addRegistry(whirlwindFG, p);
	//		particles.push_back(p);
	//	}
	//}
	// Rigid dynamic bodies
	/*if (rdParticles.size() < maxRigidInstances) {
		for (auto e : particlesGenerators) {
			list<RigidDynamicParticle*> bodies = e->generateRigidDynamicParticles(gPhysics, rdBodiesRI);
			for (auto rdb : bodies) {
				rdParticles.push_back(rdb);
				gScene->addActor(*rdb->getRigidDynamicBody());
			}
		}
	}*/
	//for (auto e : rdParticles)whirlwindFG->updateForceRDBody(e->getRigidDynamicBody());
	
	for (int i = 0; i < particles.size(); i++) {
		particles.at(i)->integrate(t);
		if (!particles.at(i)->isAlive() /*|| particles.at(i)->getPosition().y < 0.0f*/) {
			forceReg->deleteParticle(particles.at(i));
			delete particles.at(i);
			particles.erase(particles.begin() + i);
		}
		
	}
	for (int i = 0; i < rdParticles.size(); i++) {
		if (rdParticles.at(i)->hasToDie()) {
			delete rdParticles.at(i);
			rdParticles.erase(rdParticles.begin() + i);
		}

	}
	for (int i = 0; i < wallParts.size(); i++) {
		if (wallSleeping && !wallParts.at(i)->getRigidDynamicBody()->isSleeping()) {
			wallHitTime = GetLastTime();
			wallSleeping = false;
		}

	}
	if (!wallSleeping && !wallIsDestroyed && wallHitTime + 2.0 < GetLastTime()) {
		destroyWall();
	}
	for (int i = 0; i < dartboardMotionGuide.size(); i++) {
		dartboardMotionGuide.at(i)->integrate(t);

	}
	dartboard->setPositionX(dartboardMotionGuide[0]->getPosition().x);
	for (int i = 0; i < bullets.size(); i++) {
		int auxScore = dartboard->score(bullets.at(i)->getRigidDynamicBody()->getGlobalPose().p);
		windFG->updateForceRDBody(bullets.at(i)->getRigidDynamicBody());
		bool detButHit = detButton->hit(bullets.at(i)->getRigidDynamicBody()->getGlobalPose().p);
		if (detButHit)generateExplosion();
		if (auxScore > 0 || detButHit || bullets.at(i)->hasToDie()) {
			score += auxScore;
			delete bullets.at(i);
			bullets.erase(bullets.begin() + i);
		}
	}

	// Fireworks
	for (int i = 0; i < fireworks.size(); i++) {
		fireworks.at(i)->integrate(t);
		if (!fireworks.at(i)->isAlive()) {
			if (fireworks.at(i)->hasToExplode()) {
				int newId = fireworks.at(i)->getId() + 1;
				int numExplosions = fireworks.at(i)->getNumExplosions();
				Vector4 color = { 1,newId / (float)numExplosions,0,1 };
				fireworkGenerator->setParams(fireworks.at(i)->getPosition(), { 0,0,0 }, { 2,2,2 }, { 30,30,30 }, color);
				list<Firework*> fw = fireworkGenerator->generateParticles(newId, numExplosions, fireworks.at(i)->getLifeTime());
				for (auto e : fw)fireworks.push_back(e);
			}
			forceReg->deleteParticle(fireworks.at(i));
			delete fireworks.at(i);
			fireworks.erase(fireworks.begin() + i);
		}

	}

}

void ParticleSystem::shootFirework()
{
	Firework* fw = new Firework({ -80,00,-100 }, { 0,80,0 }, { 0,-10,0 }, 0.99f, { 1,0,0,1 }, 0, 2);
	fw->setSpawnTime(GetLastTime());
	fw->setLifeTime(2.0);
	fireworks.push_back(fw);

	Firework* fw2 = new Firework({ 120,00,-100 }, { 0,80,0 }, { 0,-10,0 }, 0.99f, { 1,0,0,1 }, 0, 2);
	fw2->setSpawnTime(GetLastTime());
	fw2->setLifeTime(2.0);
	fireworks.push_back(fw2);
}

void ParticleSystem::generateTestParticles(int num, const Vector3& pos, double r)
{
	default_random_engine generator;
	generator.seed(GetLastTime());
	normal_distribution<double>d{ -1.0,1.0 };
	for (int i = 0; i < num; i++) {
		float theta = (float)d(generator) * 2 * 3.141592564;
		float phi = acosf(2 * (float)d(generator) - 1);
		float rad = cbrt((float)d(generator) * r*50);
		float sinTheta = sinf(theta);
		float cosTheta = cosf(theta);
		float sinPhi = sinf(phi);
		float cosPhi = cosf(phi);
		Vector3 partPos = { pos.x + rad * sinPhi * cosTheta ,pos.y + rad * sinPhi * sinTheta ,pos.z + rad * cosPhi };

		Particle* part = new Particle(partPos, { 0,0,0 }, { 0,0,0 }, 0.99f, { 0,1,0,1 });
		part->setSpawnTime(GetLastTime());
		part->setLifeTime(10.0);
		//forceReg->addRegistry(whirlwindFG, part);
		particles.push_back(part);
	}
}

void ParticleSystem::generateExplosion()
{
	for (auto p : particles) {
		forceReg->addRegistry(explosionFG, p);
	}
	explosionFG->setInitialTime(GetLastTime());
	for (auto e : rdParticles)explosionFG->generateExplotionForRDBody(e->getRigidDynamicBody());
	for (auto e : wallParts)explosionFG->generateExplotionForRDBody(e->getRigidDynamicBody());
}

void ParticleSystem::generateSpringDemo()
{
	// Anchored spring
	/*Particle* p = new Particle({ -10,20,0 }, { 0,0,0 }, { 0,0,0 }, 0.85, { 0,1,0,1 });
	anchSprFG = new AnchoredSpringFG(10, 10, { 10,20,0 });
	forceReg->addRegistry(anchSprFG, p);
	forceReg->addRegistry(gravityFG, p);
	particles.push_back(p);
	forceGenerators.push_back(anchSprFG);*/

	// Elastic band
	/*Particle* p1 = new Particle({ -50,30,0 }, { -00,0,0 }, { 0,0,0 }, 0.95, { 0,1,0,1 });
	Particle* p2 = new Particle({ 50,30,0 }, { 00,0,0 }, { 0,0,0 }, 0.95, { 0,0,1,1 });
	ElasticBandFG* ebFG1 = new ElasticBandFG(p2, 10, 30);
	ElasticBandFG* ebFG2 = new ElasticBandFG(p1, 10, 30);
	forceReg->addRegistry(ebFG1, p1);
	forceReg->addRegistry(ebFG2, p2);
	particles.push_back(p1);
	particles.push_back(p2);
	forceGenerators.push_back(ebFG1);
	forceGenerators.push_back(ebFG2);*/

	// Slinky
	//generateSlinky();

	// Buoyancy
	/*Particle* cube = new Particle({ 0,20,0 }, { 0,0,0 }, { 0,0,0 }, 0.85, { 0,1,0,1 });
	cube->setAsCube();
	particles.push_back(cube);
	forceReg->addRegistry(gravityFG, cube);
	BuoyancyFG* bFG = new BuoyancyFG(1, 0.01, 1000);
	forceReg->addRegistry(bFG, cube);
	forceGenerators.push_back(bFG);*/


	
}

void ParticleSystem::generateSlinky()
{
	double k = 20, restLength = 10;
	float y0 = 60;
	float dist = 4; // initial distance between each particle
	AnchoredSpringFG* anchSprFG = new AnchoredSpringFG(k, restLength, { 0,y0,0 });
	Particle* p1 = new Particle({ 0,y0 - dist,0 }, { 0,0,0 }, { 0,0,0 }, 0.95, { 0,1,1,1 });
	forceReg->addRegistry(anchSprFG, p1);
	forceReg->addRegistry(gravityFG, p1);
	particles.push_back(p1);
	forceGenerators.push_back(anchSprFG);
	Particle* p2 = new Particle({ 0,y0 - 2 * dist,0 }, { -00,0,0 }, { 0,0,0 }, 0.95, { 0,1,0.5,1 });
	SpringForceGenerator* ebFG12 = new SpringForceGenerator(p2, k, restLength);
	SpringForceGenerator* ebFG21 = new SpringForceGenerator(p1, k, restLength);
	forceReg->addRegistry(ebFG12, p1);
	forceReg->addRegistry(ebFG21, p2);
	forceReg->addRegistry(gravityFG, p2);
	particles.push_back(p2);
	forceGenerators.push_back(ebFG12);
	forceGenerators.push_back(ebFG21);
	Particle* p3 = new Particle({ 0,y0 - 3 * dist,0 }, { -00,0,0 }, { 0,0,0 }, 0.95, { 0,1,0,1 });
	SpringForceGenerator* ebFG23 = new SpringForceGenerator(p3, k, restLength);
	SpringForceGenerator* ebFG32 = new SpringForceGenerator(p2, k, restLength);
	forceReg->addRegistry(ebFG23, p2);
	forceReg->addRegistry(ebFG32, p3);
	forceReg->addRegistry(gravityFG, p3);
	particles.push_back(p3);
	forceGenerators.push_back(ebFG23);
	forceGenerators.push_back(ebFG32);
}

void ParticleSystem::shootBullet()
{
	if (shootPartGen->canShoot()) {
		list<RigidDynamicParticle*> bodies = shootPartGen->generateRigidDynamicParticles(gPhysics, rdBodiesRI);
		for (auto rdb : bodies) {
			bullets.push_back(rdb);
			gScene->addActor(*rdb->getRigidDynamicBody());
		}
	}
}

int ParticleSystem::getScore()
{
	int auxScore = score;
	score = 0;
	return auxScore;
}

void ParticleSystem::createRDWall()
{
	list<RigidDynamicParticle*> bodies = rdWallGen->generateRigidDynamicParticles(gPhysics, rdBodiesRI);
	for (auto rdb : bodies) {
		wallParts.push_back(rdb);
		gScene->addActor(*rdb->getRigidDynamicBody());
		rdb->getRigidDynamicBody()->putToSleep();
	}
}

void ParticleSystem::destroyWall()
{
	for (auto e : wallParts)delete e;
	wallParts.clear();
	wallIsDestroyed = true;
}

void ParticleSystem::generateDartboardMotion()
{
	Particle* p1 = new Particle({ -2,-20,50 }, { -00,0,0 }, { 0,0,0 }, 0.95, { 0,1,0,1 });
	Particle* p2 = new Particle({ 38,-20,50 }, { 00,0,0 }, { 0,0,0 }, 0.95, { 0,0,1,1 });
	ElasticBandFG* ebFG1 = new ElasticBandFG(p2, 2, 20);
	ElasticBandFG* ebFG2 = new ElasticBandFG(p1, 2, 20);
	forceReg->addRegistry(ebFG1, p1);
	forceReg->addRegistry(ebFG2, p2);
	dartboardMotionGuide.push_back(p1);
	dartboardMotionGuide.push_back(p2);
	forceGenerators.push_back(ebFG1);
	forceGenerators.push_back(ebFG2);
}