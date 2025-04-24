#include "FrameLayer.h"
#include <iostream>
#include <math.h>
#include <algorithm>

void FrameLayer::setPixel(unsigned int x, unsigned int y, bool erase)
{
	int px = std::max(0, std::min((int)x, 319));
	int py = std::max(0, std::min((int)y, 239));
	unsigned int idx = px + (py * 320);
	if (!erase)
	{
		m_pixels[idx / 8] |= (1 << (idx % 8));
	}
	else
	{
		m_pixels[idx / 8] &= ~(1 << (idx % 8));
	}
	
}


void FrameLayer::drawLine(int mx1, int my1, int mx2, int my2, bool erase, unsigned int diameter)
{
	int x1 = mx1, y1 = my1, x2 = mx2, y2 = my2;
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));

	if(steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	const float dx = (float)x2 - (float)x1;
	const float dy = (float)fabs(y2 - y1);
	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;
	const int maxX = (int)x2;


	for (int x = (int)x1; x <= maxX; x++)
	{
		if (steep)
		{
			if (diameter == 1)
			{
				setPixel(y, x, erase);
			}
			else
			{
				stampCircle(y, x, diameter, erase);
			}
			
		}
		else
		{
			if (diameter == 1)
			{
				setPixel(x, y, erase);
			}
			else
			{
				stampCircle(x, y, diameter, erase);
			}
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void FrameLayer::stampCircle(int x, int y, unsigned int diameter, bool erase)
{
	int r = diameter / 2;
	for (int w = 0; w < r * 2; w++)
    {
        for (int h = 0; h < r * 2; h++)
        {
            int dx = r - w; // horizontal offset
            int dy = r - h; // vertical offset
            if ((dx*dx + dy*dy) <= (r * r))
            {
				setPixel(x + dx, y + dy, erase);
			}
        }
    }

}


SDL_Texture* FrameLayer::getTexture(SDL_Renderer* renderer)
{
	if (renderer == nullptr) {
		std::cerr << "Renderer is null, cannot create texture." << std::endl;
		return nullptr;
	}

	unsigned int t_length = 240;
	unsigned int t_width = 320;

	SDL_Texture* texture = SDL_CreateTexture(renderer,
									SDL_PIXELFORMAT_ABGR8888,
									SDL_TEXTUREACCESS_STREAMING,
									320,
									240);
	if (texture == nullptr) {
		std::cerr << "SDL_CreateTexture failed: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	uint8_t* pixels = nullptr;
	int pitch  = 0;

	if (SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch) != 0) {
		std::cerr << "SDL_LockTexture failed: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(texture);
		return nullptr;
	}
	unsigned int color[2] = { 0, 0 };

	if (pixels == nullptr) {
		return nullptr;
	}

	// set color pallete, 0: black, 1: red, 2: blue
	if (m_color > 0 && m_color < 3)
	{
		color[m_color - 1] = 255;
	}

	int img_size = t_length * t_width;

	int m_len = sizeof(m_pixels) / sizeof(m_pixels[0]);


	for (int i = 0; i < img_size; i++)
	{
		int bit_idx = i / 8;
		int bit_offset = i % 8;
		if (m_pixels[bit_idx] & (1 << bit_offset))
		{
			pixels[i * 4] = color[0]; // R
			pixels[i * 4 + 1] = 0;		// G
			pixels[i * 4 + 2] = color[1]; // B
			pixels[i * 4 + 3] = 255;	// A
		}
		else
		{
			pixels[i * 4] = 0;
			pixels[i * 4 + 1] = 0;
			pixels[i * 4 + 2] = 0;
			pixels[i * 4 + 3] = 0;
		}
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_UnlockTexture(texture);

	return texture;
}

	