#pragma once
#include "core.hpp"
#include "Particle.h"
#include <list>
#include <random>
class ForceGenerator
{
public:
	virtual void updateForce(Particle* p, double duration) = 0;
	std::string name;
	double t = -1e10; // if starting negative -> eternal
};

