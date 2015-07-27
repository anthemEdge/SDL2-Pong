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

	mSpeed = 400;
	mCanBounce = true;

	// Ball spawn at the centre of the screen
	mPosX = (ARENA_SIZE - mSize) / 2;
	mPosY = (ARENA_SIZE - mSize) / 2;

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

int Ball::update(int timeTicks, int barLeftPos, int barRightPos) {

	int returnValue = 0;
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
	if (mPosY < 0 || mPosY > (ARENA_SIZE - mSize)) {
		mVelY = -mVelY;
		if (mPosY < 0) {
			mPosY = 0;
		} else {
			mPosY = ARENA_SIZE - mSize;
		}
	}

	bool bounced = false;
	int maxChange = 60 * (2 * M_PI / 360);

	// Check for bar bounce
	if ((mPosX < 0 || mPosX > ARENA_SIZE - mSize) && mCanBounce) {
		// Left Bounce
		if (mPosX < 0 && mPosY + mSize > barLeftPos
				&& mPosY < barLeftPos + BAR_Length) {
			mPosX = 0;
			// Position based relative change
			double changeRate = (double) (barLeftPos + BAR_Length / 2 - mPosY)
					/ (BAR_Length / 2);
			double direction = M_PI / 2 + maxChange * changeRate;
			mVelX = mSpeed * sin(direction);
			mVelY = mSpeed * cos(direction);
			bounced = true;
		}
		// Right bounce
		else if (mPosX > ARENA_SIZE - mSize && mPosY + mSize > barRightPos
				&& mPosY < barRightPos + BAR_Length) {
			mPosX = ARENA_SIZE - mSize;
			// Position based relative change
			double changeRate =
					(double) (mPosY - (barRightPos + BAR_Length / 2))
							/ (BAR_Length / 2);
			double direction = M_PI * 1.5 + maxChange * changeRate;
			mVelX = mSpeed * sin(direction);
			mVelY = mSpeed * cos(direction);
			bounced = true;
			// Game over
		} else {
			mCanBounce = false;
		}

	} else if ((mPosX < -mGap || mPosX > ARENA_SIZE + mGap) && !mCanBounce) {
		// game over
		newBall(timeTicks);
	}

	// Ball gets faster
	if (bounced) {
		mCanBounce = true;
		mSpeed += 5;
	}

	return returnValue;

}

void Ball::setGap(int gap) {
	mGap = gap;
}

Ball::~Ball() {
}

