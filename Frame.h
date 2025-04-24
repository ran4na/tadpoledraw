#pragma once
#include "FrameLayer.h"

class Frame
{
public:
	Frame() {
		layers[0].setColor(0);
		layers[1].setColor(1);
	}
	Frame(uint8_t color0, uint8_t color1) {
		layers[0].setColor(color0);
		layers[1].setColor(color1);
	}

	~Frame() = default;
	//handles all drawing
	void draw(uint8_t active_layer, bool erase, int diameter, int x0, int y0, int x1, int y1);

	void clear(uint8_t active_layer) { layers[active_layer].clear(); };

	SDL_Texture* getTexture(SDL_Renderer* renderer);

	void setColor(uint8_t active_layer, uint8_t color);
	uint8_t getColor(uint8_t active_layer) { return layers[active_layer].getColor(); };
private:
	FrameLayer layers[2];
};

