#pragma once
#include "TuringMachine.h"

class SingleTapeTM : public TuringMachine
{
private:
	Tape tape;
	void goToNextTransition();
	void toSingleTape();
	void toMultiTape();
public:
	SingleTapeTM();
	SingleTapeTM(int, const Tape & = Tape() , const std::map<std::string, std::vector<Transition>> & = std::map<std::string, std::vector<Transition>>());
	SingleTapeTM(int, const std::string&, const std::map<std::string, std::vector<Transition>>& = std::map<std::string, std::vector<Transition>>());
	SingleTapeTM& operator=(const SingleTapeTM&);

	void moveHeadToBeginning();
	void saveMachine();
	void saveResult() const;
	void runMachine();

	const Tape& getTape() const;
	void setTape(const Tape&);
	void printTape();
	void loadMachine();

	void usersTapeChoice();
	void linearComposition(SingleTapeTM&);
	void ifComposition(SingleTapeTM&, SingleTapeTM&);
	void whileComposition(SingleTapeTM&);
};

