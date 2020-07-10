#pragma once
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* filePath)
	{
		SetTexture(filePath);
	}

	void SetTexture(const char* filePath)
	{
		texture = TextureManager::LoadTexture(filePath);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;

		destRect.x = destRect.y = 0;
		destRect.w = destRect.h = 64;
	}

	void Update() override
	{
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};

