#include "OS.h"


/* * * * * * * * *
 * 				        
 *   OS CLASS
 * 				        
 * * * * * * * * */

void OS::init(){
  // Set old frametime to millis for updateOS() to use.
  m_frameOld = millis();
}

void OS::update(){

// Frame Handling pt. 1
  m_frameStart = millis();
  m_frame_dT = m_frameStart - m_frameOld;
  m_frameOld = m_frameStart;

// Screen Clear, and compute I/O States
  Scr.clear();
  Btn.computeBtnStates(m_frame_dT);
  Joy.setJoyX(127, -127);
  Joy.setJoyY(127, -127);
}

void OS::update2(){

// Draw to screen with byate arrays
  Scr.draw();

  // Frame Handling pt. 2
  unsigned long frameDuration {millis() - m_frameStart};

  if(m_fpsTarget > frameDuration)
    delay(m_fpsTarget - frameDuration);
}

/* * * * * * * * *
 * 				        
 *   BOOT ANIMS
 * 				        
 * * * * * * * * */

void OS::bootUpAnim(){

  Buzz.buzzer(330, 240, 320);
  Buzz.buzzer(392, 240, 320);
  Buzz.buzzer(494, 640, 700);

  for(int device{0}; device < _NUM_OF_LED; ++device){
    switch(device){

      case(0):
        Scr.draw2(device, X);
        break;

      case(1):
        Scr.draw2(device, T);
        break;

      case(2):
        Scr.draw2(device, A);
        break;

      case(3):
        Scr.draw2(device, M);
        break;
      }
  }

    delay(2500);
    Scr.clear2();
  
for(int matrix = 0; matrix < _NUM_OF_LED; ++matrix){
    Buzz.buzzer(494, 50, 200);
  for(int column = 0; column < _SCR_H; ++column){
    for(int row = 0; row < _SCR_W; ++row){
        Scr.setLEDWrapper(matrix, row, column, true);
    }
    delay(50);
  }
}

for(int matrix = 0; matrix < _NUM_OF_LED; ++matrix){
    Buzz.buzzer(330, 50, 200);
  for(int column = 0; column < _SCR_H; ++column){
    for(int row = 0; row < _SCR_W; ++row){
        Scr.setLEDWrapper(matrix, row, column, false);
      }
      delay(50);
    }
  }

  Buzz.buzzer(494, 240, 320);
  Buzz.buzzer(392, 240, 320);
  Buzz.buzzer(330, 640, 700);
}



void OS::bootOffAnim(){
  
  Buzz.buzzer(494, 240, 320);
  Buzz.buzzer(392, 240, 320);
  Buzz.buzzer(330, 640, 700);

  for(int screens{0}; screens < _NUM_OF_LED; ++screens){
    for(int columns{0}; columns < _SCR_H; ++columns){
      for(int rows{0}; rows < _SCR_W; ++rows){
          bool on = (rows+columns) % 4 == screens;
          Scr.setLEDWrapper(screens, rows, columns, on);
      }
    } 
  }

    for(int screens{0}; screens < _NUM_OF_LED; ++screens){
      for(int columns{0}; columns < _SCR_H; ++columns){
        for(int rows{0}; rows < _SCR_W; ++rows){
            bool on = (rows+columns) % 4 == screens;
            Scr.setLEDWrapper(screens, rows, columns, !on);
      }
    } 
  }

  for(int device{0}; device < _NUM_OF_LED; ++device){
    switch(device){

      case(0):
        Scr.draw2(device, M);
        break;

      case(1):
        Scr.draw2(device, A);
        break;

      case(2):
        Scr.draw2(device, T);
        break;

      case(3):
        Scr.draw2(device, X);
        break;
      }
  }

    delay(1000);
    Scr.clear2();

   for(int addr {0}; addr < _NUM_OF_LED; ++addr){
        Scr.shutdownWrapper(addr, true);
    }
}

/* * * * * * * * * *
 * 				         
 *  DEBUGGING (FRAME HANDLING) 
 * 				         
 * * * * * * * * * */


 void OS::printFrameData (DebugLevel debuglvl) const{

   switch(debuglvl){

    case(DebugLevel::E_VERBOSE):

      Serial.print("FPS Target: "); Serial.print(m_fpsMax);
      Serial.print(" Current FPS: "); Serial.print(1000 / m_fpsTarget);
      Serial.print(" Current FPS (ms): "); Serial.print(m_fpsTarget);

      Serial.print("\n");

      Serial.print("Frame Start (ms): "); Serial.print(m_frameStart);
      Serial.print(" Frame DT (ms): "); Serial.print(m_frame_dT);
      Serial.print(" Frame Old (ms): "); Serial.print(m_frameOld);
      Serial.print(" Frame Old (ms): "); Serial.print(m_frameOld);


      Serial.print("\n");
      break;

    case(DebugLevel::E_NORMAL):

      Serial.print("FPS Target: "); Serial.print(m_fpsMax);
      Serial.print(" Current FPS: "); Serial.print(1000 / m_fpsTarget);
      Serial.print("\n");
      break;
  }
 }
