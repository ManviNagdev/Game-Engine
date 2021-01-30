#pragma once
#include <chrono>
#include "Character.h"

#include <msgpack.hpp>
enum EventType {
	Event_Character_Collision,
	Event_Character_Death,
	Event_Character_Spawn,
	Event_Character_SideBoundary,
	Event_User_Input,
	Event_Start_Record,
	Event_Stop_Record,
	No_Event
};

class EventClass: public Character
{

	public:
		EventClass(float event_time);
		EventType et = No_Event;
		std::string keyvalue = "";
		GameObject collided_with;
		bool isjumping = false;
		bool isRight = false;
		bool isLeft = false;
	
		float eventTime;
	
		MSGPACK_DEFINE(et, collided_with, keyvalue, isjumping, isRight, isLeft, eventTime);
};
MSGPACK_ADD_ENUM(EventType);
