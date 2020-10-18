#include "game.h"


void GameEngine::runGame(GameList currentGame){

    if(currentGame == GameList::E_NO_SWITCH){
        // just update
        return;
    }
    else{
        if(currentGame != m_oldGame){
        //  delete this;

            switch(currentGame){
                case(GameList::E_SNAKE):
                    //this = Snake();
                    m_oldGame = GameList::E_SNAKE; 
                    break;

                case(GameList::E_INVADERS):
                    // this = Invaders();
                    m_oldGame = GameList::E_INVADERS;
                    break;
            }
            // update game
        }
    }
}

GameEngine::GameList GameEngine::changeGame(bool isToggled, unsigned long btnPressedTime, unsigned int changeTime, bool inSeconds){
  
  static short s_gameIndex {0};
  changeTime = inSeconds ? changeTime * 1000 : changeTime;

  if(isToggled && btnPressedTime > changeTime){
    s_gameIndex++;
    s_gameIndex %= m_gamesLoaded;
    GameList gameSel = m_gameList[s_gameIndex];

    switch(gameSel){

      case(GameList::E_SNAKE):
            return GameList::E_SNAKE;
            break;

      case(GameList::E_INVADERS):
            return GameList::E_INVADERS;
            break;

       case(GameList::E_NO_SWITCH):
            return GameList::E_NO_SWITCH;
            break;
    }
  }
  return GameList::E_NO_SWITCH;
}


Vec2 GameEngine::computePlayerPos(unsigned int dT, Movement iMovement, Vec2 Player, int inputX, int inputY, int scalar, bool oneAxis){

    m_dirX = sgn(static_cast<int>(inputX));
    m_dirY = sgn(static_cast<int>(inputY));

    switch(iMovement){
    
        case(Movement::E_SIMPLE):

        if(oneAxis){
            Player.x += abs(inputX) > abs(inputY) ? sgn(static_cast<int>(inputX)) : 0;
            Player.y += abs(inputX) < abs(inputY) ? sgn(static_cast<int>(inputY)) : 0;
        }

        else {  
            Player.x += m_dirX;
            Player.y += m_dirY;
        }
        
        break;


        case(Movement::E_COMPLEX):

            Player.x += m_dirX * inputX * scalar * (dT / 1000.0);
            Player.y += m_dirY * inputY * scalar * (dT / 1000.0);
            break;

    }
    return Player;
}


unsigned long GameEngine::computeRNGTimer(unsigned int iMin, unsigned int iMax, bool faster, unsigned int rapidIterate, float bareMin){

    if(!iMin || !iMax){
        Serial.print("ERROR: Did not specify iMin and iMax when calling computeRNGTimer"); Serial.print('\n');
        return _ERR_MAX;
    }

    if(faster){
       rapidIterate = clip(rapidIterate, 5u, 1u);
    }

    unsigned long t1 = random(iMin, iMax);
    static float s_tFast {0.0f};
    s_tFast += (s_tFast + rapidIterate) * 0.01;

    if(faster){
       s_tFast = s_tFast > 1.0f ? 0.0 : s_tFast;
    }

    if(s_tFast < bareMin)
        return t1;
    else
        return min(t1 * s_tFast, t1);
   
}


void snakeMap(){

    unsigned char snakeMap[32] {};
    int x[5] {};
    int y[5] {};
    int snLen = 5;

    for(int i = 0; i < snLen; ++i){
        snakeMap[x[i]] |= 1 << y[i]; 
    }

}

Vec2 GameEngine::spawnEntity(Vec2 RangeMin, Vec2 RangeMax, bool complex, unsigned char *takenMap){

    unsigned char check[32] {};

    if(complex && takenMap){
        m_Entity.x = random(RangeMin.x, RangeMax.x);
        m_Entity.y = random(RangeMin.y, RangeMax.y);

        while(true){
            for(int i = 0; i < 8; ++i){
                unsigned char map = *(takenMap + m_Entity.x);

                if(map == B11111111){
                  m_Entity.x = random(RangeMin.x, RangeMax.x);
                 continue;
                }

                else if(map){
                    check[i] = map & (1 << i);

                    if(m_Entity.y == i && !check[i])
                        return m_Entity;

                     m_Entity.y = random(i, RangeMax.y);
                }
                else
                    return m_Entity;
            }  
        }           
    }
    
    else{
        m_Entity.x = random(RangeMin.x, RangeMax.x);
        m_Entity.y = random(RangeMin.y, RangeMax.y);  
        return m_Entity; 
    }
 //   return m_Entity;
}

//unsigned long cbool timerRNG, unsigned int timerMin = 0, unsigned int timerMax = 0, bool timerFaster = false, unsigned int timerSlowDown = 0


bool GameEngine::detectCollision(Vec2 Entity1, Vec2 Entity2){

    return (Entity1.x == Entity2.x) && (Entity1.y == Entity2.y);
}

bool GameEngine::isEntityDeleted(Vec2 Entity) {

   return (Entity.x > _SCR_W || Entity.y > _SCR_H || Entity.x < 0 || Entity.x < 0);
}


Vec2 GameEngine::wrapAround(Vec2 Entity){

    // Wrap Around if greather than screen width or height
    Entity.x = (Entity.x >= 32) ? 0 : Entity.x;
    Entity.x = (Entity.x < 0) ? 32-1 : Entity.x;

    // Wrap Around if less than screen width or height
    Entity.y = (Entity.y >= 8) ? 0 : Entity.y;
    Entity.y = (Entity.y < 0) ? 8-1 : Entity.y;

    return Entity;
}


void GameEngine::gameOver(OS &Os){

    Os.Scr.clear();
    Os.Scr.clear2();
    
    Os.Buzz.buzzer(300, 1000, 1000);
    Os.Buzz.buzzer(100, 750, 750);
    Os.Buzz.buzzer(25, 500, 500);

    // Game Over Animation
    for(int row{0}; row < _SCR_W; ++row)
        for(int column{0}; column < _SCR_H; ++column)
              Os.Scr.setLED2(row,column,true);
          

    delay(1000);

    for(int row{0}; row < _SCR_W; ++row)
       for(int column{0}; column < _SCR_H; ++column)
              Os.Scr.setLED2(row, column, false);
          

    delay(1000);

        for(int device{0}; device < _NUM_OF_LED; ++device){
            switch(device){
                case(0):
                    Os.Scr.draw2(device, E);
                 break;

                 case(1):
                    Os.Scr.draw2(device, M);
                 break;

                 case(2):
                    Os.Scr.draw2(device, A);
                 break;

                 case(3):
                    Os.Scr.draw2(device, G);
                 break;
            }
        }
    
    delay(3500);
    Os.Scr.clear2();

    for(int device{0}; device < _NUM_OF_LED; ++device){
            switch(device){
                case(0):
                    Os.Scr.draw2(device, R);
                 break;

                 case(1):
                    Os.Scr.draw2(device, E);
                 break;

                 case(2):
                    Os.Scr.draw2(device, V);
                 break;

                 case(3):
                    Os.Scr.draw2(device, O);
                 break;
            }
        }

    delay(3500);
    Os.Scr.clear2();

       for(int device{0}; device < _NUM_OF_LED; ++device){
            switch(device){
                case(0):
                    Os.Scr.draw2(device, X);
                 break;

                 case(1):
                    Os.Scr.draw2(device, T);
                 break;

                 case(2):
                    Os.Scr.draw2(device, A);
                 break;

                 case(3):
                    Os.Scr.draw2(device, M);
                 break;
            }
        }

    delay(3500);
    Os.Scr.clear2();
}
