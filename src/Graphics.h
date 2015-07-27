/*
 * Graphics.h
 *
 *  Created on: 26 Jul 2015
 *      Author: eva
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL.h>
#include <string>
#include "Ball.h"


using namespace std;

class Graphics {
public:
	const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 720;

	const static int BAR_LENGTH = 144;
	const static int BAR_WIDTH = 64;

public:
	Graphics();
	bool init();

	void clear();
	void draw(Ball* ball, int barLeftPos = 0, int barRightPos = 0);
	void render();

	virtual ~Graphics();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
};

#endif /* GRAPHICS_H_ */
