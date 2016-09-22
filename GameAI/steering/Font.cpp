#include "font.h"

Font::Font(std::string filename, int size)
{
	if (TTF_Init() < 0)
	std::cout << TTF_GetError();

	mFontSize = size;
	mpFont = TTF_OpenFont(filename.c_str(), mFontSize);
	if (mpFont == NULL)
	{
		std::cout << TTF_GetError();
	}
	//mpFont = al_load_ttf_font(filename.c_str(), mFontSize, 0);
}
Font::~Font()
{
	//al_destroy_font(mpFont);
}

int Font::getSize()
{
	return mFontSize;
}