/*
 * Graphics.cpp
 *
 *  Created on: 26 Jul 2015
 *      Author: eva
 */

#include "Graphics.h"

Graphics::Graphics() :
		mWindow(NULL), mRenderer(NULL), mFont(NULL) {
}

bool Graphics::init() {
	bool success = true;

	// SDL System Initialisation
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		success = false;
		printf("SDL unable to initialise! SDL Error: %s. \n", SDL_GetError());
	}

	// SDL true front
	if (TTF_Init() == -1) {
		success = false;
		printf("SDL_ttf unable to initialise! SDL_ttf Error: %s. \n",
		TTF_GetError);
	}

	// Load front
	if (success) {
		mFont = TTF_OpenFont("assets/FFFFORWA.TTF", 16);
		if (mFont == NULL) {
			success = false;
			printf("Unable to load font %s! SDL_ttf Error: %s. \n",
					"assets/FFFFORWA.TTF", TTF_GetError);
		}
	}

	// Create and Present a Window
	if (success) {
		mWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED,
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

bool Graphics::showText(int x, int y, string text, bool middle) {
	bool success = true;
	SDL_Texture* textTexture;
	SDL_Color white = { 0xFF, 0xFF, 0xFF };
	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text.c_str(),
			white);
	if (textSurface == NULL) {
		success = false;
		printf("Unable to create surface from text! SDL_ttf Error: %s.\n",
		TTF_GetError);
	}

	if (success) {
		textTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (textTexture == NULL) {
			printf(
					"Unable to convert text surface to texture! SDL Error: %s.\n",
					SDL_GetError());
			success = false;
		}
	}

	if (success) {
		// Create SDL_Rect for texture
		SDL_Rect target;
		if (middle) {
			target.x = (SCREEN_WIDTH - textSurface->w) / 2;
		} else {
			target.x = x;
		}
		target.y = y;
		target.h = textSurface->h;
		target.w = textSurface->w;

		// Add to Render
		SDL_RenderCopy(mRenderer, textTexture, NULL, &target);

		// Free surface
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}

	return success;
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

