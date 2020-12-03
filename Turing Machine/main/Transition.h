#pragma once
#include <string>
class Transition
{
private:
	std::string current_transition;
	std::string current_cell;
	std::string change_cell;
	char move_direction;
	std::string next_transition;
public:
	Transition();
	
};

