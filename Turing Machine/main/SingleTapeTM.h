#pragma once
#include "TuringMachine.h"

class SingleTapeTM : public TuringMachine
{
private:
	Tape tape;
	void goToNextTransition();
public:
	SingleTapeTM();
	SingleTapeTM(const Tape&, const std::map<std::string, std::vector<Transition>>&);
	SingleTapeTM(const std::string&, const std::map<std::string, std::vector<Transition>>&);
	SingleTapeTM& operator=(const SingleTapeTM&);

	void moveHeadToBeginning();
	void saveMachine();
	void saveResult() const;
	void runMachine();

	//const Tape& getTape() const;
	//void setTape(const Tape& _tape);
	void printTape();
	void loadMachine();
};

