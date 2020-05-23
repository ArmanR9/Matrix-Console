#pragma once
#include "OS.h"

class GameEngine : public OS{
public:

enum class Movement{
    E_SIMPLE = 0,
    E_COMPLEX
};

enum DirectionX{
    E_LEFT = -1,
    E_STATIONARY,
    E_RIGHT
};

enum DirectionY{
    E_DOWN = -1,
    E_STATIONARY,
    E_UP
};

private:

DirectionX m_dirX {DirectionX::E_STATIONARY};
DirectionY m_dirY {DirectionY::E_STATIONARY};

public:

virtual void computePlayerPos();
virtual void spawnEntity();
virtual bool detectCollision(int posX, int posY, int posX2, int posY2);
virtual bool isEntityDeleted(int entityX, int entityY);
virtual void wrapAround(int& outPosX, int& outPosY);

virtual void gameOver();

};
