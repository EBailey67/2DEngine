#pragma once

#include "Game.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	void LoadTileMap(int m[20][25]);
	void DrawMap();

private:
	SDL_Rect src, dest;
	
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25];
};

