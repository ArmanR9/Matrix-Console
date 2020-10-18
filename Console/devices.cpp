#include "devices.h"

/* * * * * * * * *
 * 				        
 *  SCREEN CLASS 
 * 				        
 * * * * * * * * */


void Screen::init(){
  for(int i = 0; i < m_NUM_OF_LED; ++i)
    LedMatrix.shutdown(i, false);
}


void Screen::reboot(){

  for(int addr {0}; addr < m_NUM_OF_LED; ++addr)
    LedMatrix.shutdown(addr, false);
}



void Screen::brightness(int level){
  if(level > 16)
    level = 16;
  else if(level < 0)
    level = 0;
        
  for(int addr {0}; addr < m_NUM_OF_LED; ++addr)
    LedMatrix.setIntensity(addr, level);
}



void Screen::clear(){

  for(int row {0}; row < 8; ++row){
    m_pixelsA[row] = 0;
    m_pixelsB[row] = 0;
    m_pixelsC[row] = 0;
    m_pixelsD[row] = 0;
  }
}

void Screen::clear2(){

    for(int addr {0}; addr < m_NUM_OF_LED; ++addr){
        LedMatrix.clearDisplay(addr);
    }

}

/* * * * * * * * *
 * 				        
 *  MAIN METHOD FOR 
 *  MAPPING COORDS 
 *  TO PIXELS
 *   				        
 * * * * * * * * */

#define OUT_OF_RANGE iX > 31 || iX < 0 || iY > 7 || iY < 0 

void Screen::setLED(int iX, int iY, bool state){

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

    case(false):
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


void Screen::setLED2(int iX, int iY, bool state){

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

void Screen::setLEDWrapper(int addr, int row, int col, bool state){
  LedMatrix.setLed(addr, row, col, state);
}

void Screen::shutdownWrapper(int addr, bool b){
   LedMatrix.shutdown(addr, b);
}


void Screen::draw(){

  for(int row {0}; row < 8; ++row){
      LedMatrix.setRow(0, row, m_pixelsA[row]);
      LedMatrix.setRow(1, row, m_pixelsB[row]);
      LedMatrix.setRow(2, row, m_pixelsC[row]);
      LedMatrix.setRow(3, row, m_pixelsD[row]);
  }
}


void Screen::draw2(int device, unsigned char* array){

  for(int row {0}; row < 8; ++row)
    LedMatrix.setRow(device, row, array[row]);
}



/* * * * * * * * *
 * 				        
 * JOYSTICK CLASS
 * 				        
 * * * * * * * *  */



// Remap Joystick X method
// max is maximum value of joystick (1023)
// scalar is value you want to scale the joystick input to output to
// Deadband in case joystick is drifiting
// Maps joystick to custom set of values

int Joystick::setJoyX(float max, float min, int threshold){

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

int Joystick::setJoyY(float max, float min, int threshold){

  m_joyY = -((analogRead(m_joyYPin) / 1024.0) * (max*2) + min);

    if(abs(m_joyY) < threshold) // Deadband
      m_joyY = 0;

  return m_joyY;
}


/* * * * * * * * *
 * 				        
 *  BUTTON CLASS
 * 				        
 * * * * * * * * */


// Button logic method
// btnOld is old button state 
// dT is deltaTime from last CPU cycle
// Checks whether a button is pressed
// Checks if button is toggled
// Checks if button is double tapped
// Checks how long button is held for

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int oldReading = 0;

void Button::computeBtnStates(int dT){

  int reading = digitalRead(m_btnPin);

  if(reading != oldReading)
    lastDebounceTime = millis();

  if((millis() - lastDebounceTime) > debounceDelay){
    static bool s_isToggled = false;
    bool btnOld = m_btnIsPressed;
    m_btnIsPressed = reading;
    bool btnPressedThisCycle = m_btnIsPressed && (m_btnIsPressed != btnOld);

    if(!s_isToggled && btnPressedThisCycle){
      m_btnIsToggled = 1 - m_btnIsToggled;
      s_isToggled = !s_isToggled;
    }
    else{
    s_isToggled = 0;
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

else{
    m_btnIsPressed = 0;
  }
  
  oldReading = reading;
}


/* * * * * * * * *
 * 				        
 *  BUZZER CLASS
 * 				        
 * * * * * * * *  */

// Buzzer Method
// Set frequency of sound
// Set duration of sound
// Set delay if want to halt code execution (by default 0)


void Buzzer::buzzer(short freq, unsigned short time, unsigned int iDelay){
  tone(m_buzzPin, freq, time);
  delay(iDelay);
}


/* * * * * * * * * *
 * 				         
 *  DEBUGGING (ALL DEVICES)   
 * 				         
 * * * * * * * * * */


void Joystick::printJoy (DebugLevel debuglvl) const{

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

void Button::printBtn(DebugLevel debuglvl) const{

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

void Buzzer::printBuzz(DebugLevel debuglvl) const{

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

void Screen::printLEDMatrix(DebugLevel debuglvl) const{

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



void Screen::profilingLED(){

  // Bit Wise:
  
  unsigned long start = millis();
  
    int x = 5;
    int y = 5;
    setLED(x,y,true);
    int x2 = random(0, 31);
    int y2 = random(0, 7);
    setLED(x2,y2,false);

    draw();

  unsigned long end = millis();
  unsigned long dT = end - start;
  

  Serial.print("Using Bit Manipulation (Execution Time): "); Serial.print(dT); Serial.print('\n');
  

  // Non Bit-Wise:
  
  unsigned long start2 = millis();

    int x3 = random(0, 31);
    int y3 = random(0, 7);
    setLED2(x3,y3,true);
    int x4 = random(0, 31);
    int y4 = random(0, 7);
    setLED2(x4,y4,false);

  unsigned long end2 = millis();
  unsigned long dT2 = end2 - start2;

  Serial.print("Not Bit Manipulation (Execution Time): "); Serial.print(dT2); Serial.print('\n');
  
}
