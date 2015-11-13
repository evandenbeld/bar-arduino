/*
 * serialbartender.cpp
 *
 *  Created on: 24 nov. 2012
 *      Author: erwin
 */

#ifndef DISTRIBUTOR_H_
	#include "serialbartender.h"
#endif
#ifndef Arduino_h
	#include "Arduino.h"
#endif

SerialBartender::SerialBartender(const int latchPin, const int clockPin,
		const int dataPin, const int oePin)
{
	this->latchPin = latchPin;
	this->clockPin =clockPin;
	this->dataPin = dataPin;
	this->oePin = oePin;
}

void SerialBartender::setup()
{
	//set pins to output because they are addressed in the main loop
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(oePin, OUTPUT);

	//Output disabled
	digitalWrite(oePin, HIGH);

	//Reset all valves
	resetValves();
}

void SerialBartender::pourOut(const int valve, const int interval)
{

	Serial.print("DO VALVE: ");
	Serial.println(valve);

	Serial.print("Time: ");
	Serial.println(interval, DEC);
	//Enable DD 4 bottle swap
	int vIndex = valve == 7 ? 0 : valve;
	doValve(vIndex, HIGH);
	//output enable
	digitalWrite(oePin, LOW);
	delay(interval);
	//output disable
	digitalWrite(oePin, HIGH);

	doValve(valve, LOW);
}

void SerialBartender::resetValves()
{

	  byte bitsToSend = 0b00000000;

	  //Disable latch while shifting bits
	  digitalWrite(latchPin, LOW);

	  // shift the bits out:
	  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

	    // turn on the output so the LEDs can light up:
	  digitalWrite(latchPin, HIGH);
}

void SerialBartender::doValve(const int whichValve, const int state)
{
		// the bits you want to send
	  byte bitsToSend = 0b00000000;

	  //Disable latch while shifting bits
	  digitalWrite(latchPin, LOW);

	  // turn on the correct bit in bitsToSend:
	  bitWrite(bitsToSend, whichValve, state);

	  // shift the bits out:
	  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

	    // turn on the output so the LEDs can light up:
	  digitalWrite(latchPin, HIGH);
}


