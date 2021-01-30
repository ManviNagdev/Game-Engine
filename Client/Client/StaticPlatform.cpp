#pragma once
#include "StaticPlatform.h"
StaticPlatform::StaticPlatform(float X, float Y, float width, float height, int r, int g, int b) {
	pos.x = X;
	pos.y = Y;
	gameobject_shape.setSize(sf::Vector2f(width, height));
	gameobject_shape.setPosition(pos);
	gameobject_shape.setFillColor(sf::Color(r, g, b));
	gameobject_type = "staticplatform";
}


void StaticPlatform::update() {
	gameobject_shape.setPosition(pos);
}