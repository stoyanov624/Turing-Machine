#include "LinearComposedTM.h"

LinearComposedTM::LinearComposedTM() : first_tm(),second_tm() {}

LinearComposedTM::LinearComposedTM(const TuringMachine& _first_tm, const TuringMachine& _second_tm) {
	first_tm = _first_tm;
	second_tm = _second_tm;
	setTape(_first_tm.getTape());
}

void LinearComposedTM::runMachine() {
	first_tm.runMachine();
	if (first_tm.isSuccesful()) { 
		second_tm.setTape(first_tm.getTape()); // We set the modified tape from T1 and in setTape method head goes to the beginning
		second_tm.runMachine();
		setTape(second_tm.getTape());
	}
	else {
		std::cout << "First Turing Machine in the composition did not end succesfully!" << std::endl;
	}
}