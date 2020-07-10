#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "ECS\Components.h"


SDL_Renderer* Game::renderer = nullptr;

TileMap* map = nullptr;

Manager manager;
auto& newPlayer(manager.AddEntity());

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

//	player = new GameObject("Assets/Sprites/player.png", 0, 0);
//	enemy = new GameObject("Assets/Sprites/enemy.png", 64,64);

	newPlayer.AddComponent<PositionComponent>();
	newPlayer.GetComponent<PositionComponent>().SetPosition(500, 500);

	map = new TileMap();
}

void Game::HandleEvents()
{
	SDL_Event event;
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
	manager.Update();
	std::cout << newPlayer.GetComponent<PositionComponent>().X() << "," << newPlayer.GetComponent<PositionComponent>().Y() << std::endl;
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	
	map->DrawMap();
	// add stuff to render here

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
