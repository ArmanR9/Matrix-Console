#pragma once
#include "Arduino.h"
#include "OS.h"
#include "game.h"


class Snake : public GameEngine {
private:

    Vec2 m_snakeBody[256] {};

    int m_snakeLen {1};

    bool m_gameOver {false};

    int m_nDirX {0};
    int m_nDirY {0};
    int m_oDirX {0};
    int m_oDirY {0};

    bool m_isFoodSpawned {false};

    unsigned long m_timer {0};
    unsigned long m_timerThreshold {115}; // ms

    unsigned long m_timeUntilFood {0};
    unsigned long m_timeToFoodThreshold {2000}; // (ms) Calculate via RNG timer
    unsigned long m_foodTimeMin {2000}; // (ms)
    unsigned long m_foodTimeMax {6000}; // (ms)

    unsigned char snakeMap[32] {};




public:


    virtual void update(OS& GameOS);
    virtual Vec2 computePlayerPos(Vec2 Player, int inputX, int inputY, unsigned long &dTimer, unsigned long dInputDelay, int snakeLen);



/* * * * * * * * * *
 * 				   
 *   CONSTRUCTORS  
 * 				   
 * * * * * * * * * */

    Snake()
    {}

/* * * * * * * * * *
 * 				   
 *   DESTRUCTORS  
 * 				   
 * * * * * * * * * */

    ~Snake()
    {}

};
