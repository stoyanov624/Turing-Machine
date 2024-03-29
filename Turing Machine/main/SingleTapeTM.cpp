#include "SingleTapeTM.h"

SingleTapeTM::SingleTapeTM() :TuringMachine() {}

SingleTapeTM::SingleTapeTM(int _machine_ID,const Tape& other_tm_tape,
	const std::map<std::string, std::vector<Transition>>& other_instructions) : TuringMachine(_machine_ID,other_instructions) {
	tape = other_tm_tape;
}

SingleTapeTM::SingleTapeTM(int _machine_ID, const std::string& tape_str,
	const std::map<std::string, std::vector<Transition>>& other_instructions) : TuringMachine(_machine_ID, other_instructions) {
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
	//Making sure folder exists
	if (!fs::is_directory("turing_machines") || !fs::exists("turing_machines"))
		fs::create_directory("turing_machines");
	//Making sure machine is unique
	std::string machine_file_str = "turing_machines\\singletape_machine" + std::to_string(machine_ID) + ".txt";
	while (fs::exists(machine_file_str)) {
		machine_file_str = "turing_machines\\singletape_machine";
		giveUniqueID(machine_file_str);
	}

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
	if (!fs::is_directory("results_from_machines") || !fs::exists("results_from_machines")) 
		fs::create_directory("results_from_machines");
	
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
	goToStart();
	tape.show_tape();
	while (current_state != "halt" && current_state != "reject" && current_state != "accept") {
		goToNextTransition();
	}
	printFinalState();
	if (isSuccesful()) 
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
	if (!fs::is_directory("turing_machines") || !fs::exists("turing_machines"))
		fs::create_directory("turing_machines");

	std::string path = getPathToWantedLoad();
	if (path == "") {
		std::cout << "No machine to load! Folder empty!\n";
		return;
	}

	if (path[path.find('\\') + 1] != 's') {
		std::cout << "Trying to load a multitape machine! That won't work well!\n";
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

	if (!fs::is_directory("results_from_LC_machines") || !fs::exists("results_from_LC_machines"))
		fs::create_directory("results_from_LC_machines");
	
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

	if (!fs::is_directory("results_from_Decider_machines") || !fs::exists("results_from_Decider_machines"))
		fs::create_directory("results_from_Decider_machines");
	
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

	if (!fs::is_directory("results_from_While_machines") || !fs::exists("results_from_While_machines"))
		fs::create_directory("results_from_Decider_machines");
	
	std::string result_file_str = "results_from_While_machines\\Whileresult" + std::to_string(machine_ID + tm.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	tm.tape.saveTape(resultFile);
}

void SingleTapeTM::usersTapeChoice(bool isGettingCreated) {
	std::string choice;

	if (isGettingCreated) {
		std::cout << "Enter tape: ";
		std::cin >> choice;
		tape.initializeTape(choice);
		std::cout << std::endl;
		return;
	}
	Menu menu;
	menu.addChoice("Enter custom tape");
	menu.addChoice("Use tape from machine you loaded");

	switch (menu.getIndexChoice()) {
	case 0:
		system("cls");
		std::cout << "Enter tape: ";
		std::cin >> choice;
		tape.initializeTape(choice);
		std::cout << std::endl;
		return;
	}
	system("cls");
	std::cout << "Okay we will use the tape from the machine you loaded!\n";
	system("pause");
	return;
}

bool SingleTapeTM::isSingleTapeMachine() const {
	return true;
}

void SingleTapeTM::toSingleTape() {}
void SingleTapeTM::toMultiTape() {}