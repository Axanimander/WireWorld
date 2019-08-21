#ifndef WIREWORLD_MODULE
#define WIREWORLD_MODULE

class Module{
	std::string moduleName;
	Module(std::string name){
		moduleName = name;
	}
	public:
		void addWire(int x, int y);
		std::vector<std::pair<int, int>> positions;

};

#endif