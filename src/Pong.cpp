//============================================================================
// Name        : SDLViewport.cpp
// Author      : anthemEdge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include <sstream>
#include "Graphics.h"
#include "Ball.h"
using namespace std;

int main() {
	srand(time(NULL)); // Time seeded randomness
	Ball ball(SDL_GetTicks());
	ball.setGap(Graphics::GAP);
	int scoreLim = 10;

	// Initial variables
	int userInput = 0;
	int aiInput = 0;
	int userScore = 0;
	int aiScore = 0;
	bool paues = true;
	bool newGame = false;

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
			} else if (event.type == SDL_KEYDOWN) {
				// Unpaues by player
				switch (event.key.keysym.sym) {
				case SDLK_SPACE:
					paues = false;
					if (newGame) {
						userScore = 0;
						aiScore = 0;
						newGame = false;
					}
					ball.newBall(SDL_GetTicks());
					break;
				case SDLK_q:
					userQuit = true;
					break;
				}

			}
		}
		// Small delay for ball to move
		SDL_Delay(10);

		// AI
		aiInput += (ball.mPosY - Ball::BAR_Length / 2 - aiInput) * 0.15;
		// Perfect AI
		//aiInput = ball.mPosY - Ball::BAR_Length / 2;
		// minor corrections to AI
		if (aiInput > Graphics::SCREEN_HEIGHT - Ball::BAR_Length) {
			aiInput = Graphics::SCREEN_HEIGHT - Ball::BAR_Length;
		}
		if (aiInput < 0) {
			aiInput = 0;
		}

		// If game paues
		if (!paues) {
			paues = ball.update(SDL_GetTicks(), userInput, aiInput);
			if (paues) {
				if (ball.leftWon()) {
					userScore++;
				} else {
					aiScore++;
				}

				ball.newBall(SDL_GetTicks());
			}

		}
		graphics.clear();
		stringstream scores;
		scores << userScore;
		scores << " : ";
		scores << aiScore;

		graphics.showText(200, 50, scores.str().c_str());
		graphics.draw(&ball, userInput, aiInput);
		// When the game is paused
		if (paues) {
			graphics.showText(200, 400, "Press [SPACE] to Start");
			graphics.showText(200, 440, "Press [Q] to Quit");
			if (userScore == scoreLim || aiScore == scoreLim) {
				newGame = true;
				string name;
				if (userScore == scoreLim) {
					name = "Player";
				} else {
					name = "AI";
				}

				stringstream winner;
				winner << "-- ";
				winner << name;
				winner << " Wins!";
				winner << " --";
				if (paues) {
					graphics.showText(200, 260, winner.str().c_str());
				}

			}
		}

		graphics.render();

	}

	return 0;
}
