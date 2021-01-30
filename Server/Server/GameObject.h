#pragma once
#include <SFML/Graphics.hpp>
#include <msgpack.hpp>
using namespace sf;
class GameObject:public RectangleShape
{
public:
	Vector2f pos;
	float startpt;
	float endpt;
	//GameObject(float x, float y, float width, float height);
	RectangleShape getShape();
	RectangleShape gameobject_shape;
	std::string gameobject_type;
	std::string getType();
	int moveDir = 0;
	std::string checkcollision(GameObject& a, GameObject& b);
	std::vector<GameObject*> gameobjs;
	void addGameObjects(GameObject& g);
	float gameobject_velocity;
	void setGameObjectVelocity(float v);
	float getGameObjectVelocity();
	std::vector<GameObject*> getGameObjects();
	//std::vector<GameObject> gameobjs;
	void update();
	MSGPACK_DEFINE(pos.x, pos.y, gameobject_type);
};

