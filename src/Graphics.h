/*
 * Graphics.h
 *
 *  Created on: 26 Jul 2015
 *      Author: eva
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Ball.h"

using namespace std;

class Graphics {
public:
	const static int SCREEN_WIDTH = 640;
	const static int SCREEN_HEIGHT = 480;
	const static int GAP = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;

	const static int BAR_LENGTH = 144;
	const static int BAR_WIDTH = 64;

public:
	Graphics();
	bool init();

	void clear();
	void draw(Ball* ball, int barLeftPos = 0, int barRightPos = 0);
	void render();

	bool showText(int x, int y, string text, bool middle = true);

	virtual ~Graphics();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	TTF_Font* mFont;
};

#endif /* GRAPHICS_H_ */
