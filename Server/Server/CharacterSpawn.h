#pragma once
#include "EventClass.h"
class CharacterSpawn:public EventClass
{
public:
	GameObject character_spawn_event(GameObject a, GameObject b);
};

