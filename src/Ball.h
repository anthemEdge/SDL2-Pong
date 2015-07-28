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
#include <SDL.h>
#include <cstdlib>

using namespace std;

class Ball {

public:
	int mPosX, mPosY;
public:
	const static int BAR_Length = 64;
	const static int mSize = 8;

private:
	const static int ARENA_SIZE = 480;
	double mVelX, mVelY;
	int mSpeed;
	int mLastUpdate;
	int mGap;
	bool mLeftWon;

private:
	bool collision(int barX, int barY);

public:
	Ball(int timeTicks);
	bool update(int timeTicks, int barLeftPos = 0, int barRightPos = 0);
	void newBall(int timeTicks);
	void setGap(int gap);
	bool leftWon();
	virtual ~Ball();
};

#endif /* BALL_H_ */
