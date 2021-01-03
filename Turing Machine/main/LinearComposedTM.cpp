#include "LinearComposedTM.h"

LinearComposedTM::LinearComposedTM() {
	machine_ID_generator -= 3;
	machine_ID = machine_ID_generator++;
}

LinearComposedTM::LinearComposedTM(const TuringMachine& _first_tm, const TuringMachine& _second_tm) {
	machine_ID_generator -= 3;
	machine_ID = machine_ID_generator++;
	//std::cout << machine_ID_generator << std::endl;
	first_tm = _first_tm;
	second_tm = _second_tm;
	tape = _first_tm.getTape();
}

void LinearComposedTM::saveResult() const {
	std::string result_file_str = "results_from_LC_machines\\result" + std::to_string(machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	tape.saveTape(resultFile);
}

void LinearComposedTM::runMachine() {
	first_tm.runMachine();
	if (first_tm.isSuccesful()) { 
		second_tm.setTape(first_tm.getTape()); // We set the modified tape from T1 and in setTape method head goes to the beginning
		second_tm.moveHeadToBeginning();
		second_tm.runMachine();
		tape = second_tm.getTape();
		std::cout << "Linear Composed Machine " << this->machine_ID << " HALTED!" << std::endl;

		saveResult();
	}
	else {
		std::cout << "First Turing Machine in the composition did not end succesfully!" << std::endl;
	}
}

void LinearComposedTM::loadMachine() {
	std::cout << "Loading machines for linear composition..." << std::endl;
	std::cout << "Choose first machine for composition" << std::endl;
	first_tm.loadMachine();
	std::cout << "Choose second machine for composition" << std::endl;
	second_tm.loadMachine();
}