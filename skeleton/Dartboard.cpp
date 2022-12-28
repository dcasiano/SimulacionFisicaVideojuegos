#include "Dartboard.h"

Dartboard::Dartboard(float size_, Vector3 pos_)
{
	pos1 = PxTransform(pos_.x, pos_.y, pos_.z);
	pos2 = PxTransform(pos_.x, pos_.y, pos_.z + 1);
	pos3 = PxTransform(pos_.x, pos_.y, pos_.z + 2);
	size1 = size_;
	size2 = size_ / 1.5;
	size3 = size_ / 4;
	hitTime = 0;
	color1 = { 1,0,0,1.0 };
	color2 = { 1,1,1,1.0 };
	color3 = { 1,0,0,1.0 };
	hitColor = { 1,1,0,1.0 };
	renderItem1 = new RenderItem(CreateShape(PxBoxGeometry(size1, size1, 0.01)), &pos1, color1);
	renderItem2 = new RenderItem(CreateShape(PxBoxGeometry(size2, size2, 0.01)), &pos2, color2);
	renderItem3 = new RenderItem(CreateShape(PxBoxGeometry(size3, size3, 0.01)), &pos3, color3);
}

Dartboard::~Dartboard()
{
	DeregisterRenderItem(renderItem1);
	DeregisterRenderItem(renderItem2);
	DeregisterRenderItem(renderItem3);
}

void Dartboard::update(double t)
{
	if (hitTime + 0.5 < GetLastTime()) {
		renderItem1->color = color1;
		renderItem2->color = color2;
		renderItem3->color = color3;
	}
}

int Dartboard::score(PxVec3 projPos)
{
	int score = 0;
	if (abs(projPos.z - pos1.p.z) < 3.0) {
		if ((projPos.x > pos3.p.x - size3 && projPos.x < pos3.p.x + size3 && projPos.y>pos3.p.y - size3 && projPos.y < pos3.p.y + size3)) {
			score = 100;
			renderItem3->color = hitColor;
			hitTime = GetLastTime();
		}
		else if ((projPos.x > pos2.p.x - size2 && projPos.x < pos2.p.x + size2 && projPos.y>pos2.p.y - size2 && projPos.y < pos2.p.y + size2)) {
			score = 50;
			renderItem2->color = hitColor;
			hitTime = GetLastTime();
		}
		else if ((projPos.x > pos1.p.x - size1 && projPos.x < pos1.p.x + size1 && projPos.y>pos1.p.y - size1 && projPos.y < pos1.p.y + size1)) {
			score = 10;
			renderItem1->color = hitColor;
			hitTime = GetLastTime();
		}
	}
	return score;
}

void Dartboard::setPositionX(double posX)
{
	pos1 = PxTransform(posX, pos1.p.y, pos1.p.z);
	pos2 = PxTransform(posX, pos2.p.y, pos2.p.z);
	pos3 = PxTransform(posX, pos3.p.y, pos3.p.z);
}