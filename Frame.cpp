#include "Frame.h"

void Frame::draw(uint8_t active_layer, bool erase, int diameter, int x0, int y0, int x1, int y1)
{
	layers[active_layer].drawLine(x0, y0, x1, y1, erase, diameter);

}

SDL_Texture* Frame::getTexture(SDL_Renderer* renderer)
{
	SDL_Texture* tex1 = layers[0].getTexture(renderer);
	SDL_Texture* tex2 = layers[1].getTexture(renderer);

	SDL_Texture* final_tex = SDL_CreateTexture(renderer, 
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 320, 240);
	//blit to one texture
	SDL_SetRenderTarget(renderer, final_tex);
	SDL_RenderCopy(renderer, tex1, NULL, NULL);
	SDL_RenderCopy(renderer, tex2, NULL, NULL);
	SDL_SetTextureBlendMode(final_tex, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, NULL); //NULL SETS TO DEFAULT

	SDL_DestroyTexture(tex1);
	SDL_DestroyTexture(tex2);

	return final_tex;
}

void Frame::setColor(uint8_t active_layer, uint8_t color)
{
	layers[active_layer].setColor(color);
}
