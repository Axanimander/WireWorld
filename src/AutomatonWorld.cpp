#include "AutomatonWorld.h"

void AutomatonWorld::initWorld(){
	for(int i = 0; i < SIZE_X * SIZE_Y; i++){
		Automaton *temp = new Automaton;
		Automatons.push_back(temp);
	}
}
int AutomatonWorld::getPos(int x, int y){
	return (x * SIZE_X) + y;
}
Automaton* AutomatonWorld::north(int x, int y){
	if(y - 1 > 0){
		return Automatons[getPos(x, y - 1)];
	}
	return NULL;
}
Automaton* AutomatonWorld::south(int x, int y){
	if(y + 1 < SIZE_Y){
		return Automatons[getPos(x, y + 1)];
	}
	return NULL;
}
Automaton* AutomatonWorld::east(int x, int y){
	if(x + 1 < SIZE_X){
		return Automatons[getPos(x + 1, y)];
	}
	return NULL;
}
Automaton* AutomatonWorld::west(int x, int y){
	if(x - 1 > 0){
		return Automatons[getPos(x - 1, y)];
	}
	return NULL;
}
Automaton* AutomatonWorld::northeast(int x, int y){
	if(x + 1 < SIZE_X && y - 1 > 0){
		return Automatons[getPos(x + 1, y - 1)];
	}
	return NULL;
}
Automaton* AutomatonWorld::northwest(int x, int y){
	if(x - 1 > 0 && y - 1 > 0){
		return Automatons[getPos(x - 1, y - 1)];
	}
	return NULL;
}
Automaton* AutomatonWorld::southeast(int x, int y){
	if(x + 1 < SIZE_X && y + 1 < SIZE_Y){
		return Automatons[getPos(x + 1, y + 1)];
	}
	return NULL;
}
Automaton* AutomatonWorld::southwest(int x, int y){
	if(x - 1 > 0 && y + 1 <= SIZE_Y){
		return Automatons[getPos(x - 1, y + 1)];
	}
	return NULL;
}

Automaton* AutomatonWorld::getAutomaton(int x, int y){
	return Automatons[getPos(x, y)];
}

std::vector<Automaton*> AutomatonWorld::getNeighbors(int x, int y){
	std::vector<Automaton*> neighbors;
	neighbors.push_back(north(x, y));
	neighbors.push_back(south(x, y));
	neighbors.push_back(east(x, y));
	neighbors.push_back(west(x, y));
	neighbors.push_back(northwest(x, y));
	neighbors.push_back(northeast(x, y));
	neighbors.push_back(southeast(x, y));
	neighbors.push_back(southwest(x, y));
	return neighbors;
}
void AutomatonWorld::Step(){
	updateAutomatons();
	for(int i = 0; i < SIZE_X; i++){
		for(int j = 0; j < SIZE_Y; j++){
			Automaton* here = getAutomaton(i, j);
			switch(here->type_){
			case empty:
				break;
			case head:
				toUpdate.push_back(here);
				break;
			case tail:
				toUpdate.push_back(here);
				break;
			case conductor:
				std::vector<Automaton*> neighbors = getNeighbors(i, j);
				int headcount = 0;
				for(auto it : neighbors){
					if (it->type_ == head){
						headcount++;
					}
				}
				if(headcount == 2 || headcount == 1){
					toUpdate.push_back(here);
				}
			break;
			}
		}
	}
}

void AutomatonWorld::updateAutomatons(){
		for(auto here : toUpdate){
				switch(here->type_){
					case head:
						here->type_ = tail;
						break;
					case tail:
						here->type_ = conductor;
						break;
					case conductor:
						here->type_ = head;
						break;
				}
		}
		toUpdate.clear();
}

void AutomatonWorld::placeConductor(int x, int y){
	if(getAutomaton(x, y)->type_ == conductor){
		getAutomaton(x, y)->type_ = empty;
		getAutomaton(x, y)->needsUpdate = true;
		return;
	}
	getAutomaton(x, y)->type_ = conductor;
	getAutomaton(x, y)->needsUpdate = true;
}

void AutomatonWorld::placeHead(int x, int y){
	getAutomaton(x, y)->type_ = head;
	getAutomaton(x, y)->needsUpdate = true;
}

void AutomatonWorld::placeTail(int x, int y){
	getAutomaton(x, y)->type_ = tail;
	getAutomaton(x, y)->needsUpdate = true;
}

void AutomatonWorld::placeModule(Module* m, int offsetx, int offsety){
	for(auto it : m->positions){
		placeConductor(it.first + offsetx, it.second + offsety);
	}
}
