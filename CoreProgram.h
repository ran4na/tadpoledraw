#pragma once
#include <SDL.h>
#include "canvas.h"
#include "uiElement.h"
#include "td_util.h"

class CoreProgram
{
public:
	CoreProgram(int width, int height, SDL_Renderer* rend);

	void update(SDL_Event* e);

	void processGUIEvents(SDL_Event* e);

	void processInput(SDL_Event* e);

	void render();
private:
	int canv_width;
	int canv_height;
	
	//brush diameter
	int diameter;

	Canvas main_canvas;
	uiElement main_ui;

	SDL_Renderer* renderer;
};

