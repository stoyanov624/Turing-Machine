#pragma once
#include "TuringMachine.h"
class MultitapeTM : public TuringMachine {
private:
	std::vector<Tape*> tapes;
	bool isSingleTaped;
	unsigned tapes_count;
	void goToNextTransition();
	void printSingleTapeVersion();
public:
	MultitapeTM();
	MultitapeTM(const std::vector<Tape*>&, const std::map<std::string, std::vector<Transition>>&);
	MultitapeTM& operator=(const MultitapeTM&);

	const std::vector<Tape*>& getTape();
	void setTape(const std::vector<Tape*>&);

	void linearComposition(MultitapeTM&);
	void ifComposition(MultitapeTM&, MultitapeTM&);
	void whileComposition(MultitapeTM&);

	void moveHeadToBeginning();
	void printTape();
	void saveResult() const;
	
	void runMachine();
	void saveMachine();
	void loadMachine();

	void usersTapeChoice();
	void toSingleTape();
	void toMultiTape();
};