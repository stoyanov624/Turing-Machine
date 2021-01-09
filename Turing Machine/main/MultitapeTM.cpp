#include "MultitapeTM.h"

MultitapeTM::MultitapeTM() : TuringMachine() {
	tapes.push_back(new Tape());
	tapes_count = 1;
	isSingleTaped = false;
}

MultitapeTM::MultitapeTM(int _machine_ID, const std::vector<Tape*>& _tapes, const std::map<std::string, std::vector<Transition>>& _instructions) : TuringMachine(_machine_ID,_instructions) {
	if (!_tapes.empty()) {
		tapes = _tapes;
		tapes_count = tapes.size();
	}
	else {
		tapes.push_back(new Tape());
		tapes_count = 1;
	}
	
	isSingleTaped = false;
}

MultitapeTM& MultitapeTM::operator=(const MultitapeTM& other_multitapeTM) {
	if (this != &other_multitapeTM) {
		tapes = other_multitapeTM.tapes;
		isSingleTaped = other_multitapeTM.isSingleTaped;
		tapes_count = other_multitapeTM.tapes_count;
		TuringMachine::operator=(other_multitapeTM);
	}

	return *this;
}

void MultitapeTM::moveHeadToBeginning() {
	for (unsigned i = 0; i < tapes_count; i++) {
		tapes[i]->move_to_beginning();
	}
}

void MultitapeTM::printTape() {
	
	for (unsigned i = 0; i < tapes_count; i++) {
		std::cout << "Tape " << i + 1 << ": ";
		tapes[i]->show_tape();
	}
}

