#include "CoreProgram.h"

CoreProgram::CoreProgram(int width, int height, SDL_Renderer* rend) 
	: main_canvas(rend), main_ui(0, 0, width, height)
{
	canv_height = height;
	canv_width = width;
	renderer = rend;
	diameter = 1;
	main_canvas.moveCanvas((SCREEN_WIDTH / 2) - (width/ 2), (SCREEN_HEIGHT / 2) - (height / 2));
}

void CoreProgram::update(SDL_Event* e)
{
	processInput(e);
	processGUIEvents(e);
}

void CoreProgram::processGUIEvents(SDL_Event* e)
{
	//uiCallbackEvent ue = main_ui.processEvents(e);
	
	//poll UI events until UI_NONE is returned
	for (uiCallbackEvent ue; ue.type != UI_NONE; ue = main_ui.processEvents(e))
	{
		switch (ue.type)
		{
		case UI_CANVAS_ZOOM:
			main_canvas.zoomCanvas(true, std::get<int>(ue.value));
			break;
		default:
			break;
		}
	}

	
}



void CoreProgram::processInput(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_LEFTBRACKET:
			diameter /= 2;
			if (diameter < 1)
			{
				diameter = 1;
			}
			break;
		case SDLK_RIGHTBRACKET:
			if (diameter < 480)
			{
				diameter *= 2;
			}

			break;
		default:
			break;
		}
	}
	processGUIEvents(e);
	main_canvas.processInput(e, diameter);
}

void CoreProgram::render()
{
	main_canvas.render();
}
