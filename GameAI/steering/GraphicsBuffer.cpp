//used with permission from Lucas Spiker

#include "GraphicsBuffer.h"

int GraphicsBuffer::getHeight()
{
	return mpBitmap->h;
}

int GraphicsBuffer::getWidth()
{
	return mpBitmap->w;
}

GraphicsBuffer::GraphicsBuffer(std::string path)
{
	mpBitmap = IMG_Load(path.c_str());

	if (mpBitmap == NULL)
	{
		std::cout << IMG_GetError() << std::endl;
	}
}

GraphicsBuffer::GraphicsBuffer(int width, int height, Color color = Color(0, 0, 0))
{
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	mpBitmap = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);

	SDL_FillRect(mpBitmap, NULL, SDL_MapRGB(mpBitmap->format, color.getR(), color.getG(), color.getB()));
	
	if (mpBitmap == NULL)
	{
		"image is null\n";
	}
}

GraphicsBuffer::GraphicsBuffer(SDL_Surface* map, bool displayMap = false)
{
	mpBitmap = map;
	mDisplayMap = displayMap;
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (!mDisplayMap)
	{
		SDL_FreeSurface(mpBitmap);
	}
}