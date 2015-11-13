// Do not remove the include below
#include "bar2.h"
#include "LCD12864RSPI.h"
#include "logo.h"
#include <Messenger.h>
#include "Status.h"


#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

#include "simplebartender.h"

//Input device (blue tooth)
HardwareSerial& communicator = Serial1;

//Output device: LCD
//LCD12864RSPI lcd(PIN_LCD_CS_LATCH, PIN_LCD_SCK_CLOCK, PIN_LCD_SID_DATA);

//Bartender the valve controller
SimpleBartender simpleBartender(VALVE_PINS);
Bartender& bartender = simpleBartender;

#else

#include "SoftwareSerial.h"
#include "serialbartender.h"

//bluetooth input
SoftwareSerial communicator(PIN_BLUETOOTH_RxD, PIN_BLUETOOTH_TxD);
//Valve distribution
SerialBartender serialBartender(PIN_DIST_LATCH, PIN_DIST_CLOCK,
		PIN_DIST_DATA, PIN_DIST_OE);
Bartender& bartender = serialBartender;
#endif

//Input processor
Messenger message = Messenger();

//Output device: status color
Status status(PIN_RED,PIN_GREEN,PIN_BLUE);

//Amount of poured drinks
int total;

//Oevrall state
State state = INIT;

//messenger process function
void setup()
{
	//Start input
	Serial.begin(9600);
	communicator.begin(9600);

	//	FIXME setupBlueToothConnection();

	//Start Status
	pinMode(PIN_STATUS, OUTPUT);
	status.setColor(Status::BLACK);

//	//Start lcd
//	lcd.Initialise(); // INIT SCREEN
//	delay(100);

	//Start self test
	selfTest();

	//Start messenger
	message.attach(messageCompleted);

	//Start bartender
	bartender.setup();

	//Fade to blue
	status.crossFade(Status::BLUE);

//	//Set LCD to normal operation text
//	lcd.CLEAR();
//	lcd.DisplayString(0,0, TITLE , LCD_W);
//	lcd.DisplayString(1,0, TITLE2 , LCD_W);
//	delay(30);

	state = NO_GLASS;
	Serial.println("Bar is open!");

}

void loop()
{
	//TODO check other sensors
	boolean glass = glassReady();

	switch(state)
	{
		case INIT:
		{
			status.setColor(Status::BLACK);
			Serial.println("Not yet initialized");
			break;
		}
		case NO_GLASS:
		{
			status.setColor(Status::BLUE);
//			lcd.DisplayString(3,0, MSG_CLEAR , LCD_W);
			if(glass)
			{
				Serial.println("Glass placed");
				state = READY;
				total = 0;
//				lcd.DisplayString(2,0, MSG_READY , LCD_W);
				delay(10);

			}
			break;
		}
		case READY:
		{
			status.setColor(Status::WHITE);
			if(!glass)
			{
				Serial.println("Glass removed");
				state = NO_GLASS;
//				lcd.DisplayString(2,0, MSG_CLEAR , LCD_W);
				delay(10);

			}
			else if(total >= MAX)
			{
				Serial.println("Glass full");
				state = FULL;
//				lcd.DisplayString(2,0, MSG_FULL , LCD_W);
				delay(10);
			}
			break;
		}
		case FULL:
		{
			status.setColor(Status::GREEN);
			if(!glass)
			{
				Serial.println("Full glass removed");
				state = NO_GLASS;
//				lcd.DisplayString(2,0, MSG_CLEAR , LCD_W);
				delay(10);
			}
			break;
		}
	}

	//handle input by feeding the serial data to Messenger
	while ( communicator.available( ) ) message.process(communicator.read( ) );
}

void messageCompleted()
{
	Serial.println("Message complete");
//	lcd.DisplayString(3,0, MSG_PROCESS, 20);
	//Check for command
	if ( message.checkString("v") ) //Poor valve
	{
		int valve = message.readInt();
		Serial.print("Received valve: ");
		Serial.println(valve,DEC);
		int amount = message.readInt();
		Serial.print("Received amount: ");
		Serial.println(amount,DEC);

		//Check state
		if(state != READY)
		{
			//TODO error codes and strings
			communicator.print("INVALID STATE: ");
			communicator.println(state);
			status.warning();
		}
		else if(valve < 1 || valve > NUMBER_OF_VALVES)
		{
			communicator.println("UNKNOWN VALVE");
			status.warning();
		}
		else if(total + amount > MAX)
		{
			communicator.println("TO MUCH FOR GLASS");
			status.warning();
		}
		else
		{
			Serial.println("*** Start Poor ***");
			status.setColor(Status::ORANGE);
			bartender.pourOut(valve, amount * POOR);
			total += amount;
			communicator.println("OKAY");
			Serial.println("*** Poor complete ***");
		}
	}
	//TODO other commands

//	lcd.DisplayString(3,0, MSG_CLEAR, 20);
}

boolean glassReady()
{
	//Check glass sensor
//	Serial.print("Read glass sensor: ");
	float volts = analogRead(IR_RANGE)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
	float distance = 65*pow(volts, -1.10);          // TODO macro? : worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
//	Serial.println(distance);

	return distance > IR_BUMB_THRESHOLD_MIN && distance < IR_BUMB_THRESHOLD_MAX;

}

void selfTest()
{
	Serial.println("*** Starting self test ***");

	//LOGO
//	lcd.DrawFullScreen(logo);

	//Check glass
	if(glassReady())
		Serial.println("Glass ready");
	else
		Serial.println("No glass");

	//TODO other sensor checks

	//Status
	status.setColor(Status::RED);
	delay(200);
	status.setColor(Status::GREEN);
	delay(200);
	status.setColor(Status::BLUE);
	delay(200);
	status.setColor(Status::BLACK);

	Serial.println("*** End of self test ***");

}
