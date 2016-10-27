// TODO DOC + license
// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef bar2_H_
#define bar2_H_
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
boolean glassReady();
void messageCompleted();
void selfTest();
#ifdef __cplusplus
} // extern "C"
#endif

//****** Pins ******
static const int NUMBER_OF_VALVES = 8;


#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

	//*** ATmega Valves ***//
	static const int PIN_VALVE1 = 2;
	static const int PIN_VALVE2 = 3;
	static const int PIN_VALVE3 = 4;
	static const int PIN_VALVE4 = 5;
	static const int PIN_VALVE5 = 6;
	static const int PIN_VALVE6 = 7;
	static const int PIN_VALVE7 = 8;
	static const int PIN_VALVE8 = 9;
	static int VALVE_PINS[NUMBER_OF_VALVES] = {PIN_VALVE1, PIN_VALVE2, PIN_VALVE3, PIN_VALVE4,
			PIN_VALVE5, PIN_VALVE6, PIN_VALVE7, PIN_VALVE8};

	/* LCD Pins
	 *
	 * Method2:
	 *      LCD                          Arduino
	 *      SCK       clockPin(defined in the "initDriverPin" function)
	 *      CS        latchPin(defined in the "initDriverPin" function)
	 *      SID       dataPin (defined in the "initDriverPin" function)
	 *      VCC                            5V
	 *      GND                           GND
	 */
	//static const int PIN_LCD_SCK_CLOCK = A3;
	//static const int PIN_LCD_CS_LATCH = A4;
	//static const int PIN_LCD_SID_DATA = A5;
	//
	////LCD Messages
	//static unsigned int LCD_W = 16;
	//static unsigned char TITLE[]=           "  B A R   R D M ";
	//static unsigned char TITLE2[]=          "----------------";
	//static unsigned char MSG_CLEAR[]= 	    "                ";
	//static unsigned char MSG_READY[]= 		"Place your order";
	//static unsigned char MSG_FULL[]=  		"Order ready     ";
	//static unsigned char MSG_PROCESS[]=		"In progress..   ";

#else
	//*** Arduino Valves ***//
	#define PIN_BLUETOOTH_RxD 3
	#define PIN_BLUETOOTH_TxD 2

	#define PIN_DIST_LATCH 4
	#define PIN_DIST_CLOCK 5
	#define PIN_DIST_DATA 6
	#define PIN_DIST_OE 7

#endif

#define IR_RANGE A5
#define IR_BUMB_THRESHOLD_MIN 20
#define IR_BUMB_THRESHOLD_MAX 55

#define SONAR_TRIGGER A0
#define SONAR_ECHO 9

static const int PIN_RED = 10;
static const int PIN_GREEN = 11;
static const int PIN_BLUE = 12;
static const int PIN_STATUS = 13;


/****** State ******/
//Bar states
enum State {INIT, NO_GLASS, READY, FULL};

static const int POOR = 250; //250  Milliseconds poor FIXME 10cc
static const int MAX = 30;


//Do not add code below this line
#endif /* bar2_H_ */
