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
	std::string current_state;
	std::map<std::string, std::vector<Transition>> instructions;

	void instructionDeserializer(const std::string&);
	void saveInstructions(std::ofstream&);
	void loadInstructions(std::ifstream&);
public:
	TuringMachine();
	TuringMachine(Tape&, const std::map<std::string, std::vector<Transition>>&);
	void goToNextTransition();
	void runMachine();
	void addTransition(const std::string&, Transition);
	void addTape(Tape&);
	void saveMachine(std::ofstream&);
	void loadMachine(std::ifstream&);
	void printTape();
};

