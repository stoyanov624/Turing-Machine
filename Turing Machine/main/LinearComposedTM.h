#include "TuringMachine.h"
#pragma once

class LinearComposedTM : public TuringMachine {
private:
	TuringMachine first_tm;
	TuringMachine second_tm;
public:
	LinearComposedTM();
	LinearComposedTM(const TuringMachine&, const TuringMachine&);
	void runMachine() override;
	void saveResult() const override;
	void loadMachine() override;
};