void MultitapeTM::saveResult() const {
	std::string result_file_str = "results_from_MultiTapemachines\\result" + std::to_string(machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	for (unsigned i = 0; i < tapes_count; i++) {
		tapes[i]->saveTape(resultFile);
	}
}

const std::vector<Tape*>& MultitapeTM::getTape() {
	return tapes;
}

void MultitapeTM::setTape(const std::vector<Tape*>& _tapes) {
	tapes = _tapes;
}

void MultitapeTM::saveMachine() {
	std::string machine_file_str = "turing_machines\\multitape_machine" + std::to_string(machine_ID) + ".txt";
	std::ofstream machineSaveFile(machine_file_str);
	machineSaveFile << machine_ID << "\n";
	machineSaveFile << tapes_count << "\n";
	for (unsigned i = 0; i < tapes_count; i++) {
		tapes[i]->saveTape(machineSaveFile);
	}
	machineSaveFile << current_state << "\n";
	saveInstructions(machineSaveFile);
}

void MultitapeTM::loadMachine() {
	std::string path = getPathToWantedLoad();
	if (path == "") 
		return;

	if (path[path.find('\\') + 1] != 'm') {
		std::cout << "Tryng to load a singletape machine! That won't work well!\n";
		return;
	}
	std::ifstream in(path);

	in >> machine_ID;
	in.get();
	
	in >> tapes_count;
	in.get();
	tapes.clear();
	for (unsigned i = 0; i < tapes_count; i++) {
		Tape* t = new Tape();
		tapes.push_back(t);
		tapes[i]->loadTape(in);
	}
	std::string input;
	
	std::getline(in, input);
	current_state = input;
	loadInstructions(in);
}

void MultitapeTM::linearComposition(MultitapeTM& second_tm) {
	runMachine();
	if (isSuccesful()) {
		moveHeadToBeginning();
		second_tm.tapes = tapes;
		second_tm.tapes_count = tapes_count;
		second_tm.runMachine();
	}

	std::string result_file_str = "results_from_LC_machines\\LCresult" + std::to_string(machine_ID + second_tm.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	for (unsigned i = 0; i < tapes_count; i++) {
		second_tm.tapes[i]->saveTape(resultFile);
	}
}

void MultitapeTM::ifComposition(MultitapeTM& tm1, MultitapeTM& tm0) {
	std::vector<Tape*> saveTape = tapes;
	bool first_machine_ran = true;
	runMachine();
	if (isSuccesful()) {
		tm1.tapes = saveTape;
		tm1.tapes_count = tapes_count;
		tm1.moveHeadToBeginning();
		tm1.runMachine();

	}
	else {
		tm0.tapes = saveTape;
		tm0.tapes_count = tapes_count;
		tm0.moveHeadToBeginning();
		tm0.runMachine();
		first_machine_ran = false;
	}

	std::string result_file_str = "results_from_Decider_machines\\result" 
									+ std::to_string(machine_ID + tm1.machine_ID + tm0.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	for (unsigned i = 0; i < tapes_count; i++) {
		if (first_machine_ran) {
			tm1.tapes[i]->saveTape(resultFile);
		}
		else {
			tm0.tapes[i]->saveTape(resultFile);
		}
	}
}

void MultitapeTM::whileComposition(MultitapeTM& tm) {
	tm.tapes = tapes;
	tm.tapes_count = tapes_count;
	runMachine();
	while (isSuccesful()) {
		tm.tapes = tapes;
		tm.runMachine();
		tm.goToStart();

		tapes = tm.tapes;
		goToStart();
		runMachine();
	}

	std::string result_file_str = "results_from_While_machines\\Whileresult" + std::to_string(machine_ID + tm.machine_ID) + ".txt";
	std::ofstream resultFile(result_file_str);
	for (unsigned i = 0; i < tapes_count; i++) {
		tm.tapes[i]->saveTape(resultFile);
	}
}

void MultitapeTM::runMachine() {
	if (instructions.empty()) {
		std::cout << "Can't start the machine with no instructions!\n";
		return;
	}

	if (tapes.empty()) {
		std::cout << "Can't start the machine with no tapes!\n";
		return;
	}
	if (isSingleTaped) {
		printSingleTapeVersion();
	}
	else {
		printTape();
	}
	goToStart();
	while (current_state != "halt" && current_state != "reject" && current_state != "accept") {
		goToNextTransition();
	}
	printFinalState();
	
	if(isSuccesful())
		saveResult();
}

void MultitapeTM::goToNextTransition() {
	bool is_good_transition = true;
	Transition good_transition;
	for (auto t : instructions[current_state]) {
		is_good_transition = true;
		for (unsigned i = 0; i < tapes_count; i++) {
			if (t.getCurrentCell()[i] != tapes[i]->read()) {
				is_good_transition = false;
				break;
			}
		}
		if (is_good_transition) {
			good_transition = t;
			break;
		}
	}

	if (is_good_transition) {
		for (unsigned i = 0; i < tapes_count; i++) {
			std::cout << i + 1 << '.' << "Current cell is " << tapes[i]->read() << " soo change it to " << good_transition.getChangeCell()[i];
			tapes[i]->write(good_transition.getChangeCell()[i]);
			switch (good_transition.getMoveDirection()[i]) {
			case 'R':
				std::cout << " and move head to the right\n";
				tapes[i]->move_right();
				break;
			case 'L':
				std::cout << " and move head to the left\n";
				tapes[i]->move_left();
				break;
			default:
				std::cout << " and don't move the head\n";
				break;
			}
		}
		current_state = good_transition.getCurrentTransition();
		std::cout << "\n";
		if (isSingleTaped) {
			printSingleTapeVersion();
		}
		else {
			printTape();
		}
		return;
	}

	current_state = "reject";
}

void MultitapeTM::toSingleTape() {
	isSingleTaped = true;
}

void MultitapeTM::toMultiTape() {
	isSingleTaped = false;
}

void MultitapeTM::printSingleTapeVersion() {
	std::string single_tape = "[#";
	for (size_t i = 0; i < tapes_count; i++) {
		single_tape += tapes[i]->tape_str();
		single_tape += "#";
	}
	single_tape += "]";
	std::cout << single_tape << std::endl;
}

void MultitapeTM::usersTapeChoice() {
	std::string choice;
	std::cout << "Do you want to enter a custom tape or use the tape from first machine you loaded?\n";
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
		tapes_count = getNumberOfTapesYouNeed();
		tapes.clear();
		for (unsigned i = 0; i < tapes_count; i++) {
			std::cout << "Enter tape " << i + 1 << ": ";
			std::cin >> choice;
			tapes.push_back(new Tape());
			tapes[i]->initializeTape(choice);
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "Okay we will use the tape from the machine you loaded!\n";
		return;
	}
}