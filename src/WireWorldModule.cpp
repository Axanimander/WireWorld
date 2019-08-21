#include "WireWorldModule.h"


void Module::addWire(int x, int y){
	std::pair<int, int> xy;
	xy = std::make_pair(x, y);
	positions.push_back(xy);
}

