#include "game.h"



void GameEngine::runGame(OS::Games currentGame){

    if(currentGame == OS::Games::E_ERR){
        // just update
        int i = 0;
    }
    else{
        if(currentGame != m_oldGame){
        //  delete this;

            switch(currentGame){
                case(OS::Games::E_SNAKE):
                    //this = Snake();
                    m_oldGame = Games::E_SNAKE; 
                    break;

                case(OS::Games::E_INVADERS):
                    // this = Invaders();
                    m_oldGame = Games::E_INVADERS;
                    break;
            }
            // update game
        }
    }
}



Vec2 GameEngine::computePlayerPos(Movement iMovement, Vec2 Player, int inputX, int inputY, int scalar, bool oneAxis){

    m_dirX = sgn(inputX);
    m_dirY = sgn(inputY);

    switch(iMovement){
    
        case(Movement::E_SIMPLE):

        if(oneAxis){
            Player.x += abs(inputX) > abs(inputY) ? sgn(m_dirX) : 0;
            Player.y += abs(inputX) < abs(inputY) ? sgn(m_dirY) : 0;
        }

        else {  
            Player.x += m_dirX;
            Player.y += m_dirY;
        }
        
        break;


        case(Movement::E_COMPLEX):

            Player.x += m_dirX * inputX * scalar * (getFrame_dT() / 1000.0);
            Player.y += m_dirY * inputY * scalar * (getFrame_dT() / 1000.0);
            break;

    }
    return Player;
}


unsigned long GameEngine::computeRNGTimer(unsigned int iMin, unsigned int iMax, bool faster, unsigned int slowDown){
    if(!iMin || !iMax){
        Serial.print("ERROR: Did not specify iMin and iMax when calling computeRNGTimer"); Serial.print('\n');
        return ERR;
    }

    if(faster){
       slowDown = clip(slowDown, 5u, 1u);
    }

    unsigned long t1 = random(iMin, iMax);
    static float tFast {0.0f};
    tFast = (tFast + slowDown) * 0.01;

    if(faster){
       tFast = clip(tFast, 1.0f, 0.25f);
    }

    if(tFast < 0.26)
        return t1;
    else
        return min(t1 * tFast, t1);
   
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

Vec2 GameEngine::spawnEntity(Vec2 RangeMin, Vec2 RangeMax, bool complex, unsigned char *takenMap){ // byte array
     unsigned char check[8] {};

    if(complex && takenMap){
        m_Entity.x = random(RangeMin.x, RangeMax.x);
        m_Entity.y = random(RangeMin.y, RangeMax.y);

        for(int i = 0; i < 8; ++i){

            if(*(takenMap + m_Entity.x) == B11111111){
                m_Entity.x = random(RangeMin.x, RangeMax.x);
                continue;
            }
            else if(*(takenMap + m_Entity.x)){
                check[i] = *(takenMap + m_Entity.x) & (1 << i);

                    if(m_Entity.y && !check[i])
                        return m_Entity;

                m_Entity.y = random(RangeMin.y, RangeMax.y);
            }
            else
                return m_Entity;
        }   
        
    }

    else{
        m_Entity.x = random(RangeMin.x, RangeMax.x);
        m_Entity.y = random(RangeMin.y, RangeMax.y);   
      //  scrSetLED(m_Entity.x, m_Entity.y, true);
    }
    return m_Entity;
}

//unsigned long cbool timerRNG, unsigned int timerMin = 0, unsigned int timerMax = 0, bool timerFaster = false, unsigned int timerSlowDown = 0


bool GameEngine::detectCollision(Vec2 Entity1, Vec2 Entity2){

    return Entity1.x == Entity2.x && Entity1.y == Entity2.y;
}

bool GameEngine::isEntityDeleted(Vec2 Entity) {

   return (Entity.x> SCR_W || Entity.y > SCR_H || Entity.x < 0 || Entity.x < 0);
}


Vec2 GameEngine::wrapAround(Vec2 Entity){

    // Wrap Around if greather than screen width or height
    Entity.x = Entity.x > SCR_W-1 ? 0 : Entity.x;
    Entity.y = Entity.y > SCR_H-1 ? 0 : Entity.y;

    // Wrap Around if less than screen width or height
    Entity.x = Entity.x < 0 ? SCR_W - 1 : Entity.x;
    Entity.y = Entity.y < 0 ? SCR_H - 1 : Entity.y;

    return Entity;
}


void GameEngine::gameOver(){

    buzzer(300, 1000, 1000);
    buzzer(100, 750, 750);
    buzzer(25, 500, 500);

    // Game Over Animation
    for(int row{0}; row < SCR_W; ++row)
        for(int column{0}; column < SCR_H; ++column)
            scrSetLED(row, column, true);

    scrDraw();

    for(int row{7}; row >= 0; --row)
        for(int column{31}; column >= 0; --column)
            scrSetLED(row, column, false);

    scrDraw();

        for(int device{0}; device < NUM_OF_LED; ++device){
            switch(device){
                case(0):
                 scrDraw2(device, G);
                 break;

                 case(1):
                 scrDraw2(device, A);
                 break;

                 case(2):
                 scrDraw2(device, M);
                 break;

                 case(3):
                 scrDraw2(device, E);
                 break;
            }
        }
/*
    for(int device{0}; device < NUM_OF_LED; ++device){
        for(int row{0}; row < SCR_W; ++row){
            switch(device){
                case(0):
                 LedMatrix.setRow(device, row, G[row]);
                 break;

                 case(1):
                 LedMatrix.setRow(device, row, A[row]);
                 break;

                 case(2):
                 LedMatrix.setRow(device, row, M[row]);
                 break;

                 case(3):
                 LedMatrix.setRow(device, row, E[row]);
                 break;
            }
        }
    }
    */
    
    delay(1000);
    scrClear2();

    for(int device{0}; device < NUM_OF_LED; ++device){
            switch(device){
                case(0):
                 scrDraw2(device, O);
                 break;

                 case(1):
                 scrDraw2(device, V);
                 break;

                 case(2):
                 scrDraw2(device, E);
                 break;

                 case(3):
                 scrDraw2(device, R);
                 break;
            }
        }

    delay(1000);
    scrClear2();

}
