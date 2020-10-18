#pragma once
#include "LedControl.h"
#include "Arduino.h"
#include "constants.h"
#include "utils.h"



class Screen{
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
	const int m_NUM_OF_LED;

	const int m_dinPin;
	const int m_clkPin;
	const int m_csPin;

	/* * * * * * * * 
 	* 				  
 	*   BYTE ARRAYS	  
 	* 				   				  
 	* * * * * * * * */

	// Byte arrays of pixels. A,B,C,D represent Matrices and their addresses
	// (i,e: A = 0, B = 1)

	unsigned char m_pixelsA[_BYTE]{};
	unsigned char m_pixelsB[_BYTE]{}; 
	unsigned char m_pixelsC[_BYTE]{};
	unsigned char m_pixelsD[_BYTE]{};

	/* * * * * * * * 
 	* 				  
 	*  LED CONTROL OBJ  
 	* 				   				  
 	* * * * * * * * */

  // LedControl lib object (for setting pixels and related methods)
	LedControl LedMatrix;

public:

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

void init();


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

void reboot();

/**
 * Screen Brightness Adjuster
 *
 * Adjusts brightness of the screen from a range of values
 * 
 * @param void
 * 
 * @return void
 */

void brightness(int level);

/**
 * Screen Clear Method
 *
 * Sets all bytes of m_pixelsX[] array to 0 (OFF)
 * 
 * @param void
 * 
 * @return void
 */

void clear();

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
void clear2();

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

void setLED(int iX, int iY, bool state);

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

void setLED2(int iX, int iY, bool state);

/**
 * Screen SetLED Wrapper
 *
 * Wrapper for LedControl setLED method
 * 
 *   Set the status for a specific Led.
     * Params :
     * int addr		The address of the display to control
     * int row		the row in which the led is located 
     *			Only values between 0 and 7 are valid.
     * int col		the column in which the led is located
     *			Only values between 0 and 7 are valid.
     * boolean state	If true the led is switched on, if false it is switched off
*/

void setLEDWrapper(int addr, int row, int col, bool state);


/**
 * Screen ShutDown Wrapper
 *
 * Wrapper for LedControl shutdown method
 *  
 *	Set the shutdown (power saving) mode for the device

     * Params :
     * int addr		The address of the display to control
     * boolean b	If true the device goes into power-down mode. If false
     *			device goes into normal operation
 *
 */

void shutdownWrapper(int addr, bool b);

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


void draw();

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


void draw2(int device, unsigned char* array);

/* * * * * * * * * *
 * 				  
 *    DEBUGGING    
 * 				   
 * * * * * * * * * */


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

void printLEDMatrix(DebugLevel debuglvl = DebugLevel::E_NORMAL) const;

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

Screen() :
  m_scrW(_SCR_W), m_scrH(_SCR_H), m_NUM_OF_LED(_NUM_OF_LED),
  m_dinPin(_DIN_PIN), m_clkPin(_CLK_PIN), m_csPin(_CS_PIN),
  LedMatrix(_DIN_PIN, _CLK_PIN, _CS_PIN, _NUM_OF_LED) 
  {}

Screen(int iScrW, int iScrH, int iNumOfLED,
	int iDinPin, int iClkPin, int iCsPin)
 	: 
	m_scrW(iScrW), m_scrH(iScrH), m_NUM_OF_LED(iNumOfLED),
	m_dinPin(iDinPin), m_clkPin(iClkPin), m_csPin(iCsPin),
	LedMatrix(iDinPin, iClkPin, iCsPin, iNumOfLED)
	{}

 /* * * * * * * * * *
 * 				   
 *   DESTRUCTORS  
 * 				   
 * * * * * * * * * */


 ~Screen() {}


};


class Joystick{
private:

	/* * * * * * * * 
 	* 				  
 	*    CONSTANTS	  
 	* 				   				  
 	* * * * * * * * */

 	// Setting pins for devices

	const int m_joyXPin;
	const int m_joyYPin;
	const int m_joyZPin; 

	/* * * * * * * * *
 	* 				  
 	*  CUSTOM I/O DATA	  
 	* 				   				  
 	* * * * * * * * */

	// Custom Input from Joy Y/X

