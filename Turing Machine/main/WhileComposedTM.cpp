#include "WhileComposedTM.h"
WhileComposedTM::WhileComposedTM() {
	machine_ID_generator -= 3;
	machine_ID = machine_ID_generator++;
}

WhileComposedTM::WhileComposedTM(const Tape& _tape, const TuringMachine& _decider, const TuringMachine& _tm) {
	machine_ID_generator -= 3;
	machine_ID = machine_ID_generator++;
	decider = _decider;
	tm = _tm;
	tape = _tape;
}

void WhileComposedTM::saveResult() const {
	std::string result_file_str = "results_from_While_machines\\WCTMresult" + std::to_string(machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	tape.saveTape(resultFile);
}

void WhileComposedTM::runMachine() {
	decider.setTape(tape);
	decider.runMachine();
	while(decider.isSuccesful()) {
		tm.setTape(decider.getTape());
		tm.runMachine();
		tm.goToStart();
	
		
		decider.setTape(tm.getTape());
		decider.goToStart();
		decider.runMachine();
	}
	tape = decider.getTape();
	saveResult();
}

void WhileComposedTM::loadMachine() {
	std::cout << "Loading machines for while composition..." << std::endl;
	std::cout << "Choose decider machine" << std::endl;
	decider.loadMachine();
	std::cout << "Choose machine that will do stuff" << std::endl;
	tm.loadMachine();
	setTape(decider.getTape());
	usersTapeChoice();
}