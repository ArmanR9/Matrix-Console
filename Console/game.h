#pragma once
#include "OS.h"
#include "utils.h"
#include "constants.h"

class GameEngine{

public:

    enum class GameToSwitch{
		E_SNAKE = 0,
		E_INVADERS,
		E_NO_SWITCH
	};

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
    Vec2 m_Entity {0,0};
    int m_entityX {0};
    int m_entityY {0};

    const int m_gamesLoaded;
    const GameToSwitch m_gameList[2] {GameToSwitch::E_SNAKE, GameToSwitch::E_INVADERS};
    GameToSwitch m_oldGame {GameToSwitch::E_INVADERS};

public:

    void runGame(GameToSwitch currentGame);
    GameToSwitch changeGame(bool isToggled, unsigned long btnPressedTime, unsigned int changeTime, bool inSeconds = false);


    virtual Vec2 computePlayerPos(unsigned int dT, Movement iMovement, Vec2 Player, int inputX, int inputY, int scalar = 1, bool oneAxis = false);
    virtual unsigned long computeRNGTimer(unsigned int iMin, unsigned int iMax, bool faster = false, unsigned int rapidIterate = 0, float bareMin = 0.26);
    virtual Vec2 spawnEntity(Vec2 RangeMin, Vec2 RangeMax, bool complex = false, unsigned char *takenMap = nullptr);
    virtual bool detectCollision(Vec2 Entity1, Vec2 Entity2);
    virtual bool isEntityDeleted(Vec2 Entity);
    virtual Vec2 wrapAround(Vec2 Entity);

    virtual void gameOver(OS &Os);



/**
 * Change Game Method
 *
 * 
 * Call this to check if the game has changed or not.
 * Checks if button is held long enough to warrant game switch.
 *
 * @param changeTime uint -> How long you want to hold button to switch game (in milliseconds or seconds)
 * @param inSeconds bool -> Whether you want to input changeTime as seconds or not (True for seconds, False for ms)
 * 
 * @return Games of type Enum class Games. The game to switch to, or E_NO_SWITCH to indicate no switch.
 */


    GameEngine::GameToSwitch changeGame(unsigned int changeTime, bool inSeconds = false);


    GameEngine(int iGamesLoaded) :
    m_gamesLoaded(iGamesLoaded)
    {}

};
