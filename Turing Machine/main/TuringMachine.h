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
	int machine_ID;
	std::string current_state;
	std::map<std::string, std::vector<Transition>> instructions;

	void saveInstructions(std::ofstream&);
	void loadInstructions(std::ifstream&);
	void printFinalState() const;
	void printUsersChoices() const;
	void giveUniqueID(std::string&);

	const std::string getPathToWantedLoad();
	unsigned getNumberOfTapesYouNeed();
public:

	TuringMachine();
	TuringMachine(int, const std::map<std::string, std::vector<Transition>>&);
	TuringMachine& operator=(const TuringMachine&);

	int getID() const;
	bool isSuccesful() const;
	bool hasNoInstructions() const;

	void instructionDeserializer(const std::string&);
	void addTransition(const std::string&,const Transition&);
	void goToStart();

	virtual void goToNextTransition() = 0;
	virtual void usersTapeChoice(bool = false) = 0;
	virtual void moveHeadToBeginning() = 0;
	virtual void printTape() = 0;
	virtual void saveMachine() = 0;
	virtual void loadMachine() = 0;
	virtual void saveResult() const = 0;
	virtual void runMachine() = 0;
	virtual void toSingleTape() = 0;
	virtual void toMultiTape() = 0;
};

