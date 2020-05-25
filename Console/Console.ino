#include "LedControl.h"
#include "OS.h"
#include "game.h"


// Intialize Global Objects
// Default Ctor
OS MatrixOS;
GameEngine testEngine;


// Intialize function

void setup() {
  
  Serial.begin(9600);
  randomSeed(analogRead(0));

  MatrixOS.scrInit();
  MatrixOS.scrBrightness(1);
 // GameOS.scrBootUpAnim();  // Enable/Disable Screen Boot Up Animation
  MatrixOS.setTimeOld(millis());
  
}


// Main looping function

void loop() {

   // Frame Handling
  unsigned long frameStart { millis() };
  unsigned long dT {frameStart - MatrixOS.getTimeOld()};
  MatrixOS.setTimeOld(frameStart);
  MatrixOS.setFrame_dT(dT);
   
  MatrixOS.update(MatrixOS.getFrame_dT());
  //GameHandler->runGame(MatrixOS.changeGame(GameHandler, 2000);
  MatrixOS.update2();
  
  // Frame Handling pt2:
  unsigned long int frameDuration {millis() - frameStart};

  if(MatrixOS.getFPSTarget() > frameDuration)
    delay(MatrixOS.getFPSTarget() - frameDuration);
}
