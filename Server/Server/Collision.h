#pragma once
#include "EventClass.h"
#include <vector>
class Collision : public EventClass
{
public:
	GameObject* collision_event(GameObject* a, GameObject b);
};

