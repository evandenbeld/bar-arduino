/*
 * Status.h
 *
 *  Created on: 27 sep. 2013
 *      Author: erwin
 */

#ifndef STATUS_H_
#define STATUS_H_

class Status {
public:

	//Color arrays
	static const int BLACK[3];
	static const int WHITE[3];
	static const int RED[3];
	static const int GREEN[3];
	static const int DARK_BLUE[3];
	static const int BLUE[3];
	static const int ORANGE[3];
	static const int YELLOW[3];

	Status(const int redPin, const int greenPin, const int bluePin);
	virtual ~Status();

	void crossFade(const int color[3]);
	void setColor(const int color[3]);
	void warning();

private:

	int redPin;
	int greenPin;
	int bluePin;

	// Set initial color
	int redVal;
	int grnVal;
	int bluVal;

	int wait;      // 10ms internal crossFade delay; increase for slower fades
	int hold;       // Optional hold when a color is complete, before the next crossFade
	int j;          // Loop counter for repeat

	int prevR;
	int prevG;
	int prevB;

	int calculateStep(const int prevValue, const int endValue);
	int calculateVal(const int step, const int val, const int i);
};

#endif /* STATUS_H_ */