	int m_joyX {0};
	int m_joyY {0};

public:

// Setters

/**
 * Set Joystick X method
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

int setJoyX(float max, float min, int threshold = 6);

/**
 * Set Joystick Y method
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

int setJoyY(float max, float min, int threshold = 20);

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


/* * * * * * * * * *
 * 				  
 *    DEBUGGING    
 * 				   
 * * * * * * * * * */

/** Print Joystick 
 * 
 * Prints Joystick Data
 *
 * @param debuglvl --> Specifes Debugging Level intensity
 * @e: E_NORMAL --> Prints m_joyX and Y. 
 * @e: E_VERBOSE --> Prints E_NORMAL output + raw input, cfg, and pin.
 * @return void
 */

void printJoy(DebugLevel debuglvl = DebugLevel::E_NORMAL) const;

/* * * * * * * * * *
 * 				   
 *   CONSTRUCTORS  
 * 				   
 * * * * * * * * * */

Joystick() :
m_joyXPin(_JOYX_PIN), m_joyYPin(_JOYY_PIN), m_joyZPin(_JOYZ_PIN)
{}

Joystick(int iJoyXpin, int iJoyYpin, int iJoyZpin) :
m_joyXPin(iJoyXpin), m_joyYPin(iJoyYpin), m_joyZPin(iJoyZpin) {}



/* * * * * * * * * *
 * 				   
 *   DESTRUCTORS  
 * 				   
 * * * * * * * * * */

 ~Joystick(){}


};


class Button{
private:

	/* * * * * * * * 
 	* 				  
 	*    CONSTANT	  
 	* 				   				  
 	* * * * * * * * */

 	// Setting pins for device

	const int m_btnPin;

	/* * * * * * * * 
 	* 				  
 	* CUSTOM I/O DATA	  
 	* 				   				  
 	* * * * * * * * */

 	// Custom input from buttons (toggle, double tap, pressed time, etc.)

	bool m_btnIsPressed {false};
	bool m_btnIsToggled {false};
	bool m_btnIsDoubleTapped {false};
 	unsigned long m_btnIsPressedTime {0};
	unsigned long m_dblTimer {0};
	bool m_isToggle = false;

public:

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

/* * * * * * * * * *
 * 				   
 * 		 I/O       
 * GETTERS/SETTERS 
 * 				   
 * * * * * * * * * */


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

/* * * * * * * * * *
 * 				  
 *    DEBUGGING    
 * 				   
 * * * * * * * * * */

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

	void printBtn(DebugLevel debuglvl = DebugLevel::E_NORMAL) const;

/* * * * * * * * * *
 * 				   
 *   CONSTRUCTORS  
 * 				   
 * * * * * * * * * */

	Button() :
		m_btnPin(_BTN_PIN)
	{
		pinMode(m_btnPin, INPUT);
	}

	Button(int iBtnPin) :
		m_btnPin(_BTN_PIN)
	{
		pinMode(m_btnPin, INPUT);
	}

/* * * * * * * * * *
 * 				   
 *   DESTRUCTORS  
 * 				   
 * * * * * * * * * */

 	~Button() {}
};




class Buzzer {
private:

	/* * * * * * * * 
 	* 				  
 	*    CONSTANT	  
 	* 				   				  
 	* * * * * * * * */

 	// Setting pin for device
	const int m_buzzPin;

public:

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
 *    DEBUGGING    
 * 				   
 * * * * * * * * * */


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

	void printBuzz(DebugLevel debuglvl = DebugLevel::E_NORMAL) const;

/* * * * * * * * * *
 * 				   
 *   CONSTRUCTORS  
 * 				   
 * * * * * * * * * */

 	Buzzer() : 
 		m_buzzPin(_BUZZ_PIN) 
 	{
	 	pinMode(m_buzzPin, OUTPUT);
    }

 	Buzzer(int iBuzzPin) :
 		m_buzzPin(iBuzzPin)
 	{	
	 	pinMode(m_buzzPin, OUTPUT);	 
 	}

/* * * * * * * * * *
 * 				   
 *   DESTRUCTORS  
 * 				   
 * * * * * * * * * */

	~Buzzer(){}

};
