//#include "DeciderTM.h"
//
//DeciderTM::DeciderTM() {
//	machine_ID_generator -= 4;
//	machine_ID = machine_ID_generator++;
//}
//
//DeciderTM::DeciderTM(const Tape& _tape, const TuringMachine& _decider, const TuringMachine& _tm1, const TuringMachine& _tm0) {
//	machine_ID_generator -= 4;
//	machine_ID = machine_ID_generator++;
//	decider = _decider;
//	tm1 = _tm1;
//	tm0 = _tm0;
//	tape = _tape;
//}
//
//DeciderTM& DeciderTM::operator=(const DeciderTM& other_dtm) {
//	if (this != &other_dtm) {
//		machine_ID = other_dtm.machine_ID;
//		tape = other_dtm.tape;
//		decider = other_dtm.decider;
//		tm1 = other_dtm.tm1;
//		tm0 = other_dtm.tm0;
//	}
//
//	return *this;
//}
//
//void DeciderTM::runMachine() {
//	decider.setTape(tape);
//	decider.runMachine();
//
//	if (decider.isSuccesful()) {
//		tm1.setTape(tape);
//		tm1.moveHeadToBeginning();
//		tm1.runMachine();
//		tape = tm1.getTape();
//	}
//	else {
//		tm0.setTape(tape);
//		tm1.moveHeadToBeginning();
//		tm0.runMachine();
//		tape = tm0.getTape();
//	}
//
//	saveResult();
//}
//
//void DeciderTM::saveResult() const {
//	std::string result_file_str = "results_from_Decider_machines\\result" + std::to_string(machine_ID) + ".txt";
//	std::ofstream resultFile(result_file_str);
//	tape.saveTape(resultFile);
//}
//
//void DeciderTM::loadMachine() {
//	std::cout << "Loading machines for decider composition...\n\n";
//	std::cout << "Choose decider machine: \n";
//	decider.loadMachine();
//	std::cout << "Choose true machine: \n";
//	tm1.loadMachine();
//	std::cout << "Choose false machine: \n";
//	tm0.loadMachine();
//	
//	setTape(decider.getTape());
//	usersTapeChoice();
//}
//
//void DeciderTM::saveMachine() {}