#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "ECS\Components.h"
#include "Collision.h"

SDL_Renderer* Game::renderer = nullptr;

TileMap* map = nullptr;

Manager manager;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};


Game::Game()
{
	isRunning = false;
	window = nullptr;
	renderer = nullptr;
	counter = 0;
}


Game::~Game()
{

}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	isRunning = false;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, fullScreen ? SDL_WINDOW_FULLSCREEN : 0);
		if (window)
		{
			std::cout << "Window created..." << std::endl;
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				std::cout << "Renderer created..." << std::endl;
				isRunning = true;
			}
		}
	}

	// ECS Implementation
	TileMap::LoadTileMap("assets/levels/sample_16x16.map", 16, 16);


	player.AddComponent<TransformComponent>(2);
	player.AddComponent<SpriteComponent>("Assets/Sprites/player_idle.png", 4, 100);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	player.AddGroup(groupPlayers);


	wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.AddComponent<SpriteComponent>("Assets/Sprites/dirt.png");
	wall.AddComponent<ColliderComponent>("wall");
	wall.AddGroup(groupMap);

	map = new TileMap();
}

void Game::HandleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{
	manager.Refresh();
	manager.Update();

	for (auto cc : colliders)
	{
		Collision::AABB(player.GetComponent<ColliderComponent>(), *cc);
	}
}

auto& tiles(manager.GetGroup(groupMap));
auto& players(manager.GetGroup(groupPlayers));
auto& enemies(manager.GetGroup(groupEnemies));


void Game::Render()
{
	SDL_RenderClear(renderer);
	
	// add stuff to render here
	for (auto& t : tiles)
	{
		t->Draw();
	}

	for (auto& p : players)
	{
		p->Draw();
	}

	for (auto& e : enemies)
	{
		e->Draw();
	}


	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "Game cleaned..." << std::endl;
}

bool Game::IsRunning()
{
	return isRunning;
}

void Game::AddTile(int tileID, int x, int y)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(x, y, 32, 32, tileID);
	tile.AddGroup(groupMap);
}
