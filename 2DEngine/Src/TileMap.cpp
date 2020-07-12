#include "TileMap.h"
#include "Game.h"
#include <fstream>

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

void TileMap::LoadTileMap(std::string filePath, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(filePath);

	int srcX;
	int srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			srcY = atoi(&tile) * 32;
			mapFile.get(tile);
			srcX = atoi(&tile) * 32;
			Game::AddTile(srcX, srcY, x * 64, y * 64);
			mapFile.ignore();
		}
	}


	mapFile.close();
}


