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
		tape = other_machine.tape;
		TuringMachine::operator=(other_machine);
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
	if (machineSaveFile.is_open()) {
		machineSaveFile << machine_ID << "\n";
		tape.saveTape(machineSaveFile);
		machineSaveFile << current_state << "\n";
		saveInstructions(machineSaveFile);
		machineSaveFile.close();
	}
	else {
		std::cout << "Error in openning machine savefile!\n";
	}
}

void SingleTapeTM::saveResult() const {
	std::string result_file_str = "results_from_machines\\result" + std::to_string(machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	if (resultFile.is_open()) {
		tape.saveTape(resultFile);
		resultFile.close();
	}
	else {
		std::cout << "Error in opening machine resultfile!\n";
	}
	
}

void SingleTapeTM::runMachine() {
	if (instructions.empty()) {
		std::cout << "Can't start the machine with no instructions!\n";
		return;
	}
	tape.show_tape();
	while (current_state != "halt" && current_state != "reject" && current_state != "accept") {
		goToNextTransition();
	}
	printFinalState();
	saveResult();
}

const Tape& SingleTapeTM::getTape() const {
	return tape;
}

void SingleTapeTM::setTape(const Tape& _tape) {
	tape = _tape;
}

void SingleTapeTM::printTape() {
	tape.show_tape();
}

void SingleTapeTM::loadMachine() {
	std::string path = getPathToWantedLoad();
	if (path == "")
		return;

	if (path[path.find('\\') + 1] != 's') {
		std::cout << "Tryng to load a multitape machine! That won't work well!\n";
		return;
	}

	std::ifstream in(path);
	if (in.is_open()) {
		in >> machine_ID;
		in.get();
		tape.loadTape(in);
		std::string input;
		std::getline(in, input);
		current_state = input;
		loadInstructions(in);
	}
	else {
		std::cout << "Error in opening machine loadfile!\n";
	}
}

void SingleTapeTM::linearComposition(SingleTapeTM& second_tm) {
	runMachine();
	
	if (isSuccesful()) {
		std::cout << "First machine ended succesfully! Launching second machine!\n";
		moveHeadToBeginning();
		second_tm.tape = tape;
		second_tm.runMachine();
	}
	
	std::string result_file_str = "results_from_LC_machines\\LCresult" + std::to_string(machine_ID + second_tm.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	second_tm.tape.saveTape(resultFile);
	
}

void SingleTapeTM::ifComposition(SingleTapeTM& tm1, SingleTapeTM& tm0) {
	Tape saveTape = tape;
	bool we_ran_first_machine = true;
	std::cout << "Launching DECIDER machine!\n";
	runMachine();
	if (isSuccesful()) {
		std::cout << "Launching ACCEPT machine!\n";
		tm1.tape = saveTape;
		tm1.moveHeadToBeginning();
		tm1.runMachine();
	
	}
	else {
		std::cout << "Launching REJECT machine!\n";
		tm0.tape = saveTape;
		tm0.moveHeadToBeginning();
		tm0.runMachine();
		we_ran_first_machine = false;
	}
	
	std::string result_file_str = "results_from_Decider_machines\\result"
		+ std::to_string(machine_ID + tm1.machine_ID + tm0.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	if (we_ran_first_machine) {
		tm1.tape.saveTape(resultFile);
	}
	else {
		tm0.tape.saveTape(resultFile);
	}
}


void SingleTapeTM::whileComposition(SingleTapeTM& tm) {
	tm.tape = tape;
	runMachine();
	while (isSuccesful()) {
		tm.tape = tape;
		tm.runMachine();
		tm.goToStart();
	
		tape = tm.tape;
		goToStart();
		runMachine();
	}
	
	std::string result_file_str = "results_from_While_machines\\Whileresult" + std::to_string(machine_ID + tm.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	tm.tape.saveTape(resultFile);
}

void SingleTapeTM::usersTapeChoice() {
	std::string choice;
	std::cout << "Do you want to enter a custom tape or use the tape from machine you loaded?\n";
	std::cout << "1 - Enter custom tape\n";
	std::cout << "2 - Use tape from first machine\n";
	std::cout << "Your choice: ";
	std::cin >> choice;
	choice.erase(remove(choice.begin(), choice.end(), ' '), choice.end());
	while (choice != "1" && choice != "2") {
		std::cout << "Enter VALID number: ";
		std::cin >> choice;
		choice.erase(remove(choice.begin(), choice.end(), ' '), choice.end());
	}

	if (choice == "1") {
		std::cout << "Enter tape: ";
		std::cin >> choice;
		tape.initializeTape(choice);
		std::cout << std::endl;
	}
	else {
		std::cout << "Okay we will use the tape from the machine you loaded\n!";
		return;
	}
}

void SingleTapeTM::toSingleTape() {}
void SingleTapeTM::toMultiTape() {}