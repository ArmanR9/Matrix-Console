#include "game.h"


void GameEngine::computePlayerPos(Movement iMovement, int& posX, int& posY, int inputX, int inputY, int scalar, bool oneAxis){

    m_dirX = sgn(inputX);
    m_dirY = sgn(inputY);

    switch(iMovement){
    
        case(Movement::E_SIMPLE):

        if(oneAxis){
            posX += abs(inputX) > abs(inputY) ? sgn(m_dirX) : 0;
            posY += abs(inputX) < abs(inputY) ? sgn(m_dirY) : 0;
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

   return (entityX > SCR_W || entityY > SCR_H || entityX < 0 || entityY < 0);
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
