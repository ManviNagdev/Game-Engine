#include "UserInput.h"
//UserInput::UserInput(std::string keyvalue) {
//	keypress = keyvalue;
//}
Character UserInput::user_input_event(Character a, std::string keyvalue) {
	if (keyvalue == "Left") 
		a.moveLeft(1);
	else if (keyvalue == "Right")
		a.moveRight(1);
	else if (keyvalue == "Up")
		a.moveUp(1);
	
	a.update();
	return a;
}