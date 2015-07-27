//============================================================================
// Name        : SDLViewport.cpp
// Author      : anthemEdge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include "Graphics.h"
#include "Ball.h"
using namespace std;

int main() {
	srand(time(NULL)); // Time seeded randomness
	Ball ball(SDL_GetTicks());
	int userInput;
	int aiInput;

	// Start up graphics
	bool userQuit = false;
	Graphics graphics;
	userQuit = !graphics.init();

	while (!userQuit) {
		// Dealing with user inputs
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				userQuit = true;
			} else if (event.type == SDL_MOUSEMOTION) {
				// Get mouse motion inputs
				int x;
				SDL_GetMouseState(&x, &userInput);

				// minor corrections
				if (userInput > Graphics::SCREEN_HEIGHT - Ball::BAR_Length) {
					userInput = Graphics::SCREEN_HEIGHT - Ball::BAR_Length;
				}
			}
		}
		// Small delay for ball to move
		SDL_Delay(10);

		// AI
		aiInput += (ball.mPosY - aiInput) * 0.8;
		// minor corrections to AI
		if (aiInput > Graphics::SCREEN_HEIGHT - Ball::BAR_Length) {
			aiInput = Graphics::SCREEN_HEIGHT - Ball::BAR_Length;
		}

		ball.update(SDL_GetTicks(), userInput, aiInput);
		graphics.clear();
		graphics.draw(&ball, userInput, aiInput);
		graphics.render();

	}

	return 0;
}
