#include "Collision.h"
#include <iostream>
GameObject* Collision::collision_event(GameObject* a, GameObject b) {
//	std::cout<<"velocity = "<< b.getGameObjectVelocity();
	a->pos.x = a->pos.x + b.getGameObjectVelocity();
	a->pos.y = b.pos.y - 20;
	return a;
}