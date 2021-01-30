#pragma once
#include "Platform.h"
class MovablePlatform : public Platform
{
public:
	
	MovablePlatform(float x, float y, float width, float height, float start, float end, int r, int g, int b, std::string dir);
	float platform_velocity = 0.2;
	
	void move(float dt);
	//float startpt;
	//float endpt;
	float plwidth;
	float plheight;
	//void moveUpDown(float dt);
	
	int direction = 1;
	void setVelocity(int direction);
	float getVelocity();
	void setDirection();
	int getDirection();
	void update();
	
};

