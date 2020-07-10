#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	PositionComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* filePath)
	{

	}

	void Init() override
	{
		position = &entity->GetComponent<PositionComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;

		destRect.x = destRect.y = 0;
		destRect.w = destRect.h = 64;
	}

	void Update() override
	{
		destRect.x = position->X();
		destRect.y = position->Y();
	}

	void Draw() override
	{
//		TextureManager::Draw()
	}
};

