#include <iostream>
#include <SDL.h>
#include "FrameLayer.h"
#include <algorithm>
#include "Canvas.h"
#include <map>
#include "td_util.h"

#include "CoreProgram.h"

const int CANV_WIDTH = 320;
const int CANV_HEIGHT = 240;


int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;

	SDL_Surface* screenSurface = NULL;
	
	SDL_Surface* canvSurface = NULL;

	SDL_Event e;
	bool quit = false;
	int diameter = 1;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	window = SDL_CreateWindow("Animation Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cerr << "Failed to create window! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

	//SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
	}
	//Canvas canv(renderer);
	//canv.moveCanvas((SCREEN_WIDTH / 2) - (CANV_WIDTH / 2), (SCREEN_HEIGHT / 2) - (CANV_HEIGHT / 2));
	/* ---------- MAIN LOOP ---------- */
	CoreProgram prog(CANV_WIDTH, CANV_HEIGHT, renderer);

	while (quit == false) { 
		while (SDL_PollEvent(&e)) { 
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			prog.processInput(&e);
			
			//canv.processInput(e, diameter);
		}
		// RENDER
		
		//tex = testFrame.getTexture(renderer);
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		prog.render();

		//canv.render();

		SDL_RenderPresent(renderer);	
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}