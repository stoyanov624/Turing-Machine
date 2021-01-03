#pragma once
#include "TuringMachine.h"

class WhileComposedTM : public TuringMachine
{
private:
	TuringMachine decider;
	TuringMachine tm;

public:
	WhileComposedTM();
	WhileComposedTM(const TuringMachine&, const TuringMachine&);
	void runMachine() override;
	void saveResult() const override;
	void loadMachine() override;
};

