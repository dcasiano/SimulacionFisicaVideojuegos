#pragma once
#include <iostream>
#include "ParticleSystem.h"
#include <string>

class GameManager
{
public:
	GameManager();
	~GameManager();
	void update();
	void updateScore(int score);
	void setPartSyst(ParticleSystem* partSyst) { this->partSyst = partSyst; }
	void setWindActiveIndicator(RenderItem* windActiveIndicator) { this->windActiveIndicator = windActiveIndicator; }
protected:
	int score, maxScore;
	ParticleSystem* partSyst;
	bool gameInProgress, win;
	RenderItem* windActiveIndicator;
	double lastTimeWindActiveChange, windActiveChangeCooldown;
	bool windIsActive;
	Vector3 windVel;
	Vector4 windActiveColor, windInactiveColor;
};

