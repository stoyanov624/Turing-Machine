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
	std::string current_state;
	std::map<std::string, std::vector<Transition>> instructions;
	//void usersTapeChoice();
	void saveInstructions(std::ofstream&);
	void loadInstructions(std::ifstream&);
	const std::string getPathToWantedLoad();
private:
	void instructionDeserializer(const std::string&);
	virtual void goToNextTransition() = 0;
public:
	TuringMachine();
	TuringMachine(const std::map<std::string, std::vector<Transition>>&);
public:
	int getID() const;
	bool isSuccesful() const;
	void addTransition(const std::string&,const Transition&);
	void goToStart();
public:
	//virtual const std::vector<Tape>& getTapes() const = 0;
	//virtual void setTape(const std::vector<Tape>&) = 0;
	//virtual const Tape& getTape() const = 0;
	//virtual void setTape(const Tape&) = 0;
	virtual void moveHeadToBeginning() = 0;
	virtual void printTape() = 0;
	virtual void saveMachine() = 0;
	virtual void loadMachine() = 0;
	virtual void saveResult() const = 0;
	virtual void runMachine() = 0;
};

