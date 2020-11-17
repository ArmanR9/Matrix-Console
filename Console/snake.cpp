#include "snake.h"
#include "string.h"

int dirX = 0;
int dirY = 0;

void Snake::update(OS& GameOS){

// Game Over Logic
    if(m_gameOver){
        static bool gameOverAnim = true;
        GameOS.Scr.clear();

        if(gameOverAnim)
            gameOver(GameOS);

        gameOverAnim = false;

        if(GameOS.Joy.getJoyX() > 100) // Placeholder: Replace with using button held for > 5 seconds later
            m_gameOver = false;

        return;
    }

// Update Timer
    m_timer += GameOS.getFrame_dT();
  

 // Input and update head position
    Vec2 head = computePlayerPos(m_snakeBody[0], GameOS.Joy.getJoyX(), GameOS.Joy.getJoyY(), m_timer, m_timerThreshold, m_snakeLen);


// Updating Position and tail and Snake Occupancy map

    memset(snakeMap, 0, sizeof(snakeMap));

    for(int i {m_snakeLen-1}; i > 0; --i){

        m_snakeBody[i].x = m_snakeBody[i-1].x;
        m_snakeBody[i].y = m_snakeBody[i-1].y;

        snakeMap[m_snakeBody[i].x] |= 1 << m_snakeBody[i].y;

        if(detectCollision(m_snakeBody[0], m_snakeBody[i])){
            m_gameOver = true;
            GameOS.Buzz.buzzer(200, 1000, 1000);
        }
    }
    
    m_snakeBody[0] = head;
    snakeMap[m_snakeBody[0].x] |= 1 << m_snakeBody[0].y; 


// Food Logic

    // Handle Food eating 

    if(m_isFoodSpawned){

     /*   if(detectCollison(headVec, foodVec)){
        
        m_snakeLen++;

        m_isFoodSpawned = false;
       */// }
    } 

    // Increment timer, and handle food spawning 
    else{
       m_timeUntilFood += GameOS.getFrame_dT();
            if(m_timeUntilFood > m_timeToFoodThreshold){
              //  FoodPos = spawnEntity(Vec2 RangeMin, Vec2 RangeMax, bool complex = true, unsigned char *takenMap = nullptr);
                m_timeToFoodThreshold = computeRNGTimer(m_foodTimeMin, m_foodTimeMax);
      }
    }

    // Draw Snake and Food to screen
  //  if(m_isFoodSpawned)
      //  GameOS.Scr.setLED(food.x, food.y, true);

    for(int i {0}; i < m_snakeLen; ++i)
        GameOS.Scr.setLED(m_snakeBody[i].x, m_snakeBody[i].y, true);
   
}




Vec2 Snake::computePlayerPos(Vec2 Player, int inputX, int inputY, unsigned long &dTimer, unsigned long dInputDelay, int snakeLen){

  if(inputX || inputY){
      if(abs(inputX) > abs(inputY)){
        int newX = sgn(inputX);

        if(newX != -m_oDirX && snakeLen > 1){
          m_nDirX = newX;
          m_nDirY = 0;
        }
        else if(snakeLen == 1){
         m_nDirX = newX;
         m_nDirY = 0;
        }
      }
      else{
        int newY = sgn(inputY);

        if(newY != -m_oDirY && snakeLen > 1){
          m_nDirY = newY;
          m_nDirX = 0;
        }
        else if(snakeLen == 1){
          m_nDirY = newY;
          m_nDirX = 0;
        }
    } 
  }
  
    if(dTimer > dInputDelay){
        dTimer -= dInputDelay;

           m_oDirX = m_nDirX;
           m_oDirY = m_nDirY;

            
          Player.x += m_nDirX;
          Player.y += m_nDirY;
                
        Player = wrapAround(Player);
    
    }
    return Player;
}




int array[256] {0};

int array1 = 1;
int array2 = 0;
int array3 = 0;
int array4 = 0;

int* node = NULL;
