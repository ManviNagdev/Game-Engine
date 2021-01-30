
#include <SFML/Graphics.hpp>
#include <zmq.hpp>
#include <iostream>
#include <Windows.h>
#include "EventClass.h"
#include "DeathZone.h"
#include "MovablePlatform.h"
#include "Platform.h"
#include "NotRenderable.h"
#include "Character.h"
#include "Gametime.cpp"
#include "Renderable.h"
#include "StaticPlatform.h"
#include "Collision.h"
#include "SideBoundary.h"
#include "Spawn.h"
#include <queue>
#include <cmath>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include "EventClass.h"
#include <chrono>
#include <msgpack.hpp>
int main()
{	//  Prepare our context and socket	
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REQ);

	std::cout << "Connecting to hello world server" << std::endl;
	socket.connect("tcp://localhost:5555");
	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);
	int client_id = rand();

	//send a connection request to server
	std::string msg;
	msg = std::to_string(client_id);

	zmq::message_t request(msg.length());
	memcpy((void*)request.data(), msg.c_str(), msg.length());
	std::cout << "Sending " << msg << "..." << std::endl;
	socket.send(request);
	//Sleep(2000);

	//  Get the reply.
	zmq::message_t reply;
	socket.recv(&reply);
	auto msg1 = std::string(static_cast<char*>(reply.data()), reply.size());

	///connect to the port_no based on the reply from server
	int port_no = 5556 + stoi(msg1);

	std::cout << port_no;
	zmq::socket_t socket2(context, ZMQ_REQ);

	if (port_no == 5556)
	{
		socket2.connect("tcp://localhost:5556");
	}
	else if (port_no == 5557)
	{
		socket2.connect("tcp://localhost:5557");
	}
	else if (port_no == 5558)
	{
		socket2.connect("tcp://localhost:5558");
	}
	else if (port_no == 5559)
	{
		socket2.connect("tcp://localhost:5559");
	}

	zmq_disconnect(socket, "tcp://localhost:5555");

	//add character instances to the vector
	zmq::message_t request0(4);
	memcpy(request0.data(), "Time", 4);

	socket2.send(request0);

	zmq::message_t message0;
	socket2.recv(message0);

	std::string msg0 = std::string(static_cast<char*>(message0.data()), message0.size());

	int offset = stoi(msg0);

	Gametime realtime(50, offset);
	std::vector<Character> c;

	std::vector<std::queue<Character>> replay_chars;
	std::vector<std::queue<GameObject>> replay_gameobjs;
	std::vector<std::queue<int>> replay_side_boundary_collisions;
	for (int i = 0; i <= 3; i++) {
		c.push_back(Character(100.f, 100.f));
	}

	int oldclient = stoi(msg1);
	std::cout << "oldclient" << oldclient;
	std::cout << "game starts";

	//creating real time
    //Gametime charactertime(50);  //creating timeline object for character
    //Gametime platformtime(50);  //creating timeline object for platform
	int dt = 5;
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Default);
	Character c1(50.f, 100.f);
	MovablePlatform p1(200, 400, 100, 20, 200, 600, 35, 0, 30, "LR");
	MovablePlatform p2(1900, 200, 100, 20, 200, 400, 35, 0, 30, "UD");
	StaticPlatform sp1(0, 400, 200, 200, 255, 186, 73);
	StaticPlatform sp2(600, 400, 400, 200, 255, 186, 73);
	StaticPlatform sp3(1050, 350, 100, 20, 239, 91, 91);
	StaticPlatform sp4(1200, 300, 100, 20, 0, 185, 185);
	StaticPlatform sp5(1350, 250, 100, 20, 137, 0, 117);
	StaticPlatform sp6(1500, 200, 300, 400, 255, 186, 73);
	StaticPlatform sp7(2100, 300, 300, 300, 255, 186, 73);
	DeathZone d1(0, 550, 2400, 50);
	SideBoundary sb1(800, 0, 1, 600);
	SideBoundary sb2(1600, 0, 1, 600);
	Spawn sw1(0, 0, 1, 600);
	
	GameObject collide_objs;

	collide_objs.addGameObjects(p1);
	collide_objs.addGameObjects(p2);
	collide_objs.addGameObjects(sp1);
	collide_objs.addGameObjects(sp2);
	collide_objs.addGameObjects(sp3);
	collide_objs.addGameObjects(sp4);
	collide_objs.addGameObjects(sp5);
	collide_objs.addGameObjects(sp6);
	collide_objs.addGameObjects(sp7);
	collide_objs.addGameObjects(d1);
	collide_objs.addGameObjects(sb1);
	collide_objs.addGameObjects(sb2);
	
	int flag = 0;
	int start_record_time = 0;
	int end_record_time = 0;
	c1.charcater_ptr = &c1;
	//bool side_boundary_collision = false;
	//bool isjumping = false;
	bool canJump = true;
	float dt_in_c = 1;
	float dt_in_p = 1;
	int clients = 0;
	bool inFocus = true;
	bool record = false;
	int sideboundrycollisions = 0;
	bool Replay = false;
	std::string positions[13 * 2 + 13];
	std::vector<Character> chars;
	std::vector<int> side_boundary_collisions_count;
	Character dummy(0, 0);
	for (int i = 0; i < 4; i++) {
		chars.push_back(dummy);
		side_boundary_collisions_count.push_back(0);
		replay_chars.push_back(std::queue<Character>());
		replay_gameobjs.push_back(std::queue<GameObject>());
		replay_side_boundary_collisions.push_back(std::queue<int>());
	}
	int temp = 1;
	while (window.isOpen())
	{
		sf::Event event;
		EventClass e(realtime.getTime());

		if (inFocus == true) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { //move left

				e.et = Event_User_Input;
				e.keyvalue = "Left";
				e.isLeft = true;
				e.eventTime = realtime.getTime();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { //move right

				e.et = Event_User_Input;
				e.keyvalue = "Right";
				e.isRight = true;
				e.eventTime = realtime.getTime();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { //jump
				if (canJump == true)
				{
					e.isjumping = true;
					e.et = Event_User_Input;
					e.keyvalue = "Up";
					e.eventTime = realtime.getTime();
				}
				//	//			input1 = "U";

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { //start recording

				e.et = Event_Start_Record;
				e.keyvalue = "R";
				e.eventTime = realtime.getTime();
				start_record_time = e.eventTime;
				record = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { //start recording

				e.et = Event_Stop_Record;
				e.keyvalue = "S";
				e.eventTime = realtime.getTime();
				end_record_time = e.eventTime;
				Replay = true;
				record = false;
				int t = start_record_time + realtime.getTime();
				//window.clear(sf::Color(135, 206, 235));
				
				while (!replay_chars[temp-1].empty()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
						
						if (dt == 1) {
							dt = 5;
						}
						else if (dt == 5) {
							dt = 10;

						}
						else
							dt = 1;
					}
					for (int i = 0; i < temp; i++) {
						if (replay_side_boundary_collisions[i].front() == replay_side_boundary_collisions[stoi(msg1)].front())
							window.draw(replay_chars[i].front().getShape());
						else if (i == stoi(msg1)) {
							window.draw(replay_chars[i].front().getShape());
						}
						replay_side_boundary_collisions[i].pop();
						replay_chars[i].pop();

						for (int j = 0; j < collide_objs.gameobjs.size(); j++) {
							if (replay_gameobjs[i].front().gameobject_type != "deathzone" && replay_gameobjs[i].front().gameobject_type != "sideboundary" && replay_gameobjs[i].front().gameobject_type != "spawn")

								window.draw(replay_gameobjs[i].front().getShape());
							replay_gameobjs[i].pop();
						}
						
						//	window.display();
						//	Sleep(10);
						//	//window.draw(replay_side_boundary_collisions[i].front().getShape());
						//	window.clear(sf::Color(135, 206, 235));
						//}
					}
							window.display();
							Sleep(50/dt);
							//window.draw(replay_side_boundary_collisions[i].front().getShape());
							window.clear(sf::Color(135, 206, 235));
					
					
					}
					
				
			}
		}

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::GainedFocus) {
				inFocus = true;
			}

			if (event.type == sf::Event::LostFocus) {
				inFocus = false;
			}
			if (event.type == sf::Event::KeyReleased)
			{
				e.isjumping = false;
				e.isRight = false;
				e.isLeft = false;
			}

		}

		std::string type = "";
		if (c1.pos.x < 0) {
			c1.pos.x = 0;
		}
		for (int j = 0; j < collide_objs.gameobjs.size(); j++)
		{
			//std::cout << collide_objs.gameobjs[j]->pos.x << "  " << collide_objs.gameobjs[j]->pos.y << "  " << collide_objs.gameobjs[j]->gameobject_type << " \n";

			if (c1.gameobject_shape.getGlobalBounds().intersects((*(collide_objs.gameobjs[j])).gameobject_shape.getGlobalBounds())) {
				//e.et = Event_Character_Collision;
				e.collided_with = (*(collide_objs.gameobjs[j]));
				e.eventTime = realtime.getTime();
				if ((*(collide_objs.gameobjs[j])).gameobject_type == "deathzone") {
					e.et = Event_Character_Death;
					//e.side_boundary_collision = false;
				}
				else if ((*(collide_objs.gameobjs[j])).gameobject_type == "spawn") {
					e.et = Event_Character_Spawn;
					//e.side_boundary_collision = false;
				}
				else if ((*(collide_objs.gameobjs[j])).gameobject_type == "sideboundary") {

					e.et = Event_Character_SideBoundary;
					//		std::cout << "true";

				}
				else
				{
					e.et = Event_Character_Collision;
					//e.side_boundary_collision = false;
				}
			}

		}
		//std::cout << "Time = " << e.eventTime<<"\n";
		//std::cout << e.et<<"";
		c1.update();
		//std::string input1 = std::to_string(c1.pos.x) + " " + std::to_string(c1.pos.y) + " " + std::to_string(sideboundrycollisions);
		//	std::cout <<"event type=" <<e.et << " key=" <<e.keyvalue << " collided with=" << e.collided_with.gameobject_type << " jump=" << e.isjumping << " isRight="<<e.isRight<<" isLeft="<< e.isLeft<<" Time = "<< e.eventTime<<"\n";
		msgpack::sbuffer sbuf;
		msgpack::pack(&sbuf, e);

		zmq::message_t request2(sbuf.size());
		memcpy(request2.data(), sbuf.data(), sbuf.size());
		socket2.send(request2);

		zmq::message_t rec;		//input message received by server
		socket2.recv(&rec);
		msgpack::sbuffer sbuf2;
		sbuf2.write(static_cast<const char*>(rec.data()), rec.size());

		msgpack::unpacked msg;
		msgpack::unpack(msg, sbuf2.data(), sbuf2.size());
		msgpack::object obj = msg.get();
		//std::cout << obj << std::endl;
		//Character c1(0, 0);
		obj.convert(c1);

		c1.update();
		//	std::cout << collide_objs.gameobjs.size()<<"size\n";
		for (int i = 0; i < collide_objs.gameobjs.size(); i++) {
			zmq::message_t request3(1);
			memcpy(request3.data(), "_", 1);

			socket2.send(request3);

			//input message received by server
			zmq::message_t rec2;
			socket2.recv(&rec2);
			msgpack::sbuffer sbuf3;
			sbuf3.write(static_cast<const char*>(rec2.data()), rec2.size());
			msgpack::unpacked msg2;

			msgpack::unpack(msg2, sbuf3.data(), sbuf3.size());
			msgpack::object obj2 = msg2.get();
			//	std::cout << obj2 << std::endl;
			obj2.convert(*collide_objs.gameobjs[i]);
			//	std::cout << collide_objs.gameobjs[i]->pos.x <<  " object" << std::endl;
		}

		zmq::message_t request3(1);
		memcpy(request3.data(), "_", 1);
		socket2.send(request3);
		zmq::message_t rec3;
		socket2.recv(&rec3);
		std::string out = std::string(static_cast<char*>(rec3.data()), rec3.size());
		temp = stoi(out);
		//std::cout << temp << "temp";
		for (int i = 0; i < temp; i++) {
			zmq::message_t request3(1);
			memcpy(request3.data(), "_", 1);

			socket2.send(request3);

			//input message received by server
			zmq::message_t rec4;
			socket2.recv(&rec4);
			msgpack::sbuffer sbuf4;
			sbuf4.write(static_cast<const char*>(rec4.data()), rec4.size());
			msgpack::unpacked msg3;

			msgpack::unpack(msg3, sbuf4.data(), sbuf4.size());
			msgpack::object obj3 = msg3.get();
			//	std::cout << obj2 << std::endl;
			obj3.convert(chars[i]);
			//	std::cout << chars[i]->pos.x <<"   " <<chars[i]->pos.y << " "<<i<<" chars  " << std::endl;
		}

		zmq::message_t request4(1);
		memcpy(request4.data(), "_", 1);

		socket2.send(request4);

		//input message received by server
		zmq::message_t rec5;
		socket2.recv(&rec5);
		msgpack::sbuffer sbuf5;
		sbuf5.write(static_cast<const char*>(rec5.data()), rec5.size());
		msgpack::unpacked msg4;

		msgpack::unpack(msg4, sbuf5.data(), sbuf5.size());
		msgpack::object obj4 = msg4.get();
		//	std::cout << obj2 << std::endl;
		obj4.convert(side_boundary_collisions_count);

		bool drawtext = false;

		//	//std::cout << positions[0]<<"position 0\n";

		if (c1.pos.x >= 700 and side_boundary_collisions_count[stoi(msg1)] >= 2) {
			drawtext = true;
			inFocus = false;
		}
		//	for (int i = 0; i <= clients; i++) {
		//		c[i].update();
		//	}

		if (record == true) {
			for (int i = 0; i < temp; i++) {
				replay_chars[i].push(chars[i]);
				for(int j =0;j<collide_objs.gameobjs.size();j++)
				replay_gameobjs[i].push(*collide_objs.gameobjs[j]);
				replay_side_boundary_collisions[i].push(side_boundary_collisions_count[i]);
			}
		}

		Replay = false;

		sf::Font font;
		sf::Text text;
		font.loadFromFile("DejaVuSans-Bold.ttf");
		text.setFont(font);
		text.setString("Win");

		text.setCharacterSize(20);
		text.setPosition(400, 100);
		text.setFillColor(sf::Color::Black);

		if (Replay == false) {
			for (int j = 0; j < collide_objs.gameobjs.size(); j++) {
				collide_objs.gameobjs[j]->update();
			}
			for (int j = 0; j < temp; j++) {

				chars[j].update();
			}
			window.clear(sf::Color(135, 206, 235));
			if (drawtext)
				window.draw(text);
			//window.draw(p1.getShape());
			//window.draw(p2.getShape());
			for (int j = 0; j < collide_objs.gameobjs.size(); j++) {
				if (collide_objs.gameobjs[j]->gameobject_type != "deathzone" && collide_objs.gameobjs[j]->gameobject_type != "sideboundary" && collide_objs.gameobjs[j]->gameobject_type != "spawn")
					window.draw(collide_objs.gameobjs[j]->getShape());
			}
			for (int j = 0; j < temp; j++) {
				if (side_boundary_collisions_count[j] == side_boundary_collisions_count[stoi(msg1)])
					window.draw(chars[j].getShape());
			}

		}
		//	window.draw(c1.getShape());
		window.display();
	}

	//c1.setPosition(0, 0);
	socket2.close();
	return 0;
}

