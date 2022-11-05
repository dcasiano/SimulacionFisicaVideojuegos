#include "ForceRegistry.h"

ForceRegistry::ForceRegistry()
{
}

void ForceRegistry::updateForces(double duration)
{
	/*Particle* p;
	Force f;
	auto p = this->equal_range(f);
	typedef std::multimap<Force, Particle*>::iterator it;
	std::pair<it, it>range(this->equal_range(f));*/
	for (auto it = begin(); it != end(); it++) {
		it->first->updateForce(it->second, duration);
	}
	
}

void ForceRegistry::deleteParticle(Particle* p)
{
	/*for (auto it = begin(); it != end(); it++) {
		if (it->second == p) {
			erase(it);
		}
	}*/
	for (auto it = begin(); it != end();) {
		auto erase_it = it++;
		if (erase_it->second == p) {
			erase(erase_it);
		}
	}
}
