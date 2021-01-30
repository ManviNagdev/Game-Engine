#include <zmq.hpp>
#include <string>
#include <iostream>
#include <cstdlib> 
#include <zmq_zhelpers.hpp>
#include "DeathZone.h"
#include "MovablePlatform.h"
#include "Platform.h"
#include "NotRenderable.h"
#include "Character.h"
#include "CharacterSpawn.h"
#include "Gametime.cpp"
#include "Renderable.h"
#include "StaticPlatform.h"
#include "Collision.h"
#include "SideBoundary.h"
#include "CharacterSideBoundary.h"
#include "Spawn.h"
#include "RecordEvents.h"
#include "EventClass.h"
#include "UserInput.h"
#include <msgpack.hpp>
#include <queue>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif
#include <thread>
#include <mutex>          // std::mutex

std::mutex mtx;           // mutex for critical section

int itr = 0;
std::string pos[] = { "","","","" };
MovablePlatform p1(200, 400, 100, 20, 200, 600, 35, 0, 30, "LR");
DeathZone d1(0, 550, 2400, 50);
MovablePlatform p2(1900, 200, 100, 20, 200, 400, 35, 0, 30, "UD");
StaticPlatform sp1(0, 400, 200, 200, 255, 186, 73);
StaticPlatform sp2(600, 400, 400, 200, 255, 186, 73);
StaticPlatform sp3(1050, 350, 100, 20, 239, 91, 91);
StaticPlatform sp4(1200, 300, 100, 20, 0, 185, 185);
StaticPlatform sp5(1350, 250, 100, 20, 137, 0, 117);
StaticPlatform sp6(1500, 200, 300, 400, 255, 186, 73);
StaticPlatform sp7(2100, 300, 300, 300, 255, 186, 73);
SideBoundary sb1(800, 0, 1, 600);
SideBoundary sb2(1600, 0, 1, 600);
Spawn sw1(50, 50, 1, 600);

//Spawn sw2(800, 0, 1, 600);
//Spawn sw3(1600, 0, 1, 600);
DeathZone d2(0,500, 2400, 50);
Gametime server_time(50);
bool isRecord = false;
bool* RecordPtr = &isRecord;
int dt_in_p = 1;
int dt_in_c = 1;
std::vector<Character> chars;

std::vector<int> side_boundary_collisions_count;
std::vector<std::queue<EventClass>> RecordQueue; // vector of queues
 // add a queue

