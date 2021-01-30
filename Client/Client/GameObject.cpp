#include "GameObject.h"
#include <iostream>

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
