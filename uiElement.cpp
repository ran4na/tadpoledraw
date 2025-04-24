#include "uiElement.h"

uiElement::uiElement(int x, int y, int width, int height)
{
	bounding_box.x = x;
	bounding_box.y = y;
	bounding_box.w = width;
	bounding_box.h = height;
}

//this function can be overriden by internal elements
uiCallbackEvent uiElement::processEvents(SDL_Event* e)
{
	uiCallbackEvent ev;
	//iterate through internal elements, have them process the event.
	for (uiElement* i : internalElements)
	{
		ev = i->processEvents(e);
		callbackStack.push(ev);
	}


	if (internalElements.size() == 0)
	{
		return uiCallbackEvent{ UI_NONE, 0 };
	}
}

uiCallbackEvent uiElement::pollEventStack()
{
	if (callbackStack.size() > 0) {
		uiCallbackEvent ev = callbackStack.top();
		callbackStack.pop();
		return ev;
	}
	else
	{
		uiCallbackEvent ev;
		ev.type = UI_NULL;
		return ev;
	}
}

void uiElement::render(SDL_Renderer* renderer)
{
	SDL_RenderFillRect(renderer, &bounding_box);
	for (uiElement* i : internalElements)
	{
		i->render(renderer);
	}
}