void multiserver(int client_id, int index, int &id, int iteration[], std::string pos[]) {
	zmq::context_t context(1);
	zmq::socket_t socket2(context, ZMQ_REP);
	
	//	std::string socket_num = std::to_string(5556 + client_id);

	//	assign a socket based on client id

	if (client_id == 0)
		socket2.bind("tcp://*:5556");
	else if (client_id == 1)
		socket2.bind("tcp://*:5557");
	else if (client_id == 2)
		socket2.bind("tcp://*:5558");
	else if (client_id == 3)
		socket2.bind("tcp://*:5559");
	
	bool isjumping = false;
	bool canJump = true;
	std::cout << "Hi";
	zmq::message_t input0;
	RecordQueue.push_back(std::queue<EventClass>());
	
	socket2.recv(&input0);
	std::string time_elapsed;
	time_elapsed = std::to_string(server_time.getTime());
	zmq::message_t reply0(time_elapsed.length());
	memcpy(reply0.data(), time_elapsed.c_str(), time_elapsed.length());
	socket2.send(reply0);
	//std::cout << "Hi";
	Character c1(50, 150);
	
	//RecordEvents re(RecordQueue);
	std::vector<GameObject> collide_objs;
	std::queue<EventClass> events_queue;
	collide_objs.push_back(p1);
	collide_objs.push_back(p2);
	collide_objs.push_back(sp1);
	collide_objs.push_back(sp2);
	collide_objs.push_back(sp3);
	collide_objs.push_back(sp4);
	collide_objs.push_back(sp5);
	collide_objs.push_back(sp6);
	collide_objs.push_back(sp7);
	collide_objs.push_back(d1);
	collide_objs.push_back(sb1);
	collide_objs.push_back(sb2);
	//std::cout <<"character: " <<chars[0].pos.x<<"  " <<chars[0].pos.y<<"\n";
	Collision col;
	CharacterSpawn cs;
	UserInput ui;
	CharacterSideBoundary csb;
	RecordEvents re(RecordQueue);
	
	side_boundary_collisions_count.push_back(0);
	int previous_event = 5;
	int sideboundarycollisions = 0;
	for (int j = 0; j < collide_objs.size(); j++) {
		//if (collide_objs.gameobjs[j]->gameobject_type != "deathzone" && collide_objs.gameobjs[j]->gameobject_type != "sideboundary" && collide_objs.gameobjs[j]->gameobject_type != "spawn")
		//collide_objs.gameobjs[j]->update();
	//	std::cout << collide_objs[j].pos.x << "  " << collide_objs[j].pos.y << "  " << collide_objs[j].gameobject_type << " \n";
		collide_objs[j].update();
	}
	EventClass e(server_time.getTime());
	EventClass next_event(server_time.getTime());
	EventClass replay_event(server_time.getTime());
	while (true) {
		itr++;
		
		
		zmq::message_t input1;		//input message received by server
		socket2.recv(&input1);
		msgpack::sbuffer sbuf;
		//std::cout << "Received" << std::string(static_cast<char*>(input1.data()), input1.size()) << std::endl;
		sbuf.write(static_cast<const char*>(input1.data()), input1.size());
	
		msgpack::unpacked msg;
		msgpack::unpack(msg, sbuf.data(), sbuf.size());
		msgpack::object obj = msg.get();
		//std::cout <<  << std::endl;
		
		obj.convert(e);
		if (c1.pos.x < 1) {
			c1.pos.x = 1;
		}
		
		//std::cout << "event type=" << e.et << " key=" << e.keyvalue << " collided with=" << e.collided_with.gameobject_type << " jump" << e.isjumping << " isRight=" << e.isRight << " isLeft=" << e.isLeft << "\n";
		//std::cout << "Server time = " << server_time.getTime();
		//std::cout << " Time = " << e.eventTime<<"\n";
		if (e.et != 7) {
			events_queue.push(e);
	//		std::cout << "event type=" << e.et << " key=" << e.keyvalue << " collided with=" << e.collided_with.gameobject_type << " jump" << e.isjumping << " isRight=" << e.isRight << " isLeft=" << e.isLeft << "\n";

		}
		if (e.isjumping == false) //gravity 
		{
			c1.moveDown(dt_in_c);
		}
		
		p1.setDirection();
		p1.setVelocity(p1.getDirection());
		p1.move(dt_in_p);
		p2.setDirection();
		p2.setVelocity(p2.getDirection());
		p2.move(dt_in_p);
		p1.update();
		p2.update();
		sp1.update();
		sp2.update();
		sp3.update();
		sp4.update();
		sp5.update();
		sp6.update();
		sp7.update();
		collide_objs[0].pos.x = p1.pos.x - 800 * side_boundary_collisions_count[index];
		collide_objs[1].pos.x = p2.pos.x - 800 * side_boundary_collisions_count[index];
		collide_objs[0].pos.y = p1.pos.y;
		collide_objs[1].pos.y = p2.pos.y;
		
		if (!events_queue.empty()) {
			//if (events_queue.front().eventTime <= server_time.getTime()) {
			next_event = events_queue.front();
			events_queue.pop();
			//	std::cout << "event type=" << next_event.et << " key=" << next_event.keyvalue << " collided with=" << next_event.collided_with.gameobject_type << " jump" << next_event.isjumping << " isRight=" << next_event.isRight << " isLeft=" << next_event.isLeft << " time= "<<next_event.eventTime<<"\n";
			//}


			if (next_event.isRight == true) {
				c1.moveRight(1);
			}
			if (next_event.isLeft == true) {
				c1.moveLeft(1);
			}
			switch (next_event.et) {
			case 0:
				c1.pos.y = (col.collision_event(&c1, next_event.collided_with))->pos.y;
				//	std::cout << next_event.collided_with.gameobject_type << "collided with\n";
					// c1.pos.x = (col.collision_event(&c1, e.collided_with))->pos.x;
				break;
			case 1:
				// e.et = Event_Character_Spawn;

			case 2:
				c1.pos.x = (cs.character_spawn_event(c1, sw1)).pos.x;
				c1.pos.y = (cs.character_spawn_event(c1, sw1)).pos.y;

				break;
			case 3: if (previous_event != next_event.et) {
				c1.pos.x = 5;
				++side_boundary_collisions_count[index];
				collide_objs = csb.character_side_boundary_event(collide_objs);
			}
					break;
			case 4:
				c1 = ui.user_input_event(c1, next_event.keyvalue);

				break;

			case 5:
				*RecordPtr = true;
				re.start_recording(index, e.eventTime, chars, collide_objs, side_boundary_collisions_count);
			//	std::cout << "replay char" << re.replay_chars[0].pos.x << "  " << re.replay_chars[0].pos.y << "  \n";
				break;

			case 6:
				*RecordPtr = false;
				re.stop_recording(index, e.eventTime);
			
				break;
			}
			previous_event = next_event.et;
		}
		c1.update();
		
		chars[index] = c1;
		
		msgpack::sbuffer sbuf2;
		msgpack::pack(sbuf2, c1);
		zmq::message_t reply(sbuf2.size());
		memcpy(reply.data(), sbuf2.data(), sbuf2.size());
		socket2.send(reply);

		
		for (int i = 0; i<collide_objs.size(); i++) {
				//input message received by server
			zmq::message_t input2;
			
			socket2.recv(&input2);

			msgpack::sbuffer sbuf3;
		//	std::cout << collide_objs.gameobjs[i]->pos.x;
			msgpack::pack(sbuf3, collide_objs[i]);
			zmq::message_t reply2(sbuf3.size());
			memcpy(reply2.data(), sbuf3.data(), sbuf3.size());
			socket2.send(reply2);
		}

		zmq::message_t input3;
		socket2.recv(&input3);
		std::string num = std::to_string(id);
		zmq::message_t reply3(num.length());
		memcpy(reply3.data(), num.c_str(), num.length());
		socket2.send(reply3);
		for (int l = 0; l < id; l++) {

			zmq::message_t input3;

			socket2.recv(&input3);
		//	std::cout << chars[l].pos.x<<" s char "<<chars[l].pos.y<<"  "<<l<<"\n";
			msgpack::sbuffer sbuf4;
			//	std::cout << collide_objs.gameobjs[i]->pos.x;
			msgpack::pack(sbuf4, chars[l]);
			zmq::message_t reply4(sbuf4.size());
			memcpy(reply4.data(), sbuf4.data(), sbuf4.size());
			socket2.send(reply4);

		}
		zmq::message_t input4;

		socket2.recv(&input4);
		//	std::cout << chars[l].pos.x<<" s char "<<chars[l].pos.y<<"  "<<l<<"\n";
		msgpack::sbuffer sbuf5;
		//	std::cout << collide_objs.gameobjs[i]->pos.x;
		msgpack::pack(sbuf5, side_boundary_collisions_count);
		zmq::message_t reply5(sbuf5.size());
		memcpy(reply5.data(), sbuf5.data(), sbuf5.size());
		socket2.send(reply5);
	}
	
}

