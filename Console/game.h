#pragma once
#include "OS.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

class GameEngine : public OS{

public:

    enum class Movement{
        E_SIMPLE = 0,
        E_COMPLEX
    };

    enum DirectionX{
        E_LEFT_X = -1,
        E_STATIONARY_X,
        E_RIGHT_X
    };

    enum DirectionY{
        E_DOWN_Y = -1,
        E_STATIONARY_Y,
        E_UP_Y
    };

private:

    DirectionX m_dirX {DirectionX::E_STATIONARY_X};
    DirectionY m_dirY {DirectionY::E_STATIONARY_Y};

public:

    virtual void computePlayerPos(Movement iMovement, int& posX, int& posY, int inputX, int inputY, int scalar = 1, bool oneAxis = false);
    virtual void spawnEntity();
    virtual bool detectCollision(int posX, int posY, int posX2, int posY2);
    virtual bool isEntityDeleted(int entityX, int entityY);
    virtual void wrapAround(int& outPosX, int& outPosY);

    virtual void gameOver();

};
