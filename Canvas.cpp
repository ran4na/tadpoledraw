#include "Canvas.h"

Canvas::Canvas(SDL_Renderer* render)
{
	renderer = render;
	mainTimeline.setFramerate(24);
	currentFrame = mainTimeline.getFrame(0);
	frameTexture = currentFrame->getTexture(renderer);
	pan_x = 0;
	pan_y = 0;
	zoom = 1;
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = 320;
	bgRect.h = 240;
	pan_dx = 0;
	pan_dy = 0;
	currentLayer = 0;

	playing = false;
	mousedown = false;
	panning = false;
	erase = false;
}

void Canvas::updateFrameTexture()
{
	SDL_DestroyTexture(frameTexture);
	frameTexture = currentFrame->getTexture(renderer);
}

void Canvas::setFrame(unsigned int f)
{
	// getting out of bounds, create a new frame and return it.
	if (f >= mainTimeline.getLength())
	{
		mainTimeline.appendFrame();
		currentFrame = mainTimeline.getLastFrame();
	}
	else if (f < 1)
	{
		currentFrame = mainTimeline.getFirstFrame();
	}
	else
	{
		currentFrame = mainTimeline.getFrame(f);
	}
	updateFrameTexture();
}

void Canvas::render()
{
	if (playing)
	{
		updatePlayback();
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &bgRect);
	SDL_RenderCopy(renderer, frameTexture, NULL, &bgRect);
}

void Canvas::updatePlayback()
{
	float timeStep = (float)frameTimer.getTicks();
	float ms_delay = 1000.0f / (float)mainTimeline.getFramerate();
	if (timeStep >= ms_delay)
	{
		frameTimer.stop();
		if (frameCount < mainTimeline.getLength() - 1)
		{
			frameCount++;
			setFrame(frameCount);
		}
		else
		{
			frameCount = 0;
			setFrame(frameCount);
		}
		frameTimer.start();
	}
}

void Canvas::zoomCanvas(bool inout, int amount)
{
	//zoom in
	if (inout == true)
	{
		if (zoom < INT_MAX && (zoom + amount) < INT_MAX)
		{
			zoom += amount;
			bgRect.w = CANV_W * zoom;
			bgRect.h = CANV_H * zoom;
			moveCanvas(pan_x - (CANV_W / 2), pan_y - (CANV_H / 2));
		}
	}
	else
	{
		if (zoom > 1)
		{
			zoom -= amount;
			zoom = std::max(zoom, 1);
			bgRect.w = CANV_W * zoom;
			bgRect.h = CANV_H * zoom;
			moveCanvas(pan_x + (CANV_W / 2), pan_y + (CANV_H / 2));
		}
	}
}

void Canvas::moveCanvas(int x, int y)
{
	bgRect.x = x;
	bgRect.y = y;
	pan_x = x;
	pan_y = y;
}

void Canvas::clearCanvas()
{
	currentFrame->clear(currentLayer);
	updateFrameTexture();
}

void Canvas::processInput(SDL_Event* e, int diameter)
{
	if (e->type == SDL_RENDER_TARGETS_RESET)
	{
		updateFrameTexture();
	}
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_c:
			clearCanvas();
			updateFrameTexture();

			break;
		case SDLK_LEFTBRACKET:
			if (diameter > 1)
			{
				--diameter;
			}
			break;
		case SDLK_RIGHTBRACKET:
			if (diameter < INT_MAX)
			{
				++diameter;
			}
			break;
		case SDLK_PERIOD:
			zoomCanvas(true, 1);
			break;
		case SDLK_COMMA:
			zoomCanvas(false, 1);
			break;
		case SDLK_LEFT:
			if (frameCount > 0)
			{
				frameCount--;
				setFrame(frameCount);
			}
			
			break;
		case SDLK_RIGHT:
			frameCount++;
			setFrame(frameCount);
			break;

		case SDLK_RETURN:
			if (!playing)
			{
				frameTimer.start();
				playing = true;
			}
			else
			{
				frameTimer.stop();
				playing = false;
			}

			break;
		case SDLK_b:
			//switch layer
			setLayer(!currentLayer);
			break;
		default:
			break;
		}
	}
	//mouse input temporary
	else if (e->type == SDL_MOUSEMOTION || 
			e->type == SDL_MOUSEBUTTONDOWN || 
			e->type == SDL_MOUSEBUTTONUP || 
			e->type == SDL_MOUSEWHEEL)
	{
		//Get mouse pos
		Uint32 buttonState = SDL_GetMouseState(&mouse_x, &mouse_y);

		if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			if (buttonState & SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				erase = false;
				mousedown = true;
			}
			else if (buttonState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
				erase = true;
				mousedown = true;
			}
			else if (buttonState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
				panning = true;
				pan_startx = mouse_x;
				pan_starty = mouse_y;
				pan_basex = pan_x;
				pan_basey = pan_y;
				pan_dx = 0;
				pan_dy = 0;
			}
			
		}else if (e->type == SDL_MOUSEBUTTONUP)
		{
			mousedown = false;
			if (!(buttonState & SDL_BUTTON(SDL_BUTTON_MIDDLE)))
			{
				panning = false;
			}
		}
		else if (e->type == SDL_MOUSEWHEEL)
		{
			if (e->wheel.y > 0)
			{
				zoomCanvas(true, 1);
			}
			else if (e->wheel.y < 0)
			{
				zoomCanvas(false, 1);
			}
		}
	}
	if (panning)
	{
		pan_dx = mouse_x - pan_startx;
		pan_dy = mouse_y - pan_starty;
		pan_x = pan_basex + pan_dx;
		pan_y = pan_basey + pan_dy;
		
		moveCanvas(pan_x, pan_y);
	}

	// Process drawing events
	if (mousedown)
	{
		int x0 = (oldmouse_x - pan_x) / zoom;
		int y0 = (oldmouse_y - pan_y) / zoom;
		int x1 = (mouse_x - pan_x) / zoom;
		int y1 = (mouse_y - pan_y) / zoom;

		currentFrame->draw(currentLayer, erase, diameter,
			x0, y0, x1, y1);

		//refresh texture if it changed
		updateFrameTexture();
	}

	

	oldmouse_x = mouse_x;
	oldmouse_y = mouse_y;

}
