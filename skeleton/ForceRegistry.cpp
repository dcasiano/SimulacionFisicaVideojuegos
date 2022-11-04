#include "ForceRegistry.h"

ForceRegistry::ForceRegistry()
{
	
}

void ForceRegistry::updateForces()
{
	Particle* p;
	Force f;
	auto p = this->equal_range(f);
	typedef std::multimap<Force, Particle*>::iterator it;
	std::pair<it, it>range(this->equal_range(f));
	
	
}
