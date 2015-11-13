//**************************************************************//
//  Name    : shiftOutCode, distributor for valves
//  Author  : Erwin van den Beld
//  Notes   : Code for using a 74HC595 Shift Register           //
//****************************************************************

#ifndef DISTRIBUTOR_H_
#define DISTRIBUTOR_H_

#include "bartender.h"

class SerialBartender : public Bartender
{

public:

	SerialBartender(const int latchPin, const int clockPin,
			const int dataPin, const int oePin);
	virtual void setup();
	virtual void pourOut(const int valve, const int interval);

private:
	//Pin connected to ST_CP of 74HC595
	int latchPin;
	//Pin connected to SH_CP of 74HC595
	int clockPin;
	////Pin connected to DS of 74HC595
	int dataPin;
	//oe pin
	int oePin;

	//This method resets all bit to 0 TODO use master clear pin?
	void resetValves();
	// This method sends bits to the shift register:
	void doValve(const int whichValve, const int state);
};

#endif /* DISTRIBUTOR_H_ */
