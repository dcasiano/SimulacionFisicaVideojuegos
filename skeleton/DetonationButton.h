#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
class DetonationButton
{
public:
	DetonationButton(Vector3 pos_);
	~DetonationButton();
	bool hit(PxVec3 projPos);
	PxTransform getPos() { return pos; }
private:
	PxTransform pos;
	RenderItem* renderItem;
	float size;
	Vector4 color, hitColor;
};

