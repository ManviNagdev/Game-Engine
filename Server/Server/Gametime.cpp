#pragma once
//#include <chrono>
#include <chrono>
#include "Timeline.cpp"
//using namespace std::chrono;
class Gametime : public Timeline {

private:
	std::chrono::milliseconds startTime;


public:
	float speed_change_factor;
	int step_size;
	float speed;
	std::chrono::time_point<std::chrono::system_clock> epoch;
	Gametime(int step_size) {
		this->step_size = step_size;
		this->speed = 1;
		this->speed_change_factor = speed_change_factor;
		startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - epoch);
	}

	void setSpeed(float ss) {
		speed = ss;

	}

	int getTime() {
		std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - epoch);
		std::chrono::milliseconds et = now - startTime;
		int elapsed = (int)(et.count() / step_size) * speed;
		return elapsed;
	}

	int getSpeed() {
		return speed;
	}
	//void pause(bool p) {
	//	std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - epoch);
	//	if (p) {
	//		startTime = now;
	//		std::chrono::milliseconds et = now - startTime;
	//	}
	//	if(!p)
	//		startTime = now;
	//}
	//
};