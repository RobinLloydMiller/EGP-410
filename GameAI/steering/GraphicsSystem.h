#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "Trackable.h"
#include "Vector2D.h"

class GraphicsBuffer;

class GraphicsSystem:public Trackable
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	bool init( int width, int height );
	void cleanup();

	void swap();
	void wrapCoordinates( Vector2D& vector );//change the x and y values in the vector to keep them on the visible screen

	//accessors
	int getWidth() const { return mWidth; };
	int getHeight() const { return mHeight; };
	ALLEGRO_DISPLAY* getDisplay() const { return mpDisplay; };
	inline GraphicsBuffer* getBackBuffer() { return mpBackBuffer; };

	static ALLEGRO_BITMAP* switchTargetBitmap( ALLEGRO_BITMAP* pNewTarget );//return old target
	static void drawText(ALLEGRO_FONT* pFont, int r, int g, int b, float x, float y, int flags, const char* text);
	static void drawDebugText(ALLEGRO_FONT* pFont, int r, int g, int b, float x, float y, int flags, float vel, float radius, float rotVel, float accel);

private:
	ALLEGRO_DISPLAY* mpDisplay;
	GraphicsBuffer* mpBackBuffer;
	int mWidth;
	int mHeight;
};