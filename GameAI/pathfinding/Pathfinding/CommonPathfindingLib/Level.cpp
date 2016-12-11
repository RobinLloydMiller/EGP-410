#include "Level.h"
#include "Game.h"

Level::Level(std::string path)
{
	//mpBoxManager = new CollisionBoxManager();
	mPath = path;
	mMap = TiXmlDocument(path.c_str());

	if (!mMap.LoadFile())
	{
		std::cout << "level xml not loading.\n" << std::endl;
		return;
	}
	else
	{
		std::cout << "wow this acutally worked\n";
	}

	mMap.Accept(this);
}

Level::~Level()
{
	//thanks stackoverflow man: http://stackoverflow.com/questions/12795196/clearing-a-vector-of-pointers 
	for (std::vector< SpriteSheet* >::iterator it = mSheets.begin(); it != mSheets.end(); ++it)
	{
		delete (*it);
	}
	mSheets.clear();

	for (std::vector< TileLayer* >::iterator it = mLayers.begin(); it != mLayers.end(); ++it)
	{
		delete (*it);
	}
	mLayers.clear();

	for (std::vector< Sprite* >::iterator it = mTileSprites.begin(); it != mTileSprites.end(); ++it)
	{
		delete (*it);
	}
	mTileSprites.clear();

//	delete mpBoxManager;
}

void Level::draw(GraphicsSystem* gs)
{
	for (int layer = 0; layer < (int) mLayers.size(); layer++)
	{
		for (int y = 0; y < mHeight; y++)
		{
			for (int x = 0; x < mWidth; x++)
			{
				int tmp = mLayers[layer]->getTile(x, y)->getID();
				if (tmp > 0)
					NULL; //TODO: Draw functions are internal to things like sprites and are 100% exposed to allegro in dean's implementation.
						  //	We need to write our own draw in the graphics system to use the following line.
					//gs->draw(Vector2D((float)x * mTileWidth - Game::getCameraOffset().getX() + 512, (float)y * mTileHeight - Game::getCameraOffset().getY() + 512), mTileSprites[tmp - 1], 1.0f);
			}
		}
	}

}

void Level::getLevelSize(int &width, int &height)
{
	width = mWidth * mTileWidth;
	height = mHeight * mTileHeight;
}

bool Level::VisitEnter(const TiXmlDocument  &mMap)
{
	return true;
}

bool Level::VisitExit(const TiXmlDocument &mMap)
{
	return true;
}

bool Level::VisitEnter(const TiXmlElement &elem, const TiXmlAttribute *attrib)
{
	if (std::string("map") == elem.Value()) 
	{
		elem.Attribute("width", &mWidth);
		elem.Attribute("height", &mHeight);

		elem.Attribute("tilewidth", &mTileWidth);
		elem.Attribute("tileheight", &mTileHeight);

	}
	else if (std::string("tileset") == elem.Value()) 
	{
		//From the tileset
		SpriteSheet* tmpSheet;
		int tmpTWidth, tmpTHeight, tmpCount, tmpColumns;
		//From the tileset's image
		std::string tmpSource;
		int tmpWidth, tmpHeight;

		//tileset
		elem.Attribute("tilewidth", &tmpTWidth);
		elem.Attribute("tileheight", &tmpTHeight);
		elem.Attribute("tilecount", &tmpCount);
		elem.Attribute("columns", &tmpColumns);

		//image
		const TiXmlElement* image = elem.FirstChildElement();
		tmpSource = image->Attribute("source");
		image->Attribute("width", &tmpWidth);
		image->Attribute("height", &tmpHeight);

		//remove the first three chars ("../") of the path so it gets it relative to the executable, t the .tmx
		tmpSource.erase(0, 3);

		std::cout <<
			"tmpTWidth: " << tmpTWidth << ", tmpTHeight: " << tmpTHeight << ", columns: " << tmpColumns << std::endl <<
			"tmpSource: " << tmpSource << std::endl <<
			"tmpWidth: " << tmpWidth << ", tmpHeight " << tmpHeight << std::endl << std::endl;// << "\a";

		tmpSheet = new SpriteSheet(tmpSource, tmpWidth, tmpHeight, tmpTWidth, tmpTHeight, tmpCount, tmpColumns);

		for (int x = 0; x < tmpCount/tmpColumns; x++)
		{
			for (int y = 0; y < tmpColumns; y++)
			{
				Sprite* tmpSprite = new Sprite(tmpSheet->getBuffer(), (float) y * tmpTHeight, (float) x * tmpTWidth, tmpTWidth, tmpTHeight);
				mTileSprites.push_back(tmpSprite);
			}
		}

		mSheets.push_back(tmpSheet);

	}
	else if (std::string("layer") == elem.Value())
	{
		TileLayer* tmpLayer;
		int tmpWidth, tmpHeight;
		std::string tmpName;
		std::string tmpTileList;
		elem.Attribute("width", &tmpWidth);
		elem.Attribute("height", &tmpHeight);
		tmpName = elem.Attribute("name");

		const TiXmlElement* data = elem.FirstChildElement();
		tmpTileList = data->GetText();

		//std::cout << "Tile: \n" << tmpTileList << std::endl;

		tmpLayer = new TileLayer(tmpName, tmpWidth, tmpHeight, tmpTileList);

		mLayers.push_back(tmpLayer);
	}

	else if (std::string("object") == elem.Value())
	{
		int x, y, w, h;
		elem.Attribute("x", &x);
		elem.Attribute("y", &y);
		elem.Attribute("width", &w);
		elem.Attribute("height", &h);

		const TiXmlElement* propElement = elem.FirstChildElement()->FirstChildElement();
		if (propElement->Attribute("name") == std::string("Spawn"))
		{
			x = x + w / 2;
			y = y + h / 2;
			mSpawnLoc = Vector2D((float)x, (float)y);
		}
		/*  Boxes not yet implemented
		else if (propElement->Attribute("value") == std::string("win"))
		{
			const TiXmlElement* pathElem = propElement->NextSiblingElement();
			if (pathElem == NULL)
			{
				mpBoxManager->addCollisionBox(x, y, w, h, "win");
			}
			else
			{
				const char* path = pathElem->Attribute("value");
				mpBoxManager->addCollisionBox(x, y, w, h, "win", path);
				cout << "Winning to: " << path << endl;
			}
		}
		else if (propElement->Attribute("value") == std::string("lose"))
		{
			mpBoxManager->addCollisionBox(x, y, w, h, "lose");
		}
		else if (propElement->Attribute("value") == std::string("ladder"))
		{
			mpBoxManager->addCollisionBox(x, y, w, h, "ladder");
		}
		*/
	}

	return true;
}

Tile* Level::getTile(int x, int y, std::string target)
{
	TileLayer* layer = NULL;
	for each (TileLayer* curr in mLayers)
	{
		if (curr->getName() == target)
		{
			layer = curr;
			break;
		}
	}

	if (layer == NULL)
		return NULL;

	return layer->getTile(x, y);
}

void Level::getTileSize(int &width, int &height)
{
	width = mTileWidth;
	height = mTileHeight;
}