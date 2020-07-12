#pragma once

#include "ECS.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include <SDL.h>

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* filePath;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			filePath = "Assets/Sprites/water.png";
			break;
		case 1:
			filePath = "Assets/Sprites/dirt.png";
			break;
		case 2:
			filePath = "Assets/Sprites/grass.png";
			break;

		default:
			std::cout << "Invalid sprite ID passed to the TileComponent" << std::endl;
			break;
		}

	}

	void Init() override
	{
		entity->AddComponent<TransformComponent>(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), tileRect.w, tileRect.h, 1);
		transform = &entity->GetComponent<TransformComponent>();

		entity->AddComponent<SpriteComponent>(filePath);
		sprite = &entity->GetComponent<SpriteComponent>();
	}

};