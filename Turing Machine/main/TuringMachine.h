#pragma once
#include <string>
#include <map>
#include "Tape.h"
#include "Transition.h"
#include <filesystem>
namespace fs = std::filesystem;
class TuringMachine
{
protected:
	static int machine_ID_generator;
	int machine_ID;
	Tape tape;
	void usersTapeChoice();
private:
	std::string current_state;
	std::map<std::string, std::vector<Transition>> instructions;
	void goToNextTransition();
	void instructionDeserializer(const std::string&);
	void saveInstructions(std::ofstream&);
	void loadInstructions(std::ifstream&);
	
public:
	TuringMachine();
	TuringMachine(const Tape&, const std::map<std::string, std::vector<Transition>>&);
	TuringMachine& operator=(const TuringMachine&);
public:
	const Tape& getTape() const;
	int getID() const;
	void setTape(const Tape&);
	bool isSuccesful() const;
public:
	void addTransition(const std::string&, Transition);
	void printTape();
	void goToStart();
	void moveHeadToBeginning();
public:
	void saveMachine();
	virtual void loadMachine();
	virtual void saveResult() const;
	virtual void runMachine();
};

