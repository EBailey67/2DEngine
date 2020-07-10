#pragma once
#include "ECS.h"

class PositionComponent : public Component
{
private:
	int xPos;
	int yPos;

public:
	int X() { return xPos; }
	void X(int x) { xPos = x; }

	int Y() { return yPos; }
	void Y(int y) { yPos = y; }

	void Init() override
	{
		xPos = 0;
		yPos = 0;
	}

	void Update() override
	{
		xPos++;
		yPos++;
	}

	void SetPosition(int x, int y)
	{
		xPos = x;
		yPos = y;
	}
};

