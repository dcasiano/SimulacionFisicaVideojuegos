#include "DetonationButton.h"

DetonationButton::DetonationButton(Vector3 pos_)
{
	pos = PxTransform(pos_.x, pos_.y, pos_.z);
	size = 1;
	color = { 1,0,0,1.0 };
	hitColor = { 0,1,0,1.0 };
	renderItem = new RenderItem(CreateShape(PxBoxGeometry(size, size, size / 10.0)), &pos, color);
}

DetonationButton::~DetonationButton()
{
	DeregisterRenderItem(renderItem);
}

bool DetonationButton::hit(PxVec3 projPos)
{
	if (abs(projPos.z - pos.p.z) < 3.0) {
		if ((projPos.x > pos.p.x - size && projPos.x < pos.p.x + size && projPos.y>pos.p.y - size && projPos.y < pos.p.y + size)) {
			renderItem->color = hitColor;
			return true;
		}
	}
	return false;
}
