#include "Timeline.h"

Timeline::Timeline()
{
	framerate = 12;
	frames.push_back(new Frame);
}

Timeline::Timeline(uint8_t fps)
{
	framerate = fps;
}

Frame* Timeline::getFrame(unsigned int f)
{
	if (f >= getLength())
	{
		return frames.back();
	}
	else
	{
		return frames.at(f);
	}
}

void Timeline::appendFrame()
{
	uint8_t colors[2] = { frames.back()->getColor(0), frames.back()->getColor(1) };
	frames.push_back(new Frame(colors[0], colors[1]));
}

void Timeline::insertFrame(unsigned int f)
{
	if (f >= getLength())
	{
		appendFrame();
	}
	else
	{
		uint8_t colors[2] = { frames.at(f)->getColor(0), frames.at(f)->getColor(1) };
		frames.insert(frames.begin() + f, new Frame(colors[0], colors[1]));
	}
}

void Timeline::removeFrame(unsigned int f)
{
	if (f >= getLength())
	{
		frames.pop_back();
	}
	else
	{
		frames.erase(frames.begin() + f);
	}
}

