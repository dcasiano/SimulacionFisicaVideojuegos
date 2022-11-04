#pragma once
#include <map>
#include "Particle.h"
using Force = Vector3;
class ForceRegistry:public std::multimap<Force,Particle*> // tiene que ser multimap<ForceGenerator,Particle*>
{
public:
	ForceRegistry();
	~ForceRegistry(){}
	void addRegistry(Force f, Particle* p) { this->insert(std::pair<Force,Particle*>( f,p )); p->addForce(f); }
	void updateForces();
protected:
	//std::multimap<Force, Particle*> map;
};

