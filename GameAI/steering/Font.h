#ifndef _FONT_H
#define _FONT_H

#include <iostream>
#include <string.h>
#include "DeanLib/Trackable.h"
#include "SDL2/SDL.h"
//#include "SDL_ttf.h"


class Font : public Trackable
{
private:
	//ALLEGRO_FONT* mpFont
	SDL_ttf* mpFont
	
	int mFontSize;
	friend class GraphicsSystem;

public:
	Font(std::string filename, int size);
	~Font();
	int getSize();

};

#endif 