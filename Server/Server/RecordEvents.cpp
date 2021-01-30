#include "RecordEvents.h"
RecordEvents::RecordEvents(std::vector<std::queue<EventClass>> RQ) {
	RecordQueue = RQ;
}
void RecordEvents::start_recording(int id, int time, std::vector<Character> chars, std::vector<GameObject> collide_objs, std::vector<int> side_boundary_collisions) {
	client_id = id;
	start_time = time;
	replay_chars = chars;
	replay_game_objs = collide_objs;
	replay_side_boundary_collisions = side_boundary_collisions;
}

void RecordEvents::stop_recording(int id, int time) {
	client_id = id;
	end_time = time;
}

int RecordEvents::getClientId() {
	return client_id;
}