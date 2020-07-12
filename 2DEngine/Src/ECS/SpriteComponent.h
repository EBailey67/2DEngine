#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;			// Count of frames in animation sequence
	int speed = 100;		// Delay in milliseconds between each frame during animation

public:
	SpriteComponent() = default;
	SpriteComponent(const char* filePath)
	{
		SetTexture(filePath);
	}

	SpriteComponent(const char* filePath, int nFrames, int mSpeed)
	{
		animated = true;
		SetTexture(filePath);
		frames = nFrames;
		speed = mSpeed;
	}


	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void SetTexture(const char* filePath)
	{
		texture = TextureManager::LoadTexture(filePath);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void Update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};

