#pragma once
#include "LedControl.h"
#include "Arduino.h"

// ERROR CODES
#define _ERR_MAX 4294967295;

//SIZES
inline constexpr unsigned short _BYTE {8};

// DEVICE CONSTANTS
inline constexpr unsigned short _SCR_W {32};
inline constexpr unsigned short _SCR_H {8};
inline constexpr unsigned short _DIN_PIN {9};
inline constexpr unsigned short _CS_PIN {8};
inline constexpr unsigned short _CLK_PIN {10};
inline constexpr unsigned short _NUM_OF_LED {4};
inline constexpr unsigned short _BTN_PIN {4};
inline constexpr unsigned short _LDR_PIN {0};
inline constexpr unsigned short _BUZZ_PIN {2};
inline constexpr unsigned short _JOYX_PIN {3};
inline constexpr unsigned short _JOYY_PIN {5};
inline constexpr unsigned short _JOYZ_PIN {1};
inline constexpr unsigned short _GAME_COUNT {2};


// Global Byte Arrays for letters on matrices.
// I should probably change this set-up, but all well. It works. ¯\_(ツ)_/¯

inline constexpr unsigned char A[_BYTE] {B00000000,B00111100,B00100100,B00100100,B00111100,B00100100,B00100100,B00000000};
inline constexpr unsigned char E[_BYTE] {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
inline constexpr unsigned char G[_BYTE] {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
inline constexpr unsigned char I[_BYTE] {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
inline constexpr unsigned char M[_BYTE] {B00000000,B01000100,B10101010,B10010010,B10010010,B10000010,B10000010,B00000000};
inline constexpr unsigned char O[_BYTE] {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
inline constexpr unsigned char R[_BYTE] {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
inline constexpr unsigned char T[_BYTE] {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
inline constexpr unsigned char V[_BYTE] {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
inline constexpr unsigned char X[_BYTE] {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};


class OS {
public:

	enum class GameToSwitch{
		E_SNAKE = 0,
		E_INVADERS,
		E_NO_SWITCH
	};

private:

	/* * * * * * * * 
 	* 				  
 	*    CONSTANTS	  
 	* 				   				  
 	* * * * * * * * */

 	// Setting pins for devices
	// and screen constants

	const int m_scrW;
	const int m_scrH;
	const int m_dinPin;
	const int m_csPin;
	const int m_clkPin;
	const int m_NUM_OF_LED;
	const int m_btnPin;
	//const int m_ldrPin {A0};
	const int m_buzzPin;
	const int m_joyXPin;
	const int m_joyYPin;
	const int m_joyZPin; 

	/* * * * * * * * * 
 	* 				  
 	*  	SCREEN DATA   
	* 		AND       
	* 	  OBJECT	  
 	* 				  				
 	* * * * * * * * * */

	// Byte arrays of pixels. A,B,C,D represent Matrices and their addresses
	// (i,e: A = 0, B = 1)

	unsigned char m_pixelsA[_BYTE]{};
	unsigned char m_pixelsB[_BYTE]{}; 
	unsigned char m_pixelsC[_BYTE]{};
	unsigned char m_pixelsD[_BYTE]{};

	// LedControl lib object (for setting pixels and related methods)

	LedControl LedMatrix;


	/* * * * * * * * 
 	* 				 
 	*  	   I/O       
	* 	   DATA      
	* 	  	         						
 	* * * * * * * * */

	int m_joyX {0};
	int m_joyY {0};

	bool m_btnIsPressed {false};
	bool m_btnIsToggled {false};
	bool m_btnIsDoubleTapped {false};
 	unsigned long m_btnIsPressedTime {0};

	
	/* * * * * * * * *			 
 	*  	   MISC      
	*  INTERNAL DATA 	       		 	  	        					
 	* * * * * * * * */
 	
 	 const int m_gamesLoaded;
	 unsigned long m_dblTimer {0};
 	 unsigned long m_frame_dT {0};
 	 unsigned int m_fpsMax {60};
	 unsigned int m_fpsTarget {1000/m_fpsMax};
	 unsigned long m_frameStart{0};
	 unsigned long m_frameOld{0};
	 bool m_isToggle = false;
   const GameToSwitch m_gameList[2] {GameToSwitch::E_SNAKE, GameToSwitch::E_INVADERS};


public:

/**
 * Frame handling intialize method
 *
 * Sets m_frameOld to millis() at console start.
 *
 * @param void
 * 
 * @return void-
 */

void init();


/* * * * * * * * *
 * 				  
 *  MAIN METHOD   				  
 * 				  
 * * * * * * * * */

/**
 * Update Method
 *
 * Handles OS related functions
 * Calls all relevant methods to compute I/O States
 * Clears screen at start
 *
 * @param void
 * 
 * @return void-
 */


void updateOS(); 

/**
 * Update2 Method
 *
 * 
 * Handles debugging and screen drawing
 * Takes in the final byte data for pixels, and outputs it on screen.
 *
 * @param void
 * 
 * @return void-
 */

void updateOS2();


/* * * * * * * *  *
 * 				        
 * OS GAME METHODS 
 * 				        
 * * * * * * * * */

/**
 * Change Game Method
 *
 * 
 * Handles debugging and screen drawing
 * Takes in the final byte data for pixels, and outputs it on screen.
 *
 * @param changeTime uint -> How long you want to hold button to switch game (in milliseconds or seconds)
 * @param inSeconds bool -> Whether you want to input changeTime as seconds or not (True for seconds, False for ms)
 * 
 * @return Games of type Enum class Games. The game to switch to, or E_NO_SWITCH to indicate no switch.
 */


OS::GameToSwitch changeGame(unsigned int changeTime, bool inSeconds = false);


/* * * * * * * *  *
 * 				  
 * SCREEN METHODS 
 * 				  
 * * * * * * * * */

/**
 * Screen Intialize
 *
 * Initialzes screen to turn on each pixel
 * Call this before the main loop
 * 
 * @param void
 * 
 * @return void
 */

void scrInit();

/**
 * Screen Boot Up Animation
 *
 * Call this method before the main loop. (Take ~15 seconds to complete)
 *
 * @param void
 * 
 * @return void
 */
void scrBootUpAnim();

/**
 * Screen Boot Off Animation
 *
 * Call this method to turn off the screen. (Take ~15 seconds to complete)
 * 
 * @param void
 * 
 * @return void
 */

void scrBootOffAnim();

/**
 * Screen Reboot
 *
 * Call this method to reboot the screen (w/o animation)
 * if you want to use the screen again. 
 * (Take ~15 seconds to complete)
 * 
 * @param void
 * 
 * @return void
 */

void scrReboot();

/**
 * Screen Brightness Adjuster
 *
 * Adjusts brightness of the screen from a range of values
 * 
 * @param void
 * 
 * @return void
 */

void scrBrightness(int level);

/**
 * Screen Clear Method
 *
 * Sets all bytes of m_pixelsX[] array to 0 (OFF)
 * 
 * @param void
 * 
 * @return void
 */

void scrClear();

/**
 * Screen Clear Method Alternate
 *
 * Sets all pixels on screen to OFF via the native clearDisplay(int addr) method
 * in the LedControl lib
 * 
 * @param void
 * 
 * @return void
 */
void scrClear2();

/**
 * Screen Set LED Method
 *
 * Sets indiviusal LED Pixel at coordinate (x,y) 
 * (Efficient and Fast Bitwise Method)
 * 
 * @param iX Cartesian X coordinate for screen
 * @param iY Cartesian Y coordinate for screen
 * @param state Boolean of whether pixel coordinate should be ON or OFF
 * 
 * @return void
 */

void scrSetLED(int iX, int iY, bool state);

/**
 * Screen Set LED Method Alternate
 *
 * Sets indiviusal LED Pixel at coordinate (x,y) 
 * (Slow and native method to LedControl lib)
 * 
 * @param iX Cartesian X coordinate for screen
 * @param iY Cartesian Y coordinate for screen
 * @param state Boolean of whether pixel coordinate should be ON or OFF
 * 
 * @return void
 */

void scrSetLED2(int iX, int iY, bool state);

/**
 * Screen Draw Method
 *
 * Draws LED Coordinates from scrSetLED() method row by row
 * Call this after setting all of the pixels in your app
 *  
 * 
 * NOTE: Only use with scrSetLED(int ,int ,bool) method
 * will not work with scrSetLED2(int, int, bool)
 * 
 * @param void
 * 
 * @return void
 */

void scrDraw();

/**
 * Screen Draw2 Method
 *
 * Draws LED Coordinates for custom arrays (used for letters in this project)
 * Call this aftter setting a byte array of which letters are ON/OFF per row.
 *  
 * 
 * 
 * @param device Integer of address of each LED Matrix. Typically loop through each device and call with
 * an iterator.
 * @param array Byte Array, that contains data for setting pixel ON/OFF in each row
 * 
 * @return void
 */


void scrDraw2(int device, unsigned char* array);


/* * * * * * * * *
 * 				  
 * PERIPHERAL I/O 
 * 				  
 * 				  
 * * * * * * * * */

/**
 * Custom Joystick X method
 *
 * Uses data from m_joyXPin 
 * 
 * Modifies Joystick output to be mapped to your
 * custom control scheme
 * 
 * @param max Maximum value you want the joytsick to output.
 * @param min Minimum value you want the joystick to output.
 * @param threshold Default param to 6. Sets threshold for joystick deadzone.
 * 
 * @return m_joyX ---> Remapped Joystick X input
 * NOTE: Return is only for DEBUGGING, use getJoyX for normal purposes
 */

int customJoyX(float max, float min, int threshold = 6);

/**
 * Custom Joystick Y method
 *
 * Uses data from m_joyYPin 
 * 
 * Modifies Joystick output to be mapped to your
 * custom control scheme
 * 
 * @param max Maximum value you want the joytsick to output.
 * @param min Minimum value you want the joystick to output.
 * @param threshold OPTIONAL: Param set to 6 by default. Sets threshold for joystick deadzone.
 * 
 * @return m_joyY ---> Remapped Joystick Y input 
 * NOTE: return is only for DEBUGGING, use getJoyY for normal purposes
 */

int customJoyY(float max, float min, int threshold = 6);

/**
 * Compute Button States method
 *
 * Uses data from m_btnPin 
 * 
 * Computes button state on whether it is...
 * -> Pressed
 * -> Toggled
 * -> Double-Tapped
 * -> Button Held Duration
 * 

 * @param dT Delta Time variable from main loop (used for computing button held duration, and double tap)
 * 
 * @return void
 * 
 */


void computeBtnStates(int dT);

/**
 * Buzzer Method
 *
 * Uses data from m_buzzPin
 * 
 * Takes in frequency and time to create sound
 * using a buzzer component
 * 
 * @param freq Frequency in Hz of sound you want to make.
 * @param time Duration you want sound at frequency to produce.
 * @param iDelay OPTIONAL: Sets Delay, if you want to block code execution when
 * producing sound
 * 
 * @return void
 */


void buzzer(short freq, unsigned short time, unsigned int iDelay = 0);


/* * * * * * * * * *
 * 				   
 * 		 I/O       
 * GETTERS/SETTERS 
 * 				   
 * * * * * * * * * */

// Getters

/**
 * Get Joystick X Input
 *
 * 
 * Returns custom Joystick X input
 * 
 * @param void
 * @return m_joyX
 */

int getJoyX() const { return m_joyX; }

/**
 * Get Joystick Y Input
 *
 * 
 * Returns custom Joystick Y input
 * 
 * @param void
 * @return m_joyY
 */

int getJoyY() const { return m_joyY; }

/**
 * Get Joystick Z Input
 *
 * 
 * Returns raw Joystick Pressed input
 * NOTE: This does not customize pressed input and is ANALOG not digital
 * Do not use, if set input to DIGITAL.
 *  
 * @param void
 * @return analogRead(m_joyZPin) --> Range of [0 - 1023]
 */

int getJoyZ() const { return analogRead(m_joyYPin);}

/**
 * Get Button Pressed Input
 *
 * 
 * Returns if button is pressed or not
 
 * @param void
 * @return m_btnIsPressed --> Boolean. True if pressed. False if not.
 */

bool getBtnPressed() const { return m_btnIsPressed; }

/**
 * Get Button Toggled Input
 *
 * 
 * Returns if button is toggled or not.
 
 * @param void
 * @return m_btnIsToggled --> Boolean. True if toggled. False if not.
 */

bool getBtnToggled() const { return m_btnIsToggled; }

/**
 * Get Button Double-Tapped Input
 *
 * 
 * Returns if button is double-tapped or not.
 
 * @param void
 * @return m_btnIsDoubleTapped --> Boolean. True if Double-Tapped. False if not.
 */

bool getBtnDoubleTap() const { return m_btnIsDoubleTapped; }

/**
 * Get Button Pressed time
 *
 *
 * Returns how long button is pressed
 *
 * @param void
 * @return m_btnIsPressedTime --> uint long.
 */

unsigned long getBtnPressedTime() const { return m_btnIsPressedTime; }

/**
 * Get FPS Max
 *
 *
 * Returns what the MAX FPS is.
 *
 * @param void
 * @return m_fpsMax --> uint.
 */

unsigned int getFPSMax() const { return m_fpsMax; }

/**
 * Get FPS target
 *
 *
 * Returns what the FPS Target is in ms
 *
 * @param void
 * @return m_fpsTarget --> uint.
 */

 unsigned int getFPSTarget() const { return m_fpsTarget; }

/**
 * Gets Frame Delta Time
 *
 *
 * Returns change in time between frames
 *
 * @param void
 * @return m_frame_dT --> uint long.
 */

 unsigned long getFrame_dT() const { return m_frame_dT; }

/**
 * Gets Old Frame Time
 *
 *
 * Returns time from last frame
 *
 * @param void
 * @return m_frameOld --> uint long.
 */

 unsigned long getTimeOld() const { return m_frameOld; }


//  Setters

/**
 * Set Joystick X input
 *
 * Sets the custom m_joyX variable to your input.
 *
 * @param x  Integer to set to m_joyX 
 * @return void
 */

 void setJoyX(int x) { m_joyX = x; }

/**
 * Set Joystick Y input
 *
 * Sets the custom m_joyY variable to your input.
 *
 * @param x  Integer to set to m_joyY 
 * @return void
 */

 void setJoyY(int y) { m_joyY = y; }

/**
 * Set whether the Button is pressed
 *
 * Sets the m_btnIsPressed variable to ON/OFF
 *
 * @param state Boolean of whether the button is pressed or not
 * @return void
 */

  void setBtnPressed(bool state) { m_btnIsPressed = state; }

/**
 * Set whether the Button is toggled
 *
 * Sets the m_btnIsToggled variable to ON/OFF
 *
 * @param state Boolean of whether the button is toggled or not
 * @return void
 */

 void setBtnToggled(bool state) { m_btnIsToggled = state; }

/**
 * Set whether the Button is Double-Tapped
 *
 * Sets the m_btnIsDoubleTapped variable to ON/OFF
 *
 * @param state Boolean of whether the button is double-tapped or not
 * @return void
 */

 void setBtnDoubleTap(bool state) { m_btnIsDoubleTapped = state; }

/**
 * Set how long the button is pressed
 *
 * Sets the m_btnIsPressedTime variable to a time in ms 
 *
 * @param time uint long of how long the button is pressed
 * @return void
 */

 void setBtnPressedTime(unsigned long time) { m_btnIsPressedTime = time; }

/**
 * Set the dT between frame times
 *
 * Sets m_frame_dT to specific time
 *
 * @param timeDT uint long of how the duration of the dT.
 * @return void
 */

 void setFrame_dT(unsigned long timeDT) { m_frame_dT = timeDT; }

/**
 * Set the time of the old frame
 *
 * Sets m_frameOld to specific time
 *
 * @param timeOLd uint long of how the duration of the old time.
 * @return void
 */

 void setTimeOld(unsigned long timeOld) { m_frameOld = timeOld; }

/**
 * Set the FPS Maximum
 *
 * Sets m_fpsMax to your desired maximum frames per seconds (i,e; 60FPS)
 *
 * @param fps uint long of the maximum FPS.
 * @return void
 */

void setFPSMax(unsigned long fps) { m_fpsMax = fps; }


/* * * * * * * * * *
 * 				  
 *    DEBUGGING    
 * 				   
 * * * * * * * * * */

/** Debug Level Enumeration
 * 
 * Debug Enum for setting levels in printing methods
 *
 * @e: E_NORMAL --> Normal Debug Data. 
 * @e: E_VERBOSE --> Verbose and detailed Debug Data.
 */

enum DebugLevel{
 E_NORMAL = 0,
 E_VERBOSE
};

/** Print Joystick 
 * 
 * Prints Joystick Data
 *
 * @param debuglvl --> Specifes Debugging Level intensity
 * @e: E_NORMAL --> Prints m_joyX and Y. 
 * @e: E_VERBOSE --> Prints E_NORMAL output + raw input, cfg, and pin.
 * @return void
 */

void printJoy(DebugLevel debuglvl = E_NORMAL) const;

/** Print Button
 * 
 * Prints Button Data
 * 
 * @param debuglvl --> Specifes Debugging Level intensity
 * @e: E_NORMAL --> Prints m_btnIsPressed, m_btnIsDoubleTapped, and m_btnIsToggled. 
 * @e: E_VERBOSE --> Prints E_NORMAL output + m_btnIsPressedTime, m_dblTimer, and pin
 * @return void
 *
 */ 

void printBtn(DebugLevel debuglvl = E_NORMAL) const;

/** Print Button
 * 
 * Prints Button Data
 * 
 * @param debuglvl --> Specifes Debugging Level intensity
 * @e: E_NORMAL --> Prints buzzer data 
 * @e: E_VERBOSE --> Prints E_NORMAL output + cfg and pin.
 * @return void
 *
 */ 

void printBuzz(DebugLevel debuglvl = E_NORMAL) const;

/** Print LED Matrix
 * 
 * Prints LED Data
 * 
 * @param debuglvl --> Specifes Debugging Level intensity
 * @e: E_NORMAL --> Prints LED Pins
 * @e: E_VERBOSE --> Prints E_NORMAL output + LED Pin Data
 * @return void
 *
 */ 

void printLEDMatrix(DebugLevel debuglvl = E_NORMAL) const;

// Methods for Benchmarking

/** Sets LED Pixel Randomly
 * 
 * Uses bitwise, and native setLED methods to benchmark execution time between the two.
 * 
 * @param void --> Specifes Debugging Level intensity
 * @e: E_NORMAL --> Prints LED Pins
 * @e: E_VERBOSE --> Prints E_NORMAL output + LED Pin Data
 * @return void
 *
 */ 

void profilingLED();


/* * * * * * * * * *
 * 				   
 *   CONSTRUCTORS  
 * 				   
 * * * * * * * * * */

// Intializing objects and variables

// Default Constructor

OS::OS() 
  :
  LedMatrix(_DIN_PIN, _CLK_PIN, _CS_PIN, _NUM_OF_LED),
  m_scrW(_SCR_W), m_scrH(_SCR_H),
  m_dinPin(_DIN_PIN), m_csPin(_CS_PIN), m_clkPin(_CLK_PIN),
  m_NUM_OF_LED(_NUM_OF_LED), m_btnPin(_BTN_PIN), // m_ldrPin(LDR_PIN)
  m_buzzPin(_BUZZ_PIN),
  m_joyXPin(_JOYX_PIN), m_joyYPin(_JOYY_PIN), m_joyZPin(_JOYZ_PIN),
  m_gamesLoaded(_GAME_COUNT)

{
      	  pinMode(m_btnPin, INPUT);
        //pinMode(m_ldrPin, INPUT);
      	  pinMode(m_buzzPin, OUTPUT);
	        scrClear();
	        m_frameOld = millis();
} 

// Alternate constructor, to initialize things yourself

OS::OS (int iScrW, int iScrH,
	int iDinPin, int iCsPin, int iClkPin,
	int iNumOfLED, int iBtnPin, int iBuzzPin,
	int iJoyXpin, int iJoyYpin, int iJoyZpin,
	int iGamesLoaded
	) 
	:	
  LedMatrix(iDinPin, iClkPin, iCsPin, iNumOfLED),
	m_scrW(iScrW), m_scrH(iScrH),
	m_dinPin(iDinPin), m_csPin(iCsPin), m_clkPin(iClkPin),
	m_NUM_OF_LED(iNumOfLED), m_btnPin(iBtnPin), // m_ldrPin(LDR_PIN)
	m_buzzPin(iBuzzPin),
	m_joyXPin(iJoyXpin), m_joyYPin(iJoyYpin), m_joyZPin(iJoyZpin),
	m_gamesLoaded(iGamesLoaded)

{
	
      		pinMode(m_btnPin, INPUT);
          //pinMode(m_ldrPin, INPUT);
      		pinMode(m_buzzPin, OUTPUT);
	      	scrClear();
	      	m_frameOld = millis();
}


/* * * * * * * * * * *
 * 				     
 *   DECONSTRUCTORS  
 * 				     
 * * * * * * * * * * */

~OS(){}


};
