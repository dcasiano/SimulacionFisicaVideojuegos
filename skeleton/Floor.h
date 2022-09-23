#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class Floor
{
public:
	Floor(float size_, Vector3 pos_);
	~Floor();
	void integrate(double t);
private: 
	PxTransform pos;
	RenderItem* renderItem;
};

