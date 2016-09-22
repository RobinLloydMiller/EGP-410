//used with permission from Lucas Spiker

#ifndef _GRAPHICSSYSTEM_H
#define _GRAPHICSSYSTEM_H

#include<SDL2/SDL.h>

//#include "SDL_ttf.h"
#include "GraphicsBuffer.h"
#include "DeanLib/Vector2D.h"
#include "Sprite.h"
#include "Font.h"

#include <iostream>

#include "DeanLib/Trackable.h"

class GraphicsSystem: public Trackable
{
public:
	void initialize(int width, int height);
	void cleanup();
	void draw(GraphicsBuffer* buffer, Vector2D loc, Sprite* sprite, float scale);
	void draw(Vector2D loc, Sprite* sprite, float scale);
	void flipDisplay();
	//void writeText(GraphicsBuffer* buffer, Vector2D loc, const Font& font, Color color, const std::string& text);
	void writeText(Vector2D loc, Font* font, Color color, std::string text);
	int getHeight();
	int getWidth();
	GraphicsBuffer* getBackBuffer();
	GraphicsSystem();
	~GraphicsSystem();

private:
	SDL_Window* mpDisplay;
	SDL_Surface* mpSurface;
	GraphicsBuffer* mpBuffer;
	int mWidth, mHeight;
};

#endif