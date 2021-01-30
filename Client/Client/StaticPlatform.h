#pragma once
#include "Platform.h"

class StaticPlatform: public Platform
{
public: 

	StaticPlatform(float x, float y, float width, float height, int r, int g, int b);
	void update();
};
