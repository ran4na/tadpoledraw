#pragma once
#include "Frame.h"
#include "Timeline.h"
#include "LTimer.h"

class Canvas
{
public:
	Canvas(SDL_Renderer* render);

	void processInput(SDL_Event* e, int diameter);


	void setRenderer(SDL_Renderer* render) { renderer = render; };

	void updateFrameTexture();

	void setFrame(unsigned int f);

	void render();

	void updatePlayback();

	void zoomCanvas(bool inout, int amount);
	void moveCanvas(int x, int y);

	void clearCanvas();

	void setLayer(bool layer) { currentLayer = layer; };

private:
	Timeline mainTimeline;

	Frame* currentFrame;
	unsigned int frameCount = 0;

	int zoom;
	int pan_x, pan_y;
	bool mousedown;
	bool erase;
	bool panning;
	bool currentLayer;

	bool playing;
	LTimer frameTimer;

	int pan_basex = 0, pan_basey = 0;
	int pan_startx = 0, pan_starty = 0;
	int pan_dx, pan_dy;

	SDL_Texture* frameTexture;

	SDL_Renderer* renderer;

	SDL_Rect bgRect;

	const int CANV_W = 320, CANV_H = 240;

	int mouse_x = 0, mouse_y = 0, oldmouse_x = 0, oldmouse_y = 0;
};

