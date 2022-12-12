#include "NormalParticleGenerator.h"

NormalParticleGenerator::NormalParticleGenerator(Vector3 pos, Vector3 vel, Vector3 posDesv, Vector3 velDesv, Vector3 acc)
{
	meanPos = pos;
	meanVel = vel;
	this->posDesv = posDesv;
	this->velDesv = velDesv;
	numParticles = 1;
	generationProb = 1;
	this->acc = acc;
	damp = 0.99f;
	mass = 1.0f;
	color = { 0,1,0,1.0 };
}

NormalParticleGenerator::~NormalParticleGenerator()
{
}

list<Particle*> NormalParticleGenerator::generateParticles()
{
	list<Particle*>particles;
	for (int i = 0; i < numParticles; i++) {
		if (abs(d(generator)) < generationProb) {
			Vector3 desvPos = { (float)d(generator) * posDesv.x,(float)d(generator) * posDesv.y ,(float)d(generator) * posDesv.z };
			Vector3 desvVel = { (float)d(generator) * velDesv.x,(float)d(generator) * velDesv.y ,(float)d(generator) * velDesv.z };
			Particle* part = new Particle(meanPos + desvPos, meanVel + desvVel, acc, damp, color);
			part->setMass(mass);
			part->setSpawnTime(GetLastTime());
			part->setLifeTime(5.0);
			particles.push_back(part);
		}

	}

	return particles;
}

list<PxRigidDynamic*> NormalParticleGenerator::generateRigidDynamicParticles(PxPhysics* gPhysics, vector<RenderItem*>& renderItems)
{
	list<PxRigidDynamic*>particles;
	for (int i = 0; i < numParticles; i++) {
		if (abs(d(generator)) < generationProb) {
			Vector3 vel = { 0.0,0.0,-30.0 };
			Vector3 velWidth = { 10.0,10.0,0.0 };
			Vector3 posWidth = { 5.0,5.0,5.0 };
			Vector3 generationPos = meanPos + Vector3(0, 20, 0);
			Vector3 desvPos = { (float)d(generator) * posWidth.x,(float)d(generator) * posWidth.y ,(float)d(generator) * posWidth.z };
			Vector3 desvVel = { (float)d(generator) * velWidth.x,(float)d(generator) * velWidth.y ,(float)d(generator) * velWidth.z };
			PxTransform pos = PxTransform(generationPos + desvPos);
			Vector3 linearVel = vel + desvVel;
			PxRigidDynamic* rdb = gPhysics->createRigidDynamic(pos);
			rdb->setLinearVelocity(linearVel);
			rdb->setAngularVelocity({ 1.0,1.0,1.0 });
			Vector3 size = { 1.0,1.0,1.0 };
			PxShape* shape = CreateShape(PxBoxGeometry(size));
			//PxShape* shape = CreateShape(PxSphereGeometry(1.0));
			float staticFriction = (float)d(generator) * 1.0f;
			PxMaterial* const mat= gPhysics->createMaterial(staticFriction, (float)d(generator), (float)d(generator)*5.0f);
			shape->setMaterials(&mat, 1);
			rdb->attachShape(*shape);
			rdb->setMass(mass);
			rdb->setMassSpaceInertiaTensor({ size.y * size.z,size.x * size.z,size.x * size.y });
			Vector4 color = { 1,0,0,1.0 };
			RenderItem* rendIt = new RenderItem(shape, rdb, color);
			renderItems.push_back(rendIt);
			particles.push_back(rdb);
		}

	}

	return particles;
}

