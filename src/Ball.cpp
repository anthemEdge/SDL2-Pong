/*
 * Ball.cpp
 *
 *  Created on: 26 Jul 2015
 *      Author: eva
 */

#include "Ball.h"

Ball::Ball(int timeTicks) {
	newBall(timeTicks);
}

void Ball::newBall(int timeTicks) {

	// Ball spawn at the centre of the screen
	mPosX = (SCREEN_WIDTH - mSize) / 2;
	mPosY = (SCREEN_HEIGHT - mSize) / 2;

	// Ball has random initial direction
	double direction = 2 * M_PI * rand() / RAND_MAX;
	mVelY = mSpeed * sin(direction);
	mVelX = mSpeed * cos(direction);

	// minor correction: make sure X speed in always higher
	if (mVelX * mVelX < mVelY * mVelY) {
		double temp = mVelX;
		mVelX = mVelY;
		mVelY = temp;
	}

	mLastUpdate = timeTicks;
}

void Ball::update(int timeTicks, int barLeftPos, int barRightPos) {
	// Time based displacement
	// Ball is the same speed on all computers
	// Time elapsed since last update, in seconds
	double elapse = (double) (timeTicks - mLastUpdate) / 1000;

	// Update position
	mPosX += round(mVelX * elapse);
	mPosY += round(mVelY * elapse);

	// set update time
	mLastUpdate = timeTicks;

	// Check for collisions
	// Always bounce off top and bottom of the screen
	if (mPosY < 0 || mPosY > (SCREEN_HEIGHT - mSize)) {
		mVelY = -mVelY;
		if (mPosY < 0) {
			mPosY = 0;
		} else {
			mPosY = SCREEN_HEIGHT - mSize;
		}
	}

	bool bounced = false;
	bool left = false;
	bool right = false;
	// Check for bar and ball collisions
	if (mPosX < mSize || mPosX > (SCREEN_WIDTH - 2 * mSize)) {
		// Ball bounce off the edge and minor correction to position
		if (mPosX < mSize) {
			// Left
			if (mPosY + mSize > barLeftPos && mPosY < barLeftPos + BAR_Length) {
				mPosX = mSize;
				mVelX = -mVelX;
				left = true;
				bounced = true;
			} else {
				newBall(timeTicks);
			}
		}

		if (mPosX > SCREEN_WIDTH - mSize) {
			if (mPosY + mSize > barRightPos
					&& mPosY < barRightPos + BAR_Length) {
				mPosX = SCREEN_WIDTH - 2 * mSize;
				mVelX = -mVelX;
				bounced = true;
				right = true;
			} else {
				newBall(timeTicks);
			}
		}
	}

	// Adding speed and some randomness when the ball bounce off the bar
	double changeRate = 0.05; 	// direction change
	if (bounced) {
		int yMod = 1;
		int xMod = 1;
		if (mVelY < 0) {
			yMod = -1;
		}
		if (mVelX < 0) {
			xMod = -1;
		}
		// Acceleration everybounce
		double direction = M_PI * 0.5 * rand() / RAND_MAX;
		mVelY += yMod * mSpeed * changeRate * sin(direction);
		mVelX += xMod * mSpeed * changeRate * cos(direction);

//		mVelY += mVelY * mSpeed * changeRate * sin(direction);
//		mVelX += mVelX * mSpeed * changeRate * cos(direction);
	}

}

Ball::~Ball() {
}

