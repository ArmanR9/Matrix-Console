#include "LedControl.h"
#include "OS.h"


// Intialize Global Objects
// Default Ctor
OS GameOS;


// Intialize function

void setup() {
  
  Serial.begin(9600);
  randomSeed(1);

  GameOS.scrInit();
  GameOS.scrBrightness(1);
 // GameOS.scrBootUpAnim();  // Enable/Disable Screen Boot Up Animation
  GameOS.setTimeOld(millis());
  
}


// Main looping function

void loop() {
   
   GameOS.update();
  
}
