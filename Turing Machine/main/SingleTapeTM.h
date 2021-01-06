#pragma once
#include "TuringMachine.h"

class SingleTapeTM : public TuringMachine
{
private:
	Tape tape;
	void goToNextTransition();
	void toSingleTape();
public:
	SingleTapeTM();
	SingleTapeTM(const Tape&, const std::map<std::string, std::vector<Transition>>&);
	SingleTapeTM(const std::string&, const std::map<std::string, std::vector<Transition>>&);
	SingleTapeTM& operator=(const SingleTapeTM&);

	void moveHeadToBeginning();
	void saveMachine();
	void saveResult() const;
	void runMachine();

	Tape& getTape() ;
	void setTape(const Tape& _tape);
	void printTape();
	void loadMachine();
};

