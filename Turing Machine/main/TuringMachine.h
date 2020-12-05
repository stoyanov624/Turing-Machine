#pragma once
#include <string>
#include <map>
#include <vector>
#include "Tape.h"
#include "Transition.h"
class TuringMachine
{
private:
	Tape* tape;
	std::string current_state;
	std::map<std::string, std::vector<Transition*>> instructions;
public:
	TuringMachine();
	TuringMachine(Tape*, const std::map<std::string, std::vector<Transition*>>&);
	void goToNextTransition();
	void runMachine();
	void addTransition(Transition*);
	void printTape();
};

