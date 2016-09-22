#ifndef _SPRITEMANAGER_H
#define _SPRITEMANAGER_H

#include "DeanLib/Trackable.h"
#include "DeanLib/Defines.h"
#include <map>

class Sprite;
class GraphicsBuffer;

class SpriteManager: public Trackable
{
public:
	SpriteManager();
	~SpriteManager();

	Sprite* createAndManageSprite( const IDType& id, GraphicsBuffer* pBuffer, float sx, float sy, float sw, float sh );
	Sprite* getSprite( const IDType& id );
	void destroySprite( const IDType& id );

private:
	std::map<IDType,Sprite*> mpSprites;
};

#endif