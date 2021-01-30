#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
using namespace sf;

class Platform : public GameObject
{
public:

	//RectangleShape platform_shape;	
	RectangleShape getShape();
	float getVelocity();
	float platform_velocity;
};