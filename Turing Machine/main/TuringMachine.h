#pragma once
#include <string>
#include <map>
#include "Tape.h"
#include "Transition.h"
#include <cassert>
#include <filesystem>
namespace fs = std::filesystem;
class TuringMachine
{
protected:
	static int machine_ID_generator;
	int machine_ID;
	std::string current_state;
	std::map<std::string, std::vector<Transition>> instructions;
	void saveInstructions(std::ofstream&);
	void loadInstructions(std::ifstream&);
	const std::string getPathToWantedLoad();
	void printFinalState() const;
	
private:
	void instructionDeserializer(const std::string&);
	virtual void goToNextTransition() = 0;
public:
	TuringMachine();
	TuringMachine(const std::map<std::string, std::vector<Transition>>&);
	TuringMachine& operator=(const TuringMachine&);
public:
	int getID() const;
	bool isSuccesful() const;
	bool hasNoInstructions() const;
	void addTransition(const std::string&,const Transition&);
	void goToStart();
public:
	virtual void usersTapeChoice() = 0;
	virtual void moveHeadToBeginning() = 0;
	virtual void printTape() = 0;
	virtual void saveMachine() = 0;
	virtual void loadMachine() = 0;
	virtual void saveResult() const = 0;
	virtual void runMachine() = 0;
	virtual void toSingleTape() = 0;
	virtual void toMultiTape() = 0;
	virtual ~TuringMachine();
};

