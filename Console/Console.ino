#include "LedControl.h"
#include "OS.h"
#include "game.h"

// Intialize Global Objects
OS MatrixOS; 
GameEngine *testEngine = new GameEngine;


// Intialize function

void setup() {
  
  Serial.begin(9600);
  randomSeed(analogRead(0));

  MatrixOS.scrInit();
  MatrixOS.scrBrightness(1);
 // MatrixOS.scrBootUpAnim(); // Enable/Disable Screen Boot Up Animation
  MatrixOS.init();
  Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
  Serial.print('\n');
  Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
   Serial.print('\n');
  Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
   Serial.print('\n');
  Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
   Serial.print('\n');
  Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
   Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
  Serial.print('\n');
  Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
   Serial.print('\n');
  Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
   Serial.print('\n');
  Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
   Serial.print('\n');
  Serial.println(testEngine->computeRNGTimer(2000, 2001, true, 5));
  
  delay(100000);
}


// Main looping function

void loop() {

  MatrixOS.updateOS();
  // Do Game Stuff
  MatrixOS.updateOS2();

  // Debug

  /*
  MatrixOS.printBtn(OS::DebugLevel::E_VERBOSE);
  delay(1000);
  MatrixOS.printJoy(OS::DebugLevel::E_VERBOSE);
  */
}
