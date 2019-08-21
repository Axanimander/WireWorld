#ifndef AUTOMATON_WORLD
#define AUTOMATON_WORLD
#include <vector>
#include "Automaton.h"
#include "WireWorldModule.h"
class AutomatonWorld{
		Automaton* north(int x, int y);
		Automaton* south(int x, int y);
		Automaton* east(int x, int y);
		Automaton* west(int x, int y);
		Automaton* northeast(int x, int y);
		Automaton* northwest(int x, int y);
		Automaton* southeast(int x, int y);
		Automaton* southwest(int x, int y);
		std::vector<Automaton*> getNeighbors(int x, int y);
	public:
		void initWorld();
		void Step();
		void clearWorld();
		int SIZE_X = 500;
		int SIZE_Y = 500;
		int scale = 10;
		std::vector<Automaton*> Automatons;
		std::vector<Automaton*> toUpdate;
		void placeConductor(int x, int y);
		void placeHead(int x, int y);
		void placeTail(int x, int y);
		Automaton* getAutomaton(int x, int y);
		int getPos(int x, int y);
		void updateAutomatons();
		void placeModule(Module* m, int offsetx, int offsety);


};
#endif