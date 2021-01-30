#pragma once
#include "Platform.h"

RectangleShape Platform::getShape()
{
	return gameobject_shape;
}

float Platform::getVelocity() {
	return gameobject_velocity;
}