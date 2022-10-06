#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class Dartboard
{
public:
	Dartboard(float size_, Vector3 pos_);
	~Dartboard();
	void integrate(double t);
	int score(PxVec3 projPos);
private: 
	PxTransform pos1, pos2, pos3;
	RenderItem* renderItem1, * renderItem2, * renderItem3;
	float size1, size2, size3;
};

