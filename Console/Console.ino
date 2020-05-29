#include "LedControl.h"
#include "OS.h"
#include "game.h"

// Intialize Global Objects
OS MatrixOS; 
GameEngine *MatrixGEng = new GameEngine(2);


// Intialize function

void setup() {
  
  Serial.begin(9600);
  randomSeed(analogRead(0));

  MatrixOS.Scr.init();
  MatrixOS.Scr.brightness(1);
 // MatrixOS.scrBootUpAnim(); // Enable/Disable Screen Boot Up Animation
  MatrixOS.init();
 // MatrixGEng->compute
  
  
  delay(100000);
}


// Main looping function
  
void loop() {

  MatrixOS.update();
  // Do Game Stuff
  MatrixOS.update2();

  // Debug

  /*
  MatrixOS.printBtn(OS::DebugLevel::E_VERBOSE);
  delay(1000);
  MatrixOS.printJoy(OS::DebugLevel::E_VERBOSE);
  */
}
