/*
 * Status.cpp
 *
 *  Created on: 27 sep. 2013
 *      Author: erwin
 */

#include "Status.h"
#include "Arduino.h"

const int Status::BLACK[3]= {0,0,0 };
const int Status::WHITE[3] = {255,255,255 };
const int Status::RED[3]    = { 255, 0, 0 };
const int Status::GREEN[3]  = { 0, 255, 0 };
const int Status::DARK_BLUE[3]   = { 0, 0, 128 };
const int Status::BLUE[3]   = { 0, 0, 255 };
const int Status::ORANGE[3] = { 255, 128, 0 };
const int Status::YELLOW[3] = { 255, 255, 0 };

Status::Status(const int redPin, const int greenPin, const int bluePin, const int whitePin) {

	this->redPin = redPin;
	this->greenPin = greenPin;
	this->bluePin = bluePin;
	this->whitePin = whitePin;

	pinMode(redPin, OUTPUT);   // sets the pins as output
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
	pinMode(whitePin, OUTPUT);

	// Initialize color variables
	redVal = 0;
	grnVal = 0;
	bluVal = 0;

	prevR = redVal;
	prevG = grnVal;
	prevB = bluVal;

	wait = 3;      // 10ms internal crossFade delay; increase for slower fades
	hold = 0;       // Optional hold when a color is complete, before the next crossFade
	j = 0;          // Loop counter for repeat

}

Status::~Status() {
	// TODO Auto-generated destructor stub
}

void Status::setColor(const int color[3])
{
	 this->redVal = color[0];
	 this->grnVal = color[1];
	 this->bluVal = color[2];

	 if(color == WHITE)
	 {
		 digitalWrite(whitePin, HIGH);
		 digitalWrite(redPin, LOW);
		 digitalWrite(greenPin, LOW);
		 digitalWrite(bluePin, LOW);
	 }
	 else
	 {
		 digitalWrite(whitePin, LOW);
		 analogWrite(this->redPin, this->redVal);
		 analogWrite(this->greenPin, this->grnVal);
		 analogWrite(this->bluePin, this->bluVal);
	 }


}

/* crossFade() converts the percentage colors to a
*  0-255 range, then loops 1020 times, checking to see if
*  the value needs to be updated each time, then writing
*  the color values to the correct pins.
*/
void Status::crossFade(const int color[3]) {

  int stepR = calculateStep(prevR, color[0]);
  int stepG = calculateStep(prevG, color[1]);
  int stepB = calculateStep(prevB, color[2]);

  for (int i = 0; i <= 1020; i++) {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);

    analogWrite(this->redPin, redVal);   // Write current values to LED pins
    analogWrite(this->greenPin, grnVal);
    analogWrite(this->bluePin, bluVal);

    delay(wait); // Pause for 'wait' milliseconds before resuming the loop


  }
  // Update current values for next loop
  prevR = redVal;
  prevG = grnVal;
  prevB = bluVal;
  delay(hold); // Pause for optional 'wait' milliseconds before resuming the loop
}

void Status::warning()
{
	for(int i=0;i<3;i++)
	{
		setColor(Status::RED);
		delay(300);
		setColor(Status::BLACK);
		delay(300); // wait
	}
}

/* The next function is calculateVal. When the loop value, i,
*  reaches the step size appropriate for one of the
*  colors, it increases or decreases the value of that color by 1.
*  (R, G, and B are each calculated separately.)
*/
int Status::calculateVal(const int step, int val, const int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;
    }
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    }
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  }
  else if (val < 0) {
    val = 0;
  }
  return val;
}

int Status::calculateStep(const int prevValue, const int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero,
    step = 1020/step;              //   divide by 1020
  }
  return step;
}

