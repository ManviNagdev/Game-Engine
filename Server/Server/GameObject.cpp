#include "GameObject.h"
#include <iostream>
//GameObject::GameObject(float X, float Y, float width, float height) {
//	pos.x = X;
//	pos.y = Y;
//	gameobject_shape.setSize(sf::Vector2f(width, height));
//	gameobject_shape.setPosition(pos);
//}
RectangleShape GameObject::getShape() {
	return gameobject_shape;
}

std::string GameObject::getType() {
	return gameobject_type;
}
std::string GameObject::checkcollision(GameObject& a, GameObject& b) {
	std::string type = "";
	//std::cout << a.pos.x << " A " << "collide\n";
	//for(int i=0;i<gameobjs.size();i++)
	if (b.gameobject_shape.getGlobalBounds().intersects(a.gameobject_shape.getGlobalBounds())) {
		type = a.gameobject_type;
		//std::cout << "type AAA" << "\n";
	}
	//}
	return type;
}
void GameObject::update() {
	gameobject_shape.setPosition(pos);
}
void GameObject::addGameObjects(GameObject& g) {
	gameobjs.push_back(&g);
}
std::vector<GameObject*> GameObject::getGameObjects() {
	return gameobjs;
}
void GameObject::setGameObjectVelocity(float v) {
	gameobject_velocity = v;
}
float GameObject::getGameObjectVelocity() {
	return gameobject_velocity;
}