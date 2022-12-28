#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class Dartboard
{
public:
	Dartboard(float size_, Vector3 pos_);
	~Dartboard();
	void update(double t);
	int score(PxVec3 projPos);
	PxTransform getPos() { return pos1; }
	void setPositionX(double posX);
private: 
	PxTransform pos1, pos2, pos3;
	RenderItem* renderItem1, * renderItem2, * renderItem3;
	float size1, size2, size3;
	double hitTime;
	Vector4 color1, color2, color3, hitColor;
};

