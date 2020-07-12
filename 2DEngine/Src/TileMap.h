#pragma once

#include <string>

class TileMap
{
public:
	TileMap();
	~TileMap();

	static void LoadTileMap(std::string filePath, int sizeX, int sizeY);

private:
};

