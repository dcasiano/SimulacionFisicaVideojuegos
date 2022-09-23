#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class Axis
{
public:
	Axis();
	~Axis();
private:
	RenderItem* riX, * riY, * riZ;
};

