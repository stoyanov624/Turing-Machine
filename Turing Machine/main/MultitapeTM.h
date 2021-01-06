#pragma once
#include "TuringMachine.h"
class MultitapeTM : public TuringMachine {
private:
	std::vector<Tape*> tapes;
	unsigned tapes_count;
	void goToNextTransition();
public:
	MultitapeTM();
	//MultitapeTM(const std::string&, const std::map<std::string, std::vector<Transition>>&);
	MultitapeTM(const std::vector<Tape*>&, const std::map<std::string, std::vector<Transition>>&);
	MultitapeTM& operator=(const MultitapeTM&);
public:
	//const std::vector<Tape>& getTape() const;
	//void setTape(const std::vector<Tape>&);
public:
	void moveHeadToBeginning();
	void printTape();
	void saveResult() const;
	
	void runMachine();

	//const Tape& getTape() const;
	//void setTape(const Tape& _tape);
	void saveMachine();
	void loadMachine();
};