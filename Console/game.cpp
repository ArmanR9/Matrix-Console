#include "game.h"
int xPos = 0;
int yPos = 0;

void updatePosition(OS& OSInstance){
    if(OSInstance.getJoyX() > 50)
        xPos++;
        //yeet
    else if(OSInstance.getJoyX() < 50)    
        xPos--;

    if(OSInstance.getJoyY() > 50)
        yPos++;
    else if(OSInstance.getJoyY() < 50)
        yPos--;

    yPos = min(yPos, 0);
    yPos = max(yPos, 7);
    xPos = min(xPos, 0);
    xPos = max(xPos, 31);

    OSInstance.scrSetLED(xPos, yPos, true);
}