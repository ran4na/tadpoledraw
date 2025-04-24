#pragma once
#include "uiElement.h"
class uiButton : public uiElement
{
public:
	uiButton(int x, int y, int width, int height, std::string btntext, uiCallbackEvent onClick);

	//virtual void render(SDL_Renderer* renderer) override;

	//virtual void processEvents(SDL_Event* e) override;

private:
	std::string text;

};

