#include "LedControl.h"
#include "OS.h"


// Intialize Global Objects
// Default Ctor
OS MatrixOS;


// Intialize function

void setup() {
  
  Serial.begin(9600);
  randomSeed(1);

  MatrixOS.scrInit();
  MatrixOS.scrBrightness(1);
 // GameOS.scrBootUpAnim();  // Enable/Disable Screen Boot Up Animation
  MatrixOS.setTimeOld(millis());
  
}


// Main looping function

void loop() {
   
  MatrixOS.update();
  
}
