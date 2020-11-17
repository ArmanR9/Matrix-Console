#include "LedControl.h"
#include "OS.h"
#include "game.h"
#include "snake2.h"

// Intialize Global Objects
OS MatrixOS; 
GameEngine* MatrixGEng = new SnakeGame();

// Intialize function

void setup() {
  
  Serial.begin(9600);
  randomSeed(analogRead(0));

  MatrixOS.Scr.init();
  MatrixOS.Scr.brightness(1);
  MatrixOS.bootUpAnim(); // Enable/Disable Screen Boot Up Animation
  MatrixOS.init();

}


// Main looping function
  
void loop() {

  MatrixOS.update();
  // Do Game Stuff
  MatrixGEng->update(MatrixOS);
  MatrixOS.update2();

}
