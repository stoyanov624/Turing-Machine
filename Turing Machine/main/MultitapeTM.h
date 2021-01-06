#pragma once
#include "TuringMachine.h"
#include "SingleTapeTM.h"
class MultitapeTM : public TuringMachine {
private:
	std::vector<Tape*> tapes;
	bool isSingleTaped;
	unsigned tapes_count;
	void goToNextTransition();
	void printSingleTapeVersion();
public:
	MultitapeTM();
	//MultitapeTM(const std::string&, const std::map<std::string, std::vector<Transition>>&);
	MultitapeTM(const std::vector<Tape*>&, const std::map<std::string, std::vector<Transition>>&);
	MultitapeTM& operator=(const MultitapeTM&);
public:
	const std::vector<Tape*>& getTape() const;
	void setTape(const std::vector<Tape*>&);
public:
	void moveHeadToBeginning();
	void printTape();
	void saveResult() const;
	void runMachine();
	void saveMachine();
	void loadMachine();
	void toSingleTape();
};