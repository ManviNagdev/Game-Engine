#pragma once
#include "Character.h"

Character::Character(float X, float Y)
{
	pos.x = X;
	pos.y = Y;

	gameobject_shape.setSize(sf::Vector2f(20, 20));
	gameobject_shape.setFillColor(Color(238, 233, 76));
	gameobject_shape.setPosition(pos);
}

Character::Character()
{
	pos.x = 0;
	pos.y = 0;

	gameobject_shape.setSize(sf::Vector2f(20, 20));
	gameobject_shape.setFillColor(Color(238, 233, 76));
	gameobject_shape.setPosition(pos);
}

RectangleShape Character::getShape()
{
	return gameobject_shape;
}
void Character::moveLeft(float dt)
{
	pos.x -= character_velocity * dt;
}

void Character::moveRight(float dt)
{
	pos.x += character_velocity * dt;
}

void Character::moveUp(float dt)
{
	pos.y -= character_velocity * dt;
}

void Character::moveDown(float dt)
{
	pos.y += character_velocity * dt;
}
void Character::update()
{
	gameobject_shape.setPosition(pos);
}
void Character::setVelocity(float v) {
	character_velocity = v;
}
void Character::CharJump(float dt) {
	pos.y += character_velocity * dt;
}
void Character::setColor(int r, int g, int b) {
	gameobject_shape.setFillColor(Color(r, g, b));
}
