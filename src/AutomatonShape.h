#ifndef AUTOMATON_SHAPE
#define AUTOMATON_SHAPE
#include <SFML/Graphics.hpp>

class AutomatonShape : public sf::RectangleShape
{
	public:
		bool NeedsUpdate = false;

};

#endif