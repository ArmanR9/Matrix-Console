#include "game.h"


void GameEngine::computePlayerPos(Movement iMovement, int& posX, int& posY, int inputX = m_joyX, int inputY = m_joyY, int scalar = 1, bool oneAxis = false){

    m_dirX = sgn(inputX);
    m_dirY = sgn(inputY);

    switch(iMovement){
    
    case(Movement::E_SIMPLE):

        if(oneAxis){
          posX += abs(inputX) > abs(inputY) ? sgn(dirX) : 0;
          posY += abs(inputX) < abs(inputY) ? sgn(dirY) : 0;
        }

        else {  
        posX += m_dirX;
        posY += m_dirY;
        }
        
    break;


    case(Movement::E_COMPLEX):

        posX += m_dirX * inputX * scalar * (getFrame_dT() / 1000.0);
        posY += m_dirY * inputY * scalar * (getFrame_dT() / 1000.0);
        break;

    }
}

void GameEngine::spawnEntity(){


}


bool GameEngine::detectCollision(int posX, int posY, int posX2, int posY2){

    return posX + posY == posX2 + posY2;
}

bool GameEngine::isEntityDeleted(int entityX, int entityY) {

   return entityX > SCR_W || entityY > SCR_H || entityX < 0 || entityY < 0)
}


void GameEngine::wrapAround(int& posX, int& posY){

    // Wrap Around if greather than screen width or height
    posX = posX > SCR_W-1 ? 0 : posX;
    posY = posY > SCR_H-1 ? 0 : posY;

    // Wrap Around if less than screen width or height
    posX = posX < 0 ? SCR_W - 1 : posX;
    posY = posY < 0 ? SCR_H - 1 : posY;
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

}






