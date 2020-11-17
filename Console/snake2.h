#pragma once
#include "game.h"
#include "OS.h"

class SnakeGame : public GameEngine {

private:
	static const int width = 32;
	static const int height = 8;
	const float timeBetweenMoves = 0.25;
	const int foodSpawnMillisMin = 400;
	const int foodSpawnMillisMax = 2000;

	unsigned char x[width * height];
	unsigned char y[width * height];

	int snakeLength;
	float timeSinceLastMove;

	int dirX;
	int dirY;
	int nextDirX;
	int nextDirY;

	bool foodExists;
	float timeRemainingToNextFoodSpawn;
	int foodX;
	int foodY;

	bool gameOver;
	float scoreDisplayAmount;

	void placeFood();
	int sign(float);

public:
	SnakeGame();
	virtual void update(OS&);
};
