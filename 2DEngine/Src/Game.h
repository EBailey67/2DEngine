#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#include "GameObject.h"

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool IsRunning();

	static SDL_Renderer* renderer;

private:
	bool isRunning;
	SDL_Window* window;
	int counter;
};

