#pragma once
#include "EventClass.h"
#include <vector>
class CharacterSideBoundary:public EventClass
{
public:
	std::vector<GameObject> character_side_boundary_event(std::vector<GameObject> b);
};

