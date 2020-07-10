#include "TileMap.h"
#include "TextureManager.h"


int lvl1[20][25] =
{
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

TileMap::TileMap()
{
	dirt = TextureManager::LoadTexture("Assets/Sprites/dirt.png");
	grass = TextureManager::LoadTexture("Assets/Sprites/grass.png");
	water = TextureManager::LoadTexture("Assets/Sprites/water.png");

	src.x = src.y = 0;
	src.w = src.h = 32;
	dest.x = dest.y = 0;
	dest.w = dest.h = 32;

	LoadTileMap(lvl1);
}

TileMap::~TileMap()
{

}

void TileMap::LoadTileMap(int m[20][25])
{
	for (int row = 0; row < 20; row++)
	{
		for (int col = 0; col < 25; col++)
		{
			map[row][col] = m[row][col];
		}
	}
}

void TileMap::DrawMap()
{
	for (int row = 0; row < 20; row++)
	{
		for (int col = 0; col < 25; col++)
		{
			dest.x = col * 32;
			dest.y = row * 32;

			switch (map[row][col])
			{
			case 0:	// Water
				TextureManager::Draw(water, src, dest);
				break;
			case 1: // Grass
				TextureManager::Draw(grass, src, dest);
				break;
			case 2: // Dirt
				TextureManager::Draw(dirt, src, dest);
				break;
			default:
				std::cout << "Unexpected value in our TileMap :" << map[row][col] << std::endl;
				break;
			}
		}
	}
}

