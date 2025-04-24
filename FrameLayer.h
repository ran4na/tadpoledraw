#pragma once
#include <cstdint>
#include <SDL.h>
#include <iostream>

class FrameLayer
{
public:
	FrameLayer()
	{
		m_color = 0;
		clear();
	};
	FrameLayer(uint8_t color)
	{
		m_color = color;
		clear();
	};

	uint8_t getColor() { return m_color; };
	void setColor(uint8_t color) { m_color = color; };

	void setPixel(unsigned int x, unsigned int y, bool erase);
	void drawLine(int x1, int y1, int x2, int y2, bool erase, unsigned int diameter);

	void stampCircle(int x, int y, unsigned int diameter, bool erase);

	void clear()
	{
		for (int i = 0; i < 9600; ++i)
		{
			m_pixels[i] = 0b00000000;
		}
	};

	SDL_Texture* getTexture(SDL_Renderer* renderer);

private:
	uint8_t m_color; // 0: black, 1: red, 2: blue
	uint8_t m_pixels[9600]; // (320 * 240)/8 = 9600 chars (9.6kb)
	//uint8_t m_img[76800];
};

