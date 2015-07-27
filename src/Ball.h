/*
 * Ball.h
 *
 *  Created on: 26 Jul 2015
 *      Author: eva
 */

#ifndef BALL_H_
#define BALL_H_

#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;

class Ball {

public:
	const static int mSize = 16;
	const static int mSpeed = 500;
	int mPosX, mPosY;

	const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 720;

public:
	const static int BAR_Length = 144;

private:
	double mVelX, mVelY;
	int mLastUpdate;

public:
	Ball(int timeTicks);
	void update(int timeTicks, int barLeftPos = 0, int barRightPos = 0);
	void newBall(int timeTicks);
	virtual ~Ball();
};

#endif /* BALL_H_ */
