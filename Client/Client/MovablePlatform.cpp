#pragma once
#include "MovablePlatform.h"

MovablePlatform::MovablePlatform(float X, float Y, float width, float height, float start, float end, int r, int g, int b, std::string dir)
{
	pos.x = X;
	pos.y = Y;
	gameobject_shape.setSize(sf::Vector2f(width, height));
	gameobject_shape.setPosition(pos);
	gameobject_shape.setFillColor(sf::Color(r, g, b));
	plwidth = width;
	plheight = height;
	gameobject_type = "movingplatform";
	if (dir == "UD") {
		moveDir = 0;
		if (start <= end)
		{
			startpt = end;
			endpt = start;
		}
		else {
			startpt = start;
			endpt = end;
		}
	}
	else
	{
		moveDir = 1;
		if (start <= end)
		{
			startpt = start;
			endpt = end;
		}
		else {
			startpt = end;
			endpt = start;
		}
	}
	
}
void MovablePlatform::setDirection() {
	if ((pos.x <= startpt && moveDir == 1) || (pos.y <= endpt - plheight && moveDir == 0)) {
		direction = 1;
	}
	else if ((pos.x >= endpt - plwidth && moveDir == 1) || (pos.y >= startpt && moveDir == 0))
		direction = -1;
	
}
void MovablePlatform::setVelocity(int direction) {
	platform_velocity = 0.4 * direction;
}

void MovablePlatform::move(float dt)

{	if (moveDir==0)
		pos.y += platform_velocity * dt;

	else
		pos.x += platform_velocity * dt;
}
float MovablePlatform::getVelocity()
{
	return platform_velocity;
}

void MovablePlatform::update()
{
	gameobject_shape.setPosition(pos);
}

int MovablePlatform::getDirection() {
	return direction;
}

