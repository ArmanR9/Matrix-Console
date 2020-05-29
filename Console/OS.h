#pragma once
#include "LedControl.h"
#include "Arduino.h"
#include "devices.h"
#include "constants.h"
#include "utils.h"




class OS {

public:

	/* * * * * * 			 
 	*  	      
	* 	DEVICES
	* 	       		 	  	        					
 	* * * * * * */

	Screen Scr;
	Joystick Joy;
	Button Btn;
	Buzzer Buzz;

private:

	
	/* * * * * * * * *			 
 	*  	      
	*  FRAME HANDLING
	*      DATA
	* 	       		 	  	        					
 	* * * * * * * * */
 	
 	 unsigned long m_frame_dT {0};
 	 unsigned int m_fpsMax {60};
	 unsigned int m_fpsTarget {1000/m_fpsMax};
	 unsigned long m_frameStart{0};
	 unsigned long m_frameOld{0};


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
 *  MAIN OS METHOD   				  
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


	void update(); 

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

	void update2();


/**
 * Screen Boot Up Animation
 *
 * Call this method before the main loop. (Take ~15 seconds to complete)
 *
 * @param void
 * 
 * @return void
 */

	void bootUpAnim();

/**
 * Screen Boot Off Animation
 *
 * Call this method to turn off the screen. (Take ~15 seconds to complete)
 * 
 * @param void
 * 
 * @return void
 */

	void bootOffAnim();


/* * * * * * * * *
 * 				  
 *  FRAME HANDLING METHODS  				  
 * 				  
 * * * * * * * * */


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


/**
 * Set the dT between frame times
 *
 * Sets m_frame_dT to specific time
 *
 * @param timeDT uint long of how the duration of the dT.
 * @return void
 */

  // void setFrame_dT(unsigned long timeDT) { m_frame_dT = timeDT; }

/**
 * Set the time of the old frame
 *
 * Sets m_frameOld to specific time
 *
 * @param timeOLd uint long of how the duration of the old time.
 * @return void
 */

  // void setTimeOld(unsigned long timeOld) { m_frameOld = timeOld; }

/**
 * Set the FPS Maximum
 *
 * Sets m_fpsMax to your desired maximum frames per seconds (i,e; 60FPS)
 *
 * @param fps uint long of the maximum FPS.
 * @return void
 */

 // void setFPSMax(unsigned long fps) { m_fpsMax = fps; }


/* * * * * * * * * *
 * 				  
 *    DEBUGGING    
 * 				   
 * * * * * * * * * */

void printFrameData(DebugLevel debuglvl = DebugLevel::E_NORMAL) const;


/* * * * * * * * * *
 * 				   
 *   CONSTRUCTORS  
 * 				   
 * * * * * * * * * */

// Intializing objects and variables

// Default Constructor

	OS() :
		Scr(), Joy(), Btn(), Buzz() 
	{
	    Scr.clear();
	    m_frameOld = millis();
	} 


// Alternate constructor, to initialize things yourself
/*
	OS (int iScrW, int iScrH,
	int iDinPin, int iCsPin, int iClkPin,
	int iNumOfLED, int iBtnPin, int iBuzzPin,
	int iJoyXpin, int iJoyYpin, int iJoyZpin
	) :
		Scr(iScrW, iScrH, iDinPin, iCsPin, iClkPin, iNumOfLED),
		Btn(iBtnPin),
		Joy(iJoyXpin, iJoyYpin, iJoyZpin),
		Buzz(iBuzzPin)
	{
          //pinMode(m_ldrPin, INPUT);
	      	Scr.clear();
	      	m_frameOld = millis();
	}	
*/

/* * * * * * * * * * *
 * 				     
 *   DECONSTRUCTORS  
 * 				     
 * * * * * * * * * * */

	~OS(){}

};

