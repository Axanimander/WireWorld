#include "App.h"
#include <iostream>
Application::Application(int ScreenX, int ScreenY){
	SCREEN_RES_X = ScreenX;
	SCREEN_RES_Y = ScreenY;
	world.initWorld();
	makeRects();
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setPosition(0, 0);
	text.setColor(sf::Color::Yellow);
	text.setScale({.5, .5});
	rw.setView(v);
	rw.setFramerateLimit(60);
	clock.restart();
}
void Application::run(){
	bool running = false;
	bool moving = false; // for click drag
	float lastTick = 0;
	float currentTick = 0;
	sf::Vector2f oldPos;
	std::ostringstream oss;

	while (rw.isOpen())
	{
		rw.setView(v);
		lastTick = currentTick;
		float currentTick = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		float tickInterval = currentTick - lastTick;
		float fps = 1000.0f / tickInterval;
		std::ostringstream oss;
		oss << fps;
		frames++;

		while (rw.pollEvent(e))
		{
			if (e.type == sf::Event::Resized)
			{
				sf::Vector2f windowSize(rw.getSize());
				const sf::Vector2f viewSize = windowSize / 2.f;
				sf::FloatRect visibleArea(0, 0, viewSize.x, viewSize.y);
				rw.setView(sf::View(visibleArea));
			}
			if (e.type == sf::Event::Closed)
				rw.close();
			if(e.type == sf::Event::KeyPressed){
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
					cout << "what\n";
					running = !running;
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
					v.rotate(-2.0f);
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
					v.rotate(2.0f);
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
					v.move(0, -1);
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
					v.move(0, 1);
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)){
					v.zoom(1.1);
				}
			}
			if(e.type == sf::Event::MouseButtonPressed){
				sf::Vector2i mousepos2 = sf::Mouse::getPosition(rw);
				sf::Vector2f mousepos =  rw.mapPixelToCoords(mousepos2, v);
				if(e.mouseButton.button == sf::Mouse::Left){
					moving = true;
					oldPos = rw.mapPixelToCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)){
						addConductor(mousepos.x / world.scale, mousepos.y / world.scale);
					}
				}
				if(e.mouseButton.button == sf::Mouse::Right){
					addHead(mousepos.x / world.scale, mousepos.y / world.scale);
				}
			}
			if(e.type == sf::Event::MouseButtonReleased){
				moving = false;
			}
			if(e.type == sf::Event::MouseMoved){
				if(!moving){
					break;
				}
				sf::Vector2f newPos = rw.mapPixelToCoords(sf::Vector2i(e.mouseMove.x, e.mouseMove.y));
				sf::Vector2f deltaPos = oldPos - newPos;
				v.setCenter(v.getCenter() + deltaPos);
				oldPos = rw.mapPixelToCoords(sf::Vector2i(e.mouseMove.x, e.mouseMove.y));
			}
			if(e.type == sf::Event::MouseWheelMoved){
				if(e.mouseWheelScroll.wheel > 0){
					v.zoom(.9);
				}
				if(e.mouseWheelScroll.wheel < 0){
					v.zoom(1.1);
				}
			}
		}
		if(running && frames % SIMULATION_SPEED == 0){
		 world.Step();
		}
		if(frames % SIMULATION_SPEED == 0){
			text.setString(oss.str());
			std::cout<< v.getCenter().x << " X " << v.getCenter().y << " Y \n";
		}
		update();
		render();
	}
}

void Application::makeRects(){
	for(int x = 0; x < world.SIZE_X; x++){
		for(int y = 0; y < world.SIZE_Y; y++){
			automatons.push_back(getRect(x, y));
		}
	}
}

void Application::update(){
	for(int x = 0; x < world.SIZE_X; x++){
		for(int y = 0; y < world.SIZE_Y; y++){
			updateRect(x, y);
		}
	}
}

void Application::render(){
	rw.clear();
	for(auto it : automatons){
		if(it->NeedsUpdate){
		rw.draw(*it, sf::RenderStates(sf::BlendAlpha));
		}
	}

	rw.setView(rw.getDefaultView());
	rw.draw(text);
	rw.display();
}

void Application::addConductor(int x, int y){
	world.placeConductor(x, y);
	if(world.getAutomaton(x, y)->type_ == conductor){
		automatons[world.getPos(x, y)]->NeedsUpdate = false;
		automatons[world.getPos(x, y)] = getRect(x, y);
	}
}

void Application::addHead(int x, int y){
	world.placeHead(x, y);
}

void Application::addTail(int x, int y){
	world.placeTail(x, y);
}

AutomatonShape* Application::getRect(int x, int y){
	AutomatonShape* R;
	R = new AutomatonShape;
	sf::Color c;
	Automaton* a = world.getAutomaton(x, y);
		switch(a->type_){
		case conductor:
			c = sf::Color::Yellow;
			R->NeedsUpdate = true;
			break;
		case head:
			c = sf::Color::Blue;
			R->NeedsUpdate = true;
			break;
		case tail:
			c = sf::Color::Red;
			R->NeedsUpdate = true;
			break;
		case empty:
			c = sf::Color::Black;
			break;
	}
	R->setFillColor(c);
	sf::Color oc(255, 255, 255, 80);
	R->setOutlineColor(oc);
	R->setOutlineThickness(1.f);
	R->setPosition(x * world.scale, y * world.scale);
	R->setSize(sf::Vector2f(world.scale, world.scale));

	return R;
}

void Application::updateRect(int x, int y){
	AutomatonShape* R = automatons[world.getPos(x, y)];
	if(world.getAutomaton(x, y)->needsUpdate == false){
		return;
	}
	sf::Color v;
	Automaton* a = world.getAutomaton(x, y);
		switch(a->type_){
		case conductor:
			v = sf::Color::Yellow;
			R->NeedsUpdate = true;
			break;
		case head:
			v = sf::Color::Blue;
			R->NeedsUpdate = true;
			break;
		case tail:
			v = sf::Color::Red;
			R->NeedsUpdate = true;
			break;
		case empty:
			v = sf::Color::Black;
			R->NeedsUpdate = false;
			break;
	}
//	v.r = (v.r + static_cast<int>(3 * rw.getView().getRotation()) % 255);
//	v.g = (v.g + static_cast<int>(4 * rw.getView().getRotation()) % 255);
//	v.b = (v.b + static_cast<int>(5 * rw.getView().getRotation()) % 255);
	R->setFillColor(v);
}