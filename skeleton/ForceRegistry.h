#pragma once
#include <map>
#include "ForceGenerator.h"
class ForceRegistry:public std::multimap<ForceGenerator*,Particle*>
{
public:
	ForceRegistry();
	~ForceRegistry(){}
	void addRegistry(ForceGenerator* fg, Particle* p) { insert(std::pair<ForceGenerator*,Particle*>( fg,p )); }
	void updateForces(double duration);
	void deleteForceGenerator(ForceGenerator* fg) { erase(fg); }
	void deleteParticle(Particle* p);
protected:
	//std::multimap<Force, Particle*> map;
};

