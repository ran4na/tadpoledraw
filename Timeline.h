#pragma once
#include "Frame.h"
#include <vector>

class Timeline
{
public:
	Timeline();
	Timeline(uint8_t fps);
	uint8_t getFramerate() { return framerate; };

	Frame* getFrame(unsigned int f);
	unsigned int getLength() { return (unsigned int)frames.size(); };
	void setFramerate(uint8_t f) { framerate = f; };

	void appendFrame();
	void insertFrame(unsigned int f);
	void removeFrame(unsigned int f);

	Frame* getLastFrame() { return frames.back(); };
	Frame* getFirstFrame() { return frames.front(); };

private:
	std::vector<Frame*> frames;
	uint8_t framerate;
};

