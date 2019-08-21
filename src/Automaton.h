#ifndef AUTOMATON_H
#define AUTOMATON_H
enum Type{
	empty,
	head,
	tail,
	conductor
};
class Automaton{
	public:
		Type type_ = empty;
		bool needsUpdate = false;
};

#endif