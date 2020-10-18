#pragma once
#include "OS.h"
#include "utils.h"
#include "constants.h"

class GameEngine{

public:

    enum class GameList{
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
    const GameList m_gameList[2] {GameList::E_SNAKE, GameList::E_INVADERS};
    GameList m_oldGame {GameList::E_SNAKE};

public:

/**
 * Update Interface Method
 *
 * 
 * This method is left to the derived (games) classes to implement
 * This method should define how the game procedure should work
 * 
 * @param GameOS OS reference -> Instance of OS object to manipulate I/O
 * 
 * @return void
 */

    virtual void update(OS& GameOS) = 0;

/**
 * Run Current Game Method
 *
 * 
 * This method implements behavior to switch the GameEngine object
 * to be an instance of any derived class game (using new and delete)
 * 
 * @param currentGame GameList -> Name of Game to switch to, or no switch.
 * 
 * @return void
 */

    void runGame(GameList currentGame);

/**
 * Change Game Method
 *
 * 
 * Call this to check if the game has changed or not.
 * Checks if button is held long enough to warrant game switch.
 * 
 * @param isToggled bool -> Input of whether button is toggled (use Button::getBtnToggle())
 * @param btnPressedTime uint long -> Input of how long button is pressed (use Button::getBtnPressed())
 * @param changeTime uint -> How long you want to hold button to switch game (in milliseconds or seconds)
 * @param inSeconds bool -> Whether you want to input changeTime as seconds or not (True for seconds, False for ms)
 * 
 * @return Games of type Enum class Games. The game to switch to, or E_NO_SWITCH to indicate no switch.
 */

    GameList changeGame(bool isToggled, unsigned long btnPressedTime, unsigned int changeTime, bool inSeconds = false);

/**
 * Compute Player Position Method
 *
 * Virtual (Abstract Method)
 * 
 * Call this to update and compute player position
 * can be reimplemented to specific games need (generic implementation)
 * as it's marked virtual
 * 
 * @param dT uint -> Delta Time between CPU Cycles (used to adjust player speed)
 * @param iMovement Movement enum -> Complex or Simple movement (adjusting speed, multi direction, or single direction)
 * @param Player Vec2 -> Players x,y coordinate data
 * @param inputX int -> Input for the X axis of translation
 * @param inputY int -> Input for the T axis of translation
 * @param scalar int -> Scalar for speed (higher = faster) (only if using complex behavior)
 * @param oneAxis bool -> Boolean for whether you want one axis control at a time and not multi-axis simulatenously
 * 
 * 
 * @return Vec2 -> Player's new position
 */

    virtual Vec2 computePlayerPos(unsigned int dT, Movement iMovement, Vec2 Player, int inputX, int inputY, int scalar = 1, bool oneAxis = false);


/**
 * Compute RNG timer
 *
 * Virtual (Abstract Method)
 * 
 * Call this to compute a random generated timer (i,e; for spawning entities)
 * This can be reimplemented to specific games need (generic implementation)
 * as it's marked virtual
 * 
 * NOTE: iMin is not the ABSOLUTE minimum. If using faster flag, the time duration will be lower than iMin.
 * Set bareMin to the lowest possible time duration you are okay with.
 * 
 * @param iMin uint -> (ms) Minimum range the time duration can be (look at above NOTE:)
 * @param iMax uint -> (ms) Maximum range the time duration can be
 * @param faster bool -> Enables fast time behavior (perfect for increasing diffulculty)
 * @param rapidIterate uint -> (0-5) Increase to rapidly iterate time durations generated (only works if faster = true)
 * @param bareMin float -> Absolute Bare Minimum the time duration can be (default = 0.26s) 
 * 
 * 
 * @return uint long -> generated time duration (ms)
 */

    virtual unsigned long computeRNGTimer(unsigned int iMin, unsigned int iMax, bool faster = false, unsigned int rapidIterate = 0, float bareMin = 0.26);


/**
 * Spawn Entity Method
 *
 * Virtual (Abstract Method)
 * 
 * Call this to compute a random generated spawn location (i,e; for spawning entities)
 * This can be reimplemented to specific games need (generic implementation)
 * as it's marked virtual
 * 
 * NOTE: complex flag uses an occupancyMap, to map to tiles that aren't utilized according to the 
 * takenMap byte array. Only use if you set up the takenMap byte array correctly.
 * 
 * @param iMin uint -> (ms) Minimum range the time duration can be (look at above NOTE:)
 * @param iMax uint -> (ms) Maximum range the time duration can be
 * @param faster bool -> Enables fast time behavior (perfect for increasing diffulculty)
 * @param rapidIterate byte array -> (0-5) Increase to rapidly iterate time durations generated (only works if faster = true)
 * 
 * 
 * @return Vec2 -> Coordinates of Entity location.
 */

    virtual Vec2 spawnEntity(Vec2 RangeMin, Vec2 RangeMax, bool complex = false, unsigned char *takenMap = nullptr);

/**
 * Detect Collision Method
 *
 * Virtual (Abstract Method)
 * 
 * Call this to check if two entities have collided with each other
 * 
 * This can be reimplemented to specific games need (generic implementation)
 * as it's marked virtual
 * 
 * 
 * @param Entity1 Vec2 -> x,y coords of Entity1
 * @param Entity2 Vec2 -> x,y coords of Entity2
 * 
 * 
 * 
 * @return bool -> Yes if entities collided. No if they didn't.
 */

    virtual bool detectCollision(Vec2 Entity1, Vec2 Entity2);

/**
 * Detect Entity is Deleted method
 *
 * Virtual (Abstract Method)
 * 
 * Call this to check if the Entity is out of screen bounds and hence deleted
 * 
 * This can be reimplemented to specific games need (generic implementation)
 * as it's marked virtual
 * 
 * 
 * @param Entity1 Vec2 -> x,y coords of Entity
 * 
 * 
 * 
 * @return bool -> Yes if entities is out of bounds. No if it isn't.
 */

    virtual bool isEntityDeleted(Vec2 Entity);

/**
 * Detect Entity Wrap Around method
 *
 * Virtual (Abstract Method)
 * 
 * Call this to check and compute new coordinates for Entity if it has
 * wrapped around.
 * 
 * This can be reimplemented to specific games need (generic implementation)
 * as it's marked virtual
 * 
 * 
 * @param Entity Vec2 -> x,y coords of Entity
 * 
 * 
 * 
 * @return Vec2 -> New coords of Entity if wrap around has occured. 
 */

    virtual Vec2 wrapAround(Vec2 Entity);

/**
 * Game Over method
 *
 * Virtual (Abstract Method)
 * 
 * Call this to trigger game over animation (prints GAME OVER, and MATX)
 * 
 * This can be reimplemented to specific games need (generic implementation)
 * as it's marked virtual
 * 
 * 
 * @param Os -> OS& - Current Instance of OS object
 * 
 * 
 * 
 * @return Vec2 -> New coords of Entity if wrap around has occured. 
 */

    virtual void gameOver(OS &Os);


/* * * * * * * * * *
 * 				   
 *   CONSTRUCTORS  
 * 				   
 * * * * * * * * * */

// Default ctor
// Init how many games loaded on the board.

    GameEngine(int iGamesLoaded) :
    m_gamesLoaded(iGamesLoaded)
    {}

    GameEngine(): m_gamesLoaded(2) {}


/* * * * * * * * * *
 * 				   
 *   DESTRUCTORS  
 * 				   
 * * * * * * * * * */

    ~GameEngine()
    {}

};
