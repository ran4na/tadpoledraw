#pragma once
#include <SDL.h>
#include <iostream>
#include <stack>
#include <variant>
#include <vector>

// uiElement.cpp
typedef enum {
	UI_NULL,
	UI_NONE,
	UI_CANVAS_ZOOM,
	UI_CANVAS_PAN,
	UI_TIMELINE_SETFRAME,
	UI_TIMELINE_DELETEFRAME,
	UI_TIMELINE_ADDFRAME
} UICallbackType;
// UI callback event union holds a type and a value (or no value for certain events, if needed.)
struct uiCallbackEvent
{
public:
	UICallbackType type;

	std::variant<int, float, const char*, std::monostate> value;
};

class uiElement
{
public:
	uiElement(int x, int y, int width, int height);

	virtual uiCallbackEvent processEvents(SDL_Event* e);

	uiCallbackEvent pollEventStack();

	//std::stack<uiCallbackEvent> getCallbacks();
	virtual void render(SDL_Renderer* renderer);
protected:
	SDL_Rect bounding_box;
	std::vector<uiElement*> internalElements;
	std::stack<uiCallbackEvent> callbackStack;
};

