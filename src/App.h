#ifndef  APP_H
#define APP_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/System/Clock.hpp>
#include "AutomatonWorld.h"
#include "AutomatonShape.h"
using std::cout;
using std::string;

class Application{
	public:
		void run();
		Application(int x, int y);
		void addConductor(int x, int y);
		void addHead(int x, int y);
		void addTail(int x, int y);
		int getPos(int x, int y);
	private:
		unsigned int SCREEN_RES_X = 800;
		unsigned int SCREEN_RES_Y = 600;
		unsigned int UPDATE_SPEED = 10;
		unsigned int SIMULATION_SPEED = 10;
		unsigned int frames = 0;
		sf::Font font;
		sf::Text text;
		sf::Clock clock;
		string WINDOW_STRING = "Window thing";
		sf::VideoMode vm = sf::VideoMode(SCREEN_RES_X, SCREEN_RES_Y);
		sf::Event e;
		std::vector<AutomatonShape*> automatons;
		sf::RenderWindow rw = sf::RenderWindow(vm, WINDOW_STRING);
		AutomatonWorld world;
		sf::View v  = rw.getView();

		void render();
		void makeRects();
		void updateRect(int x, int y);
		void update();
		void fastUpdate();
		AutomatonShape* getRect(int x, int y);
};

#endif // ! APP_H