#pragma once
#include "EventClass.h"
class UserInput: public EventClass
{
public:
	//std::string keypress;
	//UserInput(std::string keypress);
	Character user_input_event(Character a, std::string keyvalue);
};

