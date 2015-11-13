/*
 * simplebartender.cpp

 *
 *  Created on: 20 apr. 2014
 *      Author: erwin
 */
#ifndef Arduino_h
	#include "Arduino.h"
#endif
#include "simplebartender.h"

SimpleBartender::SimpleBartender(int pins[NUMBER_OF_VALVES])
{
	for(int i =0; i< NUMBER_OF_VALVES;i++)
	{
		this->valves[i] = pins[i];
	}
}

void SimpleBartender::setup()
{
	for(int i=0;i<NUMBER_OF_VALVES;i++)
	{
		pinMode(valves[i], OUTPUT);
	}
}

void SimpleBartender::pourOut(const int valve, const int interval)
{
	int pin = constrain(valve-1,0,NUMBER_OF_VALVES);
	digitalWrite(valves[pin],HIGH);
	delay(interval);
	digitalWrite(valves[pin],LOW);
}


