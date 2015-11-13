/*
 * TODO comment for bartender.h
 *
 *  Created on: 20 apr. 2014
 *      Author: erwin
 */

#ifndef BARTENDER_H_
#define BARTENDER_H_

class Bartender
{
public:
	virtual void pourOut(const int valve, const int interval) = 0;
	virtual void setup() = 0;
	virtual ~Bartender() {};
};


#endif /* BARTENDER_H_ */
