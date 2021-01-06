//#include "LinearComposedTM.h"
//
//LinearComposedTM::LinearComposedTM() {
//	machine_ID_generator -= 3;
//	machine_ID = machine_ID_generator++;
//}
//
//LinearComposedTM::LinearComposedTM(const Tape& tape_to_work_with, const TuringMachine& _first_tm, const TuringMachine& _second_tm) {
//	machine_ID_generator -= 3;
//	machine_ID = machine_ID_generator++;
//	first_tm = _first_tm;
//	second_tm = _second_tm;
//	tape = tape_to_work_with;
//}
//
//LinearComposedTM& LinearComposedTM::operator=(const LinearComposedTM& other_lctm) {
//	if (this != &other_lctm) {
//		machine_ID = other_lctm.machine_ID;
//		tape = other_lctm.tape;
//		first_tm = other_lctm.first_tm;
//		second_tm = other_lctm.second_tm;
//	}
//
//	return *this;
//}
//
//void LinearComposedTM::saveResult() const {
//	std::string result_file_str = "results_from_LC_machines\\LCresult" + std::to_string(machine_ID) + ".txt";
//	std::ofstream resultFile(result_file_str);
//	tape.saveTape(resultFile);
//}
//
//void LinearComposedTM::runMachine() {
//	first_tm.setTape(tape);
//	first_tm.runMachine();
//	if (first_tm.isSuccesful()) { 
//		second_tm.setTape(first_tm.getTape()); 
//		second_tm.moveHeadToBeginning();
//		// We set the modified tape from T1 and in setTape method head goes to the beginning
//		second_tm.runMachine();
//		tape = second_tm.getTape();
//		std::cout << "Linear Composed Machine " << this->machine_ID << " HALTED!" << std::endl;
//
//		saveResult();
//	}
//	else {
//		std::cout << "First Turing Machine in the composition did not end succesfully!" << std::endl;
//	}
//}
//
//void LinearComposedTM::loadMachine() {
//	
//	std::cout << "Loading machines for linear composition..." << std::endl;
//	std::cout << "Choose first machine for composition" << std::endl;
//	first_tm.loadMachine();
//	std::cout << "Choose second machine for composition" << std::endl;
//	second_tm.loadMachine();
//	setTape(first_tm.getTape());
//	usersTapeChoice();
//}
//
//void LinearComposedTM::saveMachine() {}