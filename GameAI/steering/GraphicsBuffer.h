//used with permission from Lucas Spiker

#ifndef _GRAPHICSBUFFER_H
#define _GRAPHICSBUFFER_H

#include <SDL2/SDL.h>
//#include "SDL_image.h"
#include "Color.h"
#include <string>

#include "DeanLib/Trackable.h"

class GraphicsBuffer: public Trackable
{
public:
	int getHeight();
	int getWidth();
	GraphicsBuffer(std::string path);
	GraphicsBuffer(int width, int height, Color color);
	~GraphicsBuffer();

private:
	friend class GraphicsSystem;
	GraphicsBuffer(SDL_Surface* map, bool displayMap);

	bool mDisplayMap;
	SDL_Surface* mpBitmap = new SDL_Surface();

};

#endif