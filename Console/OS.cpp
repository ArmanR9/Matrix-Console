#include "OS.h"
#include "game.h"

// I should probably change this set-up, but all well. It works. ¯\_(ツ)_/¯

unsigned char G[] = {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
unsigned char A[] = {B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
unsigned char M[] = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
unsigned char E[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
unsigned char I[] = {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
unsigned char O[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
unsigned char T[] = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
unsigned char V[] = {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
unsigned char R[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
unsigned char X[] = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};

/* * * * * * * * *
 * 				        
 *  MAIN METHOD   
 * 				        
 * * * * * * * * */

void OS::update(unsigned int dT){

  // Screen Clear, and compute I/O States
  scrClear();
  computeBtnStates(dT);
  customJoyX(127, -127);
  customJoyY(127, -127);
}

void OS::update2(){

  // Screen Draw
  profilingLED();
  scrDraw();
}

//  Run Video Game
  //GameHandler->runGame(changeGame(GameHandler, 2000););
   // Check if game is changed??
//  updatePosition(*this);

 // printJoy(OS::E_VERBOSE);
 // printBtn(OS::E_VERBOSE);


/* * * * * * * *  *
 * 				        
 * SCREEN METHODS 
 * 				        
 * * * * * * * * */

void OS::scrInit(){
  for(int i = 0; i < m_NUM_OF_LED; ++i)
    LedMatrix.shutdown(i, false);
}


void OS::scrBootUpAnim(){

  OS::buzzer(330, 240, 320);
  OS::buzzer(392, 240, 320);
  OS::buzzer(494, 640, 700);

  for(int device{0}; device < NUM_OF_LED; ++device){
    switch(device){

      case(0):
        scrDraw2(device, M);
        break;

      case(1):
        scrDraw2(device, A);
        break;

      case(2):
        scrDraw2(device, T);
        break;

      case(3):
        scrDraw2(device, X);
        break;
      }
  }

    delay(1000);
    scrClear2();
  
  
for(int matrix = 0; matrix < m_NUM_OF_LED; ++matrix){
    OS::buzzer(494, 50);
  for(int column = 0; column < m_scrH; ++column){
    for(int row = 0; row < m_scrW; ++row){
        LedMatrix.setRow(matrix, row, 1);
        LedMatrix.setColumn(matrix, column,1);
    }
  }
}

for(int matrix = 0; matrix < m_NUM_OF_LED; ++matrix){
    OS::buzzer(330, 50);
  for(int column = 0; column < m_scrH; ++column){
    for(int row = 0; row < m_scrW; ++row){
        LedMatrix.setRow(matrix, row, 0);
        LedMatrix.setColumn(matrix, column,0);
      }
    }
  }

  OS::buzzer(494, 240, 320);
  OS::buzzer(392, 240, 320);
  OS::buzzer(330, 640, 700);
}



void OS::scrBootOffAnim(){
  
  OS::buzzer(494, 240, 320);
  OS::buzzer(392, 240, 320);
  OS::buzzer(330, 640, 700);

  for(int screens{0}; screens < m_NUM_OF_LED; ++screens){
    for(int columns{0}; columns < m_scrH; ++columns){
      for(int rows{0}; rows < m_scrW; ++rows){
          bool on = (rows+columns) % 4 == screens;
          LedMatrix.setLed(screens, rows, columns, on);
      }
    } 
  }

    for(int screens{0}; screens < m_NUM_OF_LED; ++screens){
      for(int columns{0}; columns < m_scrH; ++columns){
        for(int rows{0}; rows < m_scrW; ++rows){
            bool on = (rows+columns) % 4 == screens;
            LedMatrix.setLed(screens, rows, columns, !on);
      }
    } 
  }

  for(int device{0}; device < NUM_OF_LED; ++device){
    switch(device){

      case(0):
        scrDraw2(device, M);
        break;

      case(1):
        scrDraw2(device, A);
        break;

      case(2):
        scrDraw2(device, T);
        break;

      case(3):
        scrDraw2(device, X);
        break;
      }
  }

    delay(1000);
    scrClear2();

   for(int addr {0}; addr < m_NUM_OF_LED; ++addr){
        LedMatrix.shutdown(addr, true);
    }
}



void OS::scrReboot(){

  for(int addr {0}; addr < m_NUM_OF_LED; ++addr)
    LedMatrix.shutdown(addr, false);
}



void OS::scrBrightness(int level){
  if(level > 16)
    level = 16;
  else if(level < 0)
    level = 0;
        
  for(int addr {0}; addr < m_NUM_OF_LED; ++addr)
    LedMatrix.setIntensity(addr, level);
}



void OS::scrClear(){

  for(int row {0}; row < 8; ++row){
    m_pixelsA[row] = 0;
    m_pixelsB[row] = 0;
    m_pixelsC[row] = 0;
    m_pixelsD[row] = 0;
  }
}



void OS::scrClear2(){

    for(int addr {0}; addr < m_NUM_OF_LED; ++addr){
        LedMatrix.clearDisplay(addr);
    }

}



#define OUT_OF_RANGE iX > 31 || iX < 0 || iY > 7 || iY < 0 

void OS::scrSetLED(int iX, int iY, bool state){

  if(OUT_OF_RANGE)
    return;

  switch(state){
  
    case(true):
    if(iX > 23)
      m_pixelsA[abs(iY-7)] |=  1 << abs(iX - 24 - 7);
  
    else if(iX > 15)
      m_pixelsB[abs(iY-7)] |= 1 << abs(iX - 16 - 7);

    else if(iX > 7)
      m_pixelsC[abs(iY-7)] |= 1 << abs(iX - 8 - 7);

    else
      m_pixelsD[abs(iY-7)] |= 1 << abs(iX - 7);
  
    break;

    default:
    if(iX > 23)
      m_pixelsA[abs(iY-7)] &= ~(1 << abs(iX - 24 - 7));
  
    else if(iX > 15)
      m_pixelsB[abs(iY-7)] &= ~(1 << abs(iX - 16 - 7));

    else if(iX > 7)
      m_pixelsC[abs(iY-7)] &= ~(1 << abs(iX - 8 - 7));

    else
      m_pixelsD[abs(iY-7)] &= ~(1 << abs(iX - 7));
    
    break;
  }
}


void OS::scrSetLED2(int iX, int iY, bool state){

  if(OUT_OF_RANGE)
    return;

  if(iX > 23)
    LedMatrix.setLed(0, abs(iX-24-7), abs(iY-7), state);
  
  else if(iX > 15)
    LedMatrix.setLed(1, abs(iX-16-7), abs(iY-7), state);

  else if(iX > 7)
    LedMatrix.setLed(2, abs(iX-8-7), abs(iY-7), state);

  else
    LedMatrix.setLed(3, abs(iX-7), abs(iY-7), state);
}



void OS::scrDraw(){

  for(int row {0}; row < 8; ++row){
      LedMatrix.setRow(0, row, m_pixelsA[row]);
      LedMatrix.setRow(1, row, m_pixelsB[row]);
      LedMatrix.setRow(2, row, m_pixelsC[row]);
      LedMatrix.setRow(3, row, m_pixelsD[row]);
  }
}


void OS::scrDraw2(int device, unsigned char* array){

  for(int row {0}; row < 8; ++row)
    LedMatrix.setRow(device, row, *(array+row));
}



/* * * * * * * *  *
 * 				        
 * PERIPHERAL I/O 
 * 				        
 * * * * * * * *  */



// Remap Joystick X method
// max is maximum value of joystick (1023)
// scalar is value you want to scale the joystick input to output to
// Deadband in case joystick is drifiting
// Maps joystick to custom set of values

int OS::customJoyX(float max, float min, int threshold){

  m_joyX = -((analogRead(m_joyXPin) / 1024.0) * (max*2) + min);

    if(abs(m_joyX) < threshold) // Deadband
       m_joyX = 0;

  return m_joyX;
}

// Remap Joystick Y method
// max is maximum value of joystick (1023)
// scalar is value you want to scale the joystick input to output to
// Deadband in case joystick is drifiting
// Maps joystick to custom set of values

int OS::customJoyY(float max, float min, int threshold){

  m_joyY = -((analogRead(m_joyYPin) / 1024.0) * (max*2) + min);

    if(abs(m_joyY) < threshold) // Deadband
      m_joyY = 0;

  return m_joyY;
}


// Button logic method
// btnOld is old button state 
// dT is deltaTime from last CPU cycle
// Checks whether a button is pressed
// Checks if button is toggled
// Checks if button is double tapped
// Checks how long button is held for

bool isToggled = false;

void OS::computeBtnStates(int dT){
  
  bool btnOld = m_btnIsPressed;
  m_btnIsPressed = digitalRead(m_btnPin);
  bool btnPressedThisCycle = m_btnIsPressed && (m_btnIsPressed != btnOld);

  if(!isToggled && btnPressedThisCycle){
      m_btnIsToggled = 1 - m_btnIsToggled;
      isToggled = !isToggled;
  }
  else{
    isToggled = 0;
  }


  if(btnPressedThisCycle && m_dblTimer > 500){
    m_btnIsPressedTime = 0;
    m_dblTimer = 0;
  }
  else if(btnPressedThisCycle && m_dblTimer < 500){
    m_btnIsPressedTime = 0;
    m_btnIsDoubleTapped = !m_btnIsDoubleTapped; // Set whether the btn has been double tapped or not
  }
  else{
    m_dblTimer += dT;
  }


  if(m_btnIsPressed){
    m_btnIsPressedTime += dT;
  }
}


// Buzzer Method
// Set frequency of sound
// Set duration of sound
// Set delay if want to halt code execution (by default 0)


void OS::buzzer(short freq, unsigned short time, unsigned int iDelay){
  tone(m_buzzPin, freq, time);
  delay(iDelay);
}


/* * * * * * * * * *
 * 				         
 *    DEBUGGING    
 * 				         
 * * * * * * * * * */


 // Debug Methods
 // Prints to Serial terminal

void OS::printJoy(DebugLevel debuglvl){

  switch(debuglvl){

    case(DebugLevel::E_VERBOSE):

      Serial.print("joyX: "); Serial.print(m_joyX);
      Serial.print(" joyY: "); Serial.print(m_joyY);
      Serial.print("\n");

      Serial.print("rawX: "); Serial.print(analogRead(m_joyXPin));
      Serial.print(" rawY: "); Serial.print(analogRead(m_joyYPin));
      Serial.print(" rawZ: "); Serial.print(analogRead(m_joyZPin));

      Serial.print("\n");
      break;

    case(DebugLevel::E_NORMAL):

      Serial.print("joyX: "); Serial.print(m_joyX);
      Serial.print(" joyY: "); Serial.print(m_joyY);
      Serial.print("\n");
      break;
  }
}

void OS::printBtn(DebugLevel debuglvl){

  switch(debuglvl){

    case(DebugLevel::E_VERBOSE):
      Serial.print("btnRaw: "); Serial.print(m_btnIsPressed);
      Serial.print(" btnToggle: "); Serial.print(m_btnIsToggled);
      Serial.print(" btnDblTap: "); Serial.print(m_btnIsDoubleTapped);
      Serial.print(" btnDblTime: "); Serial.print(m_dblTimer);
      Serial.print(" btnTime: "); Serial.print(m_btnIsPressedTime);

      Serial.print("\n");
      break;

    case(DebugLevel::E_NORMAL):
      Serial.print("btnRaw: "); Serial.print(m_btnIsPressed);
      Serial.print(" btnToggle: "); Serial.print(m_btnIsToggled);
      Serial.print(" btnDblTap: "); Serial.print(m_btnIsDoubleTapped);

      Serial.print("\n");
      break;
  }
}

void OS::printBuzz(DebugLevel debuglvl){

  switch(debuglvl){
  
    case(DebugLevel::E_VERBOSE):
      Serial.print("Buzz: "); Serial.print(digitalRead(m_buzzPin));
      Serial.print(" PIN: "); Serial.print(m_buzzPin);

      Serial.print("\n");
      break;

    case(DebugLevel::E_NORMAL):
      Serial.print("Buzz: "); Serial.print(digitalRead(m_buzzPin));
    
      Serial.print("\n");
      break;
  }
}

void OS::printLEDMatrix(DebugLevel debuglvl){

  switch(debuglvl){
    
    case(DebugLevel::E_VERBOSE): 

      Serial.print("DIN Data: "); Serial.print(digitalRead(m_dinPin));
      Serial.print("  CS DATA: "); Serial.print(digitalRead(m_csPin));
      Serial.print("  CLK DATA: "); Serial.print(digitalRead(m_clkPin));
    
      Serial.print("\n");

      Serial.print("DIN PIN: "); Serial.print(m_dinPin);
      Serial.print(" CS Pin: "); Serial.print(m_csPin);
      Serial.print(" CLK Pin: "); Serial.print(m_clkPin);
    
      Serial.print("\n");
      break;

    case(DebugLevel::E_NORMAL):

      Serial.print("DIN PIN: "); Serial.print(m_dinPin);
      Serial.print(" CS Pin: "); Serial.print(m_csPin);
      Serial.print(" CLK Pin: "); Serial.print(m_clkPin);
    
      Serial.print("\n");
      break;
  }
}



void OS::profilingLED(){

  // Bit Wise:

  unsigned long start = millis();
  
  int x = random(0, 31);
  int y = random(0, 7);
  scrSetLED(x,y,true);
  int x2 = random(0, 31);
  int y2 = random(0, 7);
  scrSetLED(x2,y2,false);

  scrDraw();

  unsigned long end = millis();
  unsigned long dT = end - start;

  Serial.print("Using Bit Manipulation (Execution Time): "); Serial.print(dT); Serial.print('\n');

  // Non Bit-Wise:

  unsigned long start2 = millis();

  int x3 = random(0, 31);
  int y3 = random(0, 7);
  scrSetLED2(x3,y3,true);
  int x4 = random(0, 31);
  int y4 = random(0, 7);
  scrSetLED2(x4,y4,false);

  unsigned long end2 = millis();
  unsigned long dT2 = end2 - start2;

  Serial.print("Not Bit Manipulation (Execution Time): "); Serial.print(dT2); Serial.print('\n');
  
}


OS::Games OS::changeGame(unsigned int changeTime, bool inSeconds){
  
  static short gameIndex {0};
  changeTime = inSeconds ? changeTime * 1000 : changeTime;

  if(m_btnIsToggled && m_btnIsPressedTime > changeTime){
    gameIndex++;
    gameIndex % m_gamesLoaded;
    OS::Games gameSel = m_gameList[gameIndex];
   // delete Game;

    switch(gameSel){

      case(Games::E_SNAKE):
        // Game = new SnakeGame(); 
        return Games::E_SNAKE;
        break;

      case(Games::E_INVADERS):
        // Game = new InvadersGame();
        return Games::E_INVADERS;
        break;

       case(Games::E_ERR):
        return Games::E_ERR;
        break;
    }
  }
  return Games::E_ERR;
}
