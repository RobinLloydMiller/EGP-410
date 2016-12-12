#ifndef _LEVEL_H
#define _LEVEL_H

/* Some code reused from/inspired by http://usefulgamedev.weebly.com/c-tiled-map-loader.html */

#include "Trackable.h"
#include "../tinyxml/tinyxml.h"
#include "TileLayer.h"
#include "Tile.h"
#include "SpriteSheet.h"
#include "sprite.h"
#include "graphicsSystem.h"
//#include "CollisionBoxManager.h"
#include <string>
#include <vector>

class Level: public TiXmlVisitor, public Trackable
{
public:
	Level(std::string path);
	~Level();

	Tile* getTile(int x, int y, std::string layer);
	void getTileSize(int &width, int &height);
	void draw(GraphicsSystem* gs);
	void getLevelSize(int &width, int &height);
	std::string getPath(){ return mPath; };
	Vector2D getSpawnLoc(){ return mSpawnLoc; };
	//CollisionBoxManager* getBoxManager(){ return mpBoxManager; };

private:
	std::vector<TileLayer*> mLayers;
	std::vector<SpriteSheet*> mSheets;
	std::vector<Sprite*> mTileSprites;
	std::string mPath;
	TiXmlDocument mMap;
	int mWidth, mHeight;
	int mTileWidth, mTileHeight;
	Vector2D mSpawnLoc;

	//CollisionBoxManager* mpBoxManager;

	virtual bool VisitEnter(const TiXmlDocument  &);
	virtual bool VisitExit(const TiXmlDocument &);
	virtual bool VisitEnter(const TiXmlElement &, const TiXmlAttribute *);
	/*virtual bool VisitExit(const TiXmlElement &);
	virtual bool Visit(const TiXmlDeclaration &);
	virtual bool Visit(const TiXmlText &);
	virtual bool Visit(const TiXmlComment &);
	virtual bool Visit(const TiXmlUnknown &);*/
};

#endif