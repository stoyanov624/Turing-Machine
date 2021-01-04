#pragma once
#include "TuringMachine.h"
class DeciderTM : public TuringMachine {
private:
	TuringMachine decider;
	TuringMachine tm0;
	TuringMachine tm1;

public:
	DeciderTM();
	DeciderTM(const TuringMachine&, const TuringMachine&, const TuringMachine&);
	void runMachine() override;
	void saveResult() const override;
	void loadMachine() override;
	void saveMachine() = delete;
};

