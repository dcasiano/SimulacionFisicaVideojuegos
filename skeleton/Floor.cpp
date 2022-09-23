#include "Floor.h"

Floor::Floor(float size_, Vector3 pos_)
{
	pos = PxTransform(pos_.x, pos_.y, pos_.z);
	renderItem = new RenderItem(CreateShape(PxBoxGeometry(size_, size_, 0)), &pos, { 0,0,0.5,1.0 });
}

Floor::~Floor()
{
	DeregisterRenderItem(renderItem);
}

void Floor::integrate(double t)
{
}
