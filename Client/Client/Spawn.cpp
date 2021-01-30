#pragma once
#include "Spawn.h"
Spawn::Spawn(float X, float Y, float width, float height) {
	pos.x = X;
	pos.y = Y;
	gameobject_shape.setSize(sf::Vector2f(width, height));
	gameobject_shape.setPosition(pos);
	gameobject_type = "spawn";
}