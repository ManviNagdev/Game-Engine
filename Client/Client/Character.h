#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <msgpack.hpp>
using namespace sf;

class Character : public GameObject
{
public:
	Vector2f pos;
	float character_velocity = 0.5f;
	//RectangleShape character_shape;
	RectangleShape getShape();
	Character(float x, float y);
	Character();
	Character* charcater_ptr = NULL;

	GameObject* platform_ptr = NULL;
	void moveLeft(float dt);

	void moveRight(float dt);

	void moveUp(float dt);

	void moveDown(float dt);

	void update();

	void setVelocity(float v);
	void setColor(int r, int g, int b);
	void CharJump(float dt);
	MSGPACK_DEFINE(pos.x, pos.y);
};