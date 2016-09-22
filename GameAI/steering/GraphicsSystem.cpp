//used with permission from Lucas Spiker

#include "GraphicsSystem.h"

void GraphicsSystem::initialize(int width, int height)
{
	

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "didn't init sdl\n\n ";
		std::cout << SDL_GetError() << "\n\n\n\n\n\n\n\n\n";
		return;
	}

	if (TTF_Init() < 0)
	{
		std::cout << "didn't init sdl_ttf\n\n ";
		std::cout << TTF_GetError() << "\n\n\n\n\n\n\n\n\n";
		return;
	}

	mpDisplay = SDL_CreateWindow("final project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (mpDisplay == NULL)
		std::cout << "failed to make display\n";
	else
	{
		//Get window surface
		mpSurface = SDL_GetWindowSurface(mpDisplay);

		

		//Fill the surface cornflower blue
		SDL_FillRect(mpSurface, NULL, SDL_MapRGB(mpSurface->format, 0x64, 0x95, 0xED));

		//Update the surface
		SDL_UpdateWindowSurface(mpDisplay);

	}


	//ALLEGRO_BITMAP* map = al_get_backbuffer(mpDisplay);
	//mpBuffer = new GraphicsBuffer(map, true);
}

void GraphicsSystem::cleanup()
{
	delete mpBuffer;
}

int GraphicsSystem::getHeight()
{
	SDL_GetWindowSize(mpDisplay, &mWidth, &mHeight);

	return mHeight;
}

int GraphicsSystem::getWidth()
{
	SDL_GetWindowSize(mpDisplay, &mWidth, &mHeight);

	return mWidth;
}

GraphicsBuffer* GraphicsSystem::getBackBuffer()
{
	return mpBuffer;
}

void GraphicsSystem::draw(Vector2D loc, Sprite* sprite, float scale = 1.0f)
{
	draw(getBackBuffer(), loc, sprite, scale);
}

void GraphicsSystem::flipDisplay()
{
	SDL_UpdateWindowSurface(mpDisplay);
}

void GraphicsSystem::draw(GraphicsBuffer* buffer, Vector2D loc, Sprite* sprite, float scale = 1.0f)
{
	SDL_Rect* drect = new SDL_Rect();
	SDL_Rect* srect = new SDL_Rect();
	drect->x = (int)loc.getX();
	drect->y = (int)loc.getY();
	srect->x = (int)sprite->getLoc().getX();
	srect->y = (int)sprite->getLoc().getY();
	srect->h = sprite->getHeight();
	srect->w = sprite->getWidth();

	if (sprite->getBuffer()->mpBitmap == NULL)
		std::cout << "buffer is null" << std::endl;

	SDL_BlitSurface(sprite->getBuffer()->mpBitmap, srect, mpSurface, drect);
}

void GraphicsSystem::writeText(Vector2D loc, Font* font, Color color, std::string text)
{
	int textW, textH;

	if (font->mpFont == NULL)
		std::cout << "\nfont is null\n";

	TTF_SizeText(font->mpFont, text.c_str(), &textW, &textH);

	SDL_Rect* drect = new SDL_Rect();
	drect->x = (int)loc.getX();
	drect->y = (int)loc.getY(); 

	drect->h = (int)(getHeight() + textH) / 2;
	drect->w = (int)(getWidth() + textW) / 2;


	SDL_Color meme = { color.getR(), color.getG(), color.getB() };
	if (font->mpFont == NULL)
		std::cout << "font is null";
	SDL_Surface* temp;
	if (!(temp = TTF_RenderText_Solid(font->mpFont, text.c_str(), meme)))
	{
		std::cout << TTF_GetError();
	}
	SDL_BlitSurface(temp, NULL, mpSurface, drect);
}

//void GraphicsSystem::writeText(GraphicsBuffer* buffer, Vector2D loc, const Font& font, Color color, const std::string& text)
//{
//	/*al_set_target_bitmap(buffer->mpBitmap);
//	writeText(loc, font, color, text);
//	al_set_target_bitmap(al_get_backbuffer(mpDisplay));*/
//}

GraphicsSystem::GraphicsSystem()
{
	mpDisplay = NULL;
	mpSurface = NULL;
}

GraphicsSystem::~GraphicsSystem()
{
	//cleanup();
	SDL_DestroyWindow(mpDisplay);
	SDL_Quit();
}