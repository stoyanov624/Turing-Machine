#include "SingleTapeTM.h"

SingleTapeTM::SingleTapeTM() :TuringMachine() {}

SingleTapeTM::SingleTapeTM(const Tape& other_tm_tape,
	const std::map<std::string, std::vector<Transition>>& other_instructions) : TuringMachine(other_instructions) {
	tape = other_tm_tape;
}

SingleTapeTM::SingleTapeTM(const std::string& tape_str,
	const std::map<std::string, std::vector<Transition>>& other_instructions) : TuringMachine(other_instructions) {
	tape.initializeTape(tape_str);
}

SingleTapeTM& SingleTapeTM::operator=(const SingleTapeTM& other_machine) {
	if (this != &other_machine) {
		machine_ID = other_machine.machine_ID;
		tape = other_machine.tape;
		current_state = other_machine.current_state;
		instructions = other_machine.instructions;
	}

	return *this;
}

void SingleTapeTM::goToNextTransition() {
	for (auto t : instructions[current_state]) {
		if (t.getCurrentCell()[0] == tape.read()) {

			std::cout << "Current cell is " << t.getCurrentCell()
				<< " soo change it to " << t.getChangeCell();

			tape.write(t.getChangeCell()[0]);

			switch (t.getMoveDirection()[0]) {
			case 'R':
				std::cout << " and move head to the right!\n";
				tape.move_right();
				break;
			case 'L':
				std::cout << " and move head to the left!\n";
				tape.move_left();
				break;
			default:
				std::cout << " and don't move the head!\n";
				break;
			}
			current_state = t.getCurrentTransition();
			//Sleep(1000);
			//system("cls");
			tape.show_tape();
			return;
		}
	}
	current_state = "reject";
}


void SingleTapeTM::moveHeadToBeginning() {
	tape.move_to_beginning();
}

void SingleTapeTM::saveMachine() {
	std::string machine_file_str = "turing_machines\\singletape_machine" + std::to_string(machine_ID) + ".txt";
	std::ofstream machineSaveFile(machine_file_str);
	machineSaveFile << machine_ID << "\n";
	tape.saveTape(machineSaveFile);
	machineSaveFile << current_state << "\n";
	saveInstructions(machineSaveFile);
}


void SingleTapeTM::saveResult() const {
	std::string result_file_str = "results_from_machines\\result" + std::to_string(machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	tape.saveTape(resultFile);
}


void SingleTapeTM::runMachine() {
	tape.show_tape();
	while (current_state != "halt" && current_state != "reject" && current_state != "accept") {
		goToNextTransition();
	}
	if (current_state == "halt") {
		std::cout << "\nMACHINE " << machine_ID << " HALTED!\n\n";
	}
	else if (current_state == "accept") {
		std::cout << "\nMACHINE" << machine_ID << " ACCEPTED YOUR WORD\n\n";
	}
	else if (current_state == "reject") {
		std::cout << "\nMACHINE" << machine_ID << " REJECTED YOUR WORD\n\n";
	}
	saveResult();
}


//const Tape& SingleTapeTM::getTape() const {
//	return tape;
//}
//
//
//void SingleTapeTM::setTape(const Tape& _tape) {
//	tape = _tape;
//}

void SingleTapeTM::printTape() {
	tape.show_tape();
}

void SingleTapeTM::loadMachine() {
	std::string path = getPathToWantedLoad();
	if (path == "")
		return;

	std::ifstream in(path);
	in >> machine_ID;
	in.get();
	tape.loadTape(in);
	std::string input;
	std::getline(in, input);
	current_state = input;
	loadInstructions(in);
	
}