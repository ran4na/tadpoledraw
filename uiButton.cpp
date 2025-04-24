#include "uiButton.h"

uiButton::uiButton(int x, int y, int width, int height, std::string btntext, uiCallbackEvent onClick)
	: uiElement(x, y, width, height)
{
	uiElement::bounding_box.x = x;
	uiElement::bounding_box.y = y;
	uiElement::bounding_box.w = width;
	uiElement::bounding_box.h = height;
	text = btntext;
}
