#pragma once
#include <string>
#include <map>
#include <vector>
#include "Tape.h"
#include "Transition.h"
class TuringMachine
{
private:
	Tape tape;
	Transition* current_state;
	std::map<std::string, std::vector<std::pair<Transition*, char>>> graph;
public:
	
};

