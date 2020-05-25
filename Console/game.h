#pragma once
#include "OS.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T> T clip(T val, T higher, T lower) {
    val = val > higher ? higher : val;
    val = val < lower ? lower : val;
    return val;
}

 struct Vec2{
    int x;
    int y;
 };

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

    enum class TimeUnits{
        E_MS = 0,
        E_SECONDS
    };

private:

    DirectionX m_dirX {DirectionX::E_STATIONARY_X};
    DirectionY m_dirY {DirectionY::E_STATIONARY_Y};
    Vec2 m_Entity = {0,0};
    int m_entityX {0};
    int m_entityY {0};
    OS::Games m_oldGame {OS::Games::E_INVADERS};

public:
    void runGame(OS::Games currentGame);

    virtual Vec2 computePlayerPos(Movement iMovement, Vec2 Player, int inputX, int inputY, int scalar = 1, bool oneAxis = false);
    virtual unsigned long computeRNGTimer(unsigned int iMin, unsigned int iMax, bool faster = false, unsigned int slowDown = 0);
    virtual Vec2 spawnEntity(Vec2 RangeMin, Vec2 RangeMax, bool complex = false, unsigned char *takenMap = nullptr);
    virtual bool detectCollision(Vec2 Entity1, Vec2 Entity2);
    virtual bool isEntityDeleted(Vec2 Entity);
    virtual Vec2 wrapAround(Vec2 Entity);

    virtual void gameOver();

    GameEngine(){}

};
