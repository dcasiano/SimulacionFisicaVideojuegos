#include "GameManager.h"

GameManager::GameManager()
{
	score = 0;
	maxScore = 200;
	gameInProgress = true;
	win = false;
	lastTimeWindActiveChange = 0;
	windActiveChangeCooldown = 3;
	windVel = { 200,0,0 };
	windIsActive = false;
	windActiveColor = { 1,0,0,1.0 };
	windInactiveColor = { 0,1,0,1.0 };
}

GameManager::~GameManager()
{
}
void GameManager::update()
{
	if (lastTimeWindActiveChange + windActiveChangeCooldown < GetLastTime()) {
		lastTimeWindActiveChange = GetLastTime();
		if (!windIsActive) {
			partSyst->setWindVelocity(windVel);
			windIsActive = true;
			windActiveIndicator->color = windActiveColor;
		}
		else{
			partSyst->setWindVelocity({ 0,0,0 });
			windIsActive = false;
			windActiveIndicator->color = windInactiveColor;
		}
	}
}
void GameManager::updateScore(int score)
{
	if (gameInProgress && score > 0) {
		this->score += score;
		std::cout << "Score: " << this->score << "\n";
		if (this->score >= maxScore) {
			gameInProgress = false;
			win = true;
			partSyst->shootFirework();
		}
	}
}
