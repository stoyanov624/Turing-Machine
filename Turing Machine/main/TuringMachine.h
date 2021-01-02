#pragma once
#include <string>
#include <map>
#include <unordered_set>
#include "Tape.h"
#include "Transition.h"
class TuringMachine
{
private:
	Tape tape;
	std::string current_state;
	std::map<std::string, std::vector<Transition>> instructions;
	virtual void goToNextTransition();
	void instructionDeserializer(const std::string&);
	void saveInstructions(std::ofstream&);
	void loadInstructions(std::ifstream&);

public:
	TuringMachine();
	TuringMachine(const Tape&, const std::map<std::string, std::vector<Transition>>&);
	TuringMachine& operator=(const TuringMachine&);
	virtual void runMachine();
	void addTransition(const std::string&, Transition);
	const Tape& getTape() const;
	void setTape(const Tape&);
	void saveMachine(std::ofstream&);
	void loadMachine(std::ifstream&);
	void printTape();
	//void composition(TuringMachine&);
	bool isSuccesful() const;
};

