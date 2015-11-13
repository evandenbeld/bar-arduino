/*
 * simplebartender.h
 *
 *  Created on: 20 apr. 2014
 *      Author: erwin
 */

#ifndef SIMPLEBARTENDER_H_
#define SIMPLEBARTENDER_H_

#include "bartender.h"

#define NUMBER_OF_VALVES 7

class SimpleBartender : public Bartender
{

public:

	SimpleBartender(int pins[NUMBER_OF_VALVES]);
	virtual void setup();
	virtual void pourOut(const int valve, const int interval);

private:
	int valves[NUMBER_OF_VALVES];
};

#endif /* SIMPLEBARTENDER_H_ */
