#include "CharacterSideBoundary.h"
std::vector<GameObject> CharacterSideBoundary::character_side_boundary_event(std::vector<GameObject> b) {
	
	for (int j = 0; j < b.size(); j++) {

		(b[j]).pos.x = (b[j]).pos.x - 800;
		if (b[j].moveDir == 1) {
			b[j].endpt = b[j].endpt - 800;
			b[j].startpt = b[j].startpt - 800;
		}
	}
	return b;
}
