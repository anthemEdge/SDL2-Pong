/*
 * Graphics.cpp
 *
 *  Created on: 26 Jul 2015
 *      Author: eva
 */

#include "Graphics.h"

Graphics::Graphics() :
		mWindow(NULL), mRenderer(NULL) {
}

bool Graphics::init() {
	bool success = true;

	// SDL System Initialisation
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		success = false;
		printf("SDL unable to initialise! SDL Error: %s. \n", SDL_GetError());
	}

	// Create and Present a Window
	if (success) {
		mWindow = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == NULL) {
			success = false;
			printf("SDL unable to create window! SDL Error: %s. \n",
					SDL_GetError());
		}
	}

	// Create corresponding Renderer from window
	if (success) {
		mRenderer = SDL_CreateRenderer(mWindow, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (mRenderer == NULL) {
			success = false;
			printf("SDL unable to create renderer! SDL Error: %s. \n",
					SDL_GetError());
		}
	}

	// Hide Cursor
	SDL_ShowCursor(0);
	// Trap cursor
	SDL_SetRelativeMouseMode(SDL_TRUE);

	return success;
}

void Graphics::clear() {
	// Clear the renderer from previous frames
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(mRenderer);
}

void Graphics::draw(Ball* ball, int leftBarPos, int rightBarPos) {

	// Drawing ball to renderer
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect ballRect = { ball->mPosX + GAP, ball->mPosY, Ball::mSize,
			Ball::mSize };
	SDL_RenderFillRect(mRenderer, &ballRect);

	// Draw bars to renderer
	SDL_Rect leftBar = { GAP - Ball::mSize, leftBarPos, Ball::mSize,
			Ball::BAR_Length };
	SDL_Rect rightBar = { SCREEN_WIDTH - GAP, rightBarPos, Ball::mSize,
			Ball::BAR_Length };

	SDL_RenderFillRect(mRenderer, &leftBar);
	SDL_RenderFillRect(mRenderer, &rightBar);

}

void Graphics::render() {
	// Present the renderer
	SDL_RenderPresent(mRenderer);
}

Graphics::~Graphics() {

	SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	SDL_Quit();
}

