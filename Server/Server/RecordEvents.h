#pragma once
#include "EventClass.h"
#include <queue>
class RecordEvents: public EventClass
{
public:
	int client_id;
	std::vector<std::queue<EventClass>> RecordQueue;
	int start_time;
	int end_time;
	std::vector<Character> replay_chars;
	std::vector<GameObject> replay_game_objs;
	std::vector<int> replay_side_boundary_collisions;
	RecordEvents(std::vector<std::queue<EventClass>> RQ);
	void start_recording(int id, int start_time, std::vector<Character> chars, std::vector<GameObject> collide_objs, std::vector<int> side_boundary_collisions);
	void stop_recording(int id, int end_time);
	//Character stop_recording(std::vector<std::queue<EventClass>> RecordQueue);
	int getClientId();

};

