#include <allegro5/allegro.h>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"

GraphicsSystem::GraphicsSystem()
	:mpDisplay(NULL)
	,mpBackBuffer(NULL)
	,mWidth(0)
	,mHeight(0)
{
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

bool GraphicsSystem::init( int width, int height )
{
	mWidth = width;
	mHeight = height;
	mpDisplay = al_create_display(width, height);
	if(!mpDisplay) 
	{
		fprintf(stderr, "GraphicsSystem::failed to create display!\n");
		return false;
	}
		
	//get the backbuffer
	ALLEGRO_BITMAP* pBackBuffer = al_get_backbuffer( mpDisplay );

	//set the back buffer as the target bitmap
	al_set_target_bitmap( pBackBuffer );

	//create the GraphicsBuffer backbuffer
	mpBackBuffer = new GraphicsBuffer( pBackBuffer );

	//al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, al_map_rgb(255,255,255));

	return true;
}

void GraphicsSystem::cleanup()
{
	al_destroy_display( mpDisplay );
	mpDisplay = NULL;

	mpBackBuffer->invalidate();
	delete mpBackBuffer;
	mpBackBuffer = NULL;
}

void GraphicsSystem::swap()
{
	al_flip_display();
}

void GraphicsSystem::wrapCoordinates( Vector2D& vector )
{
	if( vector.getX() < 0.0f )
	{
		vector.setX( getWidth() - 1.0f );
	}
	else if( vector.getX() >= getWidth() )
	{
		vector.setX( 0.0f );
	}

	if( vector.getY() < 0.0f )
	{
		vector.setY( getHeight() - 1.0f );
	}
	else if( vector.getY() >= getHeight() )
	{
		vector.setY( 0.0f );
	}
}

//static function
ALLEGRO_BITMAP* GraphicsSystem::switchTargetBitmap( ALLEGRO_BITMAP* pNewTarget )
{
	//get old target bitmap
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	//set dest to be the target
	al_set_target_bitmap( pNewTarget );

	return pOldTarget;
}

void GraphicsSystem::drawText(ALLEGRO_FONT* pFont, int r, int g, int b, float x, float y, int flags, const char* text)
{
	//al_draw_text(mpFont, al_map_rgb(255, 255, 255), mMouseState.x, mMouseState.y, ALLEGRO_ALIGN_CENTRE, mMousePos.str().c_str());
	al_draw_text(pFont, al_map_rgb(r, g, b), x, y, flags, text);
}

//this function manually sets the lines of debug text at different heights so they do not overlap
//this is because allegro's draw text function doesn't support new line characters
void GraphicsSystem::drawDebugText(ALLEGRO_FONT* pFont, int r, int g, int b, float x, float y, int flags, float vel, float radius, float rotVel, float accel, float alignment, float cohesion, float seperation)
{
	std::string draw = "[V] Enemy Max Velocity: " + std::to_string(vel);
	if (gpGame->getCurrProperty() == MAX_VELOCITY)
		drawText(pFont, 0, 0, 0, x, y, ALLEGRO_ALIGN_LEFT, draw.c_str());
	else
		drawText(pFont, r, g, b, x, y, ALLEGRO_ALIGN_LEFT, draw.c_str());

	draw = "[R] Reaction Radius: " + std::to_string(radius);
	if (gpGame->getCurrProperty() == REACTION_RADIUS)
		drawText(pFont, 0, 0, 0, x, y + 25, ALLEGRO_ALIGN_LEFT, draw.c_str());
	else
		drawText(pFont, r, g, b, x, y + 25, ALLEGRO_ALIGN_LEFT, draw.c_str());

	draw = "[O] Max Rotational Velocity: " + std::to_string(rotVel);
	if (gpGame->getCurrProperty() == ROTATIONAL_VELOCITY)
		drawText(pFont, 0, 0, 0, x, y + 50, ALLEGRO_ALIGN_LEFT, draw.c_str());
	else
		drawText(pFont, r, g, b, x, y + 50, ALLEGRO_ALIGN_LEFT, draw.c_str());

	draw = "[M] Enemy Max Acceleration: " + std::to_string(accel);
	if (gpGame->getCurrProperty() == MAX_ACCELERATION)
		drawText(pFont, 0, 0, 0, x, y + 75, ALLEGRO_ALIGN_LEFT, draw.c_str());
	else
		drawText(pFont, r, g, b, x, y + 75, ALLEGRO_ALIGN_LEFT, draw.c_str());

	draw = "[A] Alignment Weight: " + std::to_string(alignment);
	if (gpGame->getCurrProperty() == ALIGNMENT_WEIGHT)
		drawText(pFont, 0, 0, 0, x, y + 100, ALLEGRO_ALIGN_LEFT, draw.c_str());
	else
		drawText(pFont, r, g, b, x, y + 100, ALLEGRO_ALIGN_LEFT, draw.c_str());

	draw = "[C] Cohesion Weight: " + std::to_string(cohesion);
	if (gpGame->getCurrProperty() == COHESION_WEIGHT)
		drawText(pFont, 0, 0, 0, x, y + 125, ALLEGRO_ALIGN_LEFT, draw.c_str());
	else
		drawText(pFont, r, g, b, x, y + 125, ALLEGRO_ALIGN_LEFT, draw.c_str());

	draw = "[S] Seperation Weight: " + std::to_string(seperation);
	if (gpGame->getCurrProperty() == SEPERATION_WEIGHT)
		drawText(pFont, 0, 0, 0, x, y + 150, ALLEGRO_ALIGN_LEFT, draw.c_str());
	else
		drawText(pFont, r, g, b, x, y + 150, ALLEGRO_ALIGN_LEFT, draw.c_str());
}