void createClientThread(int &id, std::vector<std::thread> &clients_to_connect, int iteration[], std::string pos[]) {
	int old_id = -1;

	while (1) {
	//	std::cout << old_id << " " << id << "\n";
		if (old_id != id) {
		//	std::cout << "BBBBBBBBB";
			++old_id;
			clients_to_connect.push_back(std::thread(multiserver, old_id, id, std::ref(id), iteration, pos));
		}
	}
	
}
int main() {
	//  Prepare our context and socket
	int iteration[] = { 0,0,0,0,0,0,0,0,0,0 };
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	socket.bind("tcp://*:5555");
	//int clients[10]; //= { 0,0,0,0,0,0,0,0,0,0 };
	
	int total_i = 0;
	int index = 0;
	int c = 0;
	for (int i = 0; i < 4; i++) {
		chars.push_back(Character(0,0));
	}
	std::vector<std::thread> clients_to_connect;
	//sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Default);
	std::thread createClient(createClientThread, std::ref(index), std::ref(clients_to_connect), iteration, pos);
	
	
	while (true) {
		zmq::message_t request;
		//collide_objs.addCharacter(c1);
		
		
		//  Wait for next request from client
		socket.recv(&request);
		std::cout<< "Received" << std::string(static_cast<char*>(request.data()), request.size()) << std::endl;
		std::string client_id_recv = std::string(static_cast<char*>(request.data()), request.size());
		int client_id = stoi(client_id_recv);
		
		//sleep(1000);
		std::string mmm;
		std::string client_name;
		
		mmm = std::to_string(index);
		zmq::message_t reply(mmm.length());
		memcpy(reply.data(), mmm.c_str(), mmm.length());
		socket.send(reply);
		index++;	
		
	}
	
	socket.close();
	return 0;
}