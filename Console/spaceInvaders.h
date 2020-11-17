#pragma once
#include "game.h"
#include "OS.h"
#include "utils.h"

class SpaceGame : public Game {
private:
	// Difficulty settings:
	const float enemySpeed = 6;
	const float spawnDelayStart = 2;
	const float spawnDelayEnd = .5;
	const float difficultyDuration = 18;
	const float delayBetweenShots = .2;
	const float playerSpeed = 8.5;

	Vec2 playerPos;
	Vec2 bullets[16];
	Vec2 enemies[32];

	int numEnemies;
	int numBullets;
	int numEnemiesDestroyed;
	float timeToNextEnemySpawn;
	float scoreDisplayAmount;
	float lastShootTime;
	float elapsedTime;
	bool gameOver;
	
	
public:
	SpaceGame();
	virtual void updateLoop(OS&);